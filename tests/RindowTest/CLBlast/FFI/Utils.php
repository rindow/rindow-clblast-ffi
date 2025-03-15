<?php
namespace RindowTest\CLBlast\FFI;

use Interop\Polite\Math\Matrix\NDArray;
use Interop\Polite\Math\Matrix\BLAS;
use Interop\Polite\Math\Matrix\OpenCL;
use Interop\Polite\Math\Matrix\DeviceBuffer;
use Interop\Polite\Math\Matrix\LinearBuffer;
use InvalidArgumentException;
use RuntimeException;
use TypeError;
use ArrayObject;
use ArrayAccess;
use Rindow\Math\Buffer\FFI\BufferFactory as HostBufferFactory;
use Rindow\OpenCL\FFI\OpenCLFactory;
use Rindow\OpenCL\FFI\EventList;

function C(
    ?float $r=null,
    ?float $i=null,
) : object
{
    $r = $r ?? 0.0;
    $i = $i ?? 0.0;
    return (object)['real'=>$r,'imag'=>$i];
}

trait Utils
{
    protected ?object $hostBufferFactory = null;
    protected ?object $openCLFactory = null;
    protected object $queue;
    protected ?bool $fp64 = null;

    public function setOpenCLQueue(object $openCLQueue)
    {
        $this->queue = $openCLQueue;
    }

    protected function fp64() : bool
    {
        if($this->fp64!==null) {
            return $this->fp64;
        }
        $devices = $this->queue->getContext()->getInfo(OpenCL::CL_CONTEXT_DEVICES);
        $extensions = $devices->getInfo(0,OpenCL::CL_DEVICE_EXTENSIONS);
        if(strpos($extensions,'cl_khr_fp64')===false) {
            $this->fp64 = false;
        } else {
            $this->fp64 = true;
        }
        return $this->fp64;
    }

    public function hostBufferFactory() : object
    {
        if($this->hostBufferFactory==null) {
            $this->hostBufferFactory = new hostBufferFactory();
        }
        return $this->hostBufferFactory;
    }

    public function getOpenCL()
    {
        if($this->opencl===null) {
            $this->opencl = new OpenCLFactory();
        }
        return $this->opencl;
    }

    //public function openCLFactory() : object
    //{
    //    if($this->openCLFactory==null) {
    //        $this->openCLFactory = new OpenCLFactory();
    //    }
    //    return $this->openCLFactory;
    //}

    public function hostArray(mixed $array=null, ?int $dtype=null, ?array $shape=null) : object
    {
        $ndarray = new class ($array, $dtype, $shape, service:$this) implements NDArray {
            protected object $buffer;
            protected int $size;
            protected int $dtype;
            protected int $offset;
            protected array $shape;
            protected object $service;
            public function __construct(
                mixed $array=null, ?int $dtype=null, ?array $shape=null, ?object $service=null,
            ) {
                $this->service = $service;
                $dtype = $dtype ?? NDArray::float32;
                if(is_array($array)||$array instanceof ArrayObject) {
                    $dummyBuffer = new ArrayObject();
                    $idx = 0;
                    $this->array2Flat($array,$dummyBuffer,$idx,$prepare=true);
                    $buffer = $this->newBuffer($idx,$dtype);
                    $idx = 0;
                    $this->array2Flat($array,$buffer,$idx,$prepare=false);
                    $offset = 0;
                    if($shape===null) {
                        $shape = $this->genShape($array);
                    }
                } elseif(is_numeric($array)||is_bool($array)) {
                    if(is_bool($array)&&$dtype!=NDArray::bool) {
                        throw new InvalidArgumentException("unmatch dtype with bool value");
                    }
                    $buffer = $this->newBuffer(1,$dtype);
                    $buffer[0] = $array;
                    $offset = 0;
                    if($shape===null) {
                        $shape = [];
                    }
                    $this->checkShape($shape);
                    if(array_product($shape)!=1)
                        throw new InvalidArgumentException("Invalid dimension size");
                } elseif($array===null && $shape!==null) {
                    $this->checkShape($shape);
                    $size = (int)array_product($shape);
                    $buffer = $this->newBuffer($size,$dtype);
                    $offset = 0;
                } else {
                    var_dump($array);var_dump($shape);
                    throw new \Exception("Illegal array type");
                }
                $this->buffer = $buffer;
                $this->size = $buffer->count();
                $this->dtype = $buffer->dtype();
                $this->shape = $shape;
                $this->offset = $offset;
            }

            function newBuffer($size,$dtype) : object
            {
                return $this->service->hostBufferFactory()->Buffer($size,$dtype);
            }
            
            protected function isComplex($dtype=null) : bool
            {
                $dtype = $dtype ?? $this->_dtype;
                return $dtype==NDArray::complex64||$dtype==NDArray::complex128;
            }

            protected function array2Flat($A, $F, &$idx, $prepare)
            {
                if(is_array($A)) {
                    ksort($A);
                } elseif($A instanceof ArrayObject) {
                    $A->ksort();
                }
        
                $num = null;
                foreach ($A as $key => $value) {
                    if(!is_int($key))
                        throw new InvalidArgumentException("Dimension must be integer");
                    if(is_array($value)||$value instanceof ArrayObject) {
                        $num2 = $this->array2Flat($value, $F, $idx, $prepare);
                        if($num===null) {
                            $num = $num2;
                        } else {
                            if($num!=$num2)
                                throw new InvalidArgumentException("The shape of the dimension is broken");
                        }
                    } else {
                        if($num!==null)
                            throw new InvalidArgumentException("The shape of the dimension is broken");
                        if(!$prepare)
                            $F[$idx] = $value;
                        $idx++;
                    }
                }
                return count($A);
            }

            protected function flat2Array($F, &$idx, array $shape)
            {
                $size = array_shift($shape);
                if(count($shape)) {
                    $A = [];
                    for($i=0; $i<$size; $i++) {
                        $A[$i] = $this->flat2Array($F,$idx,$shape);
                    }
                }  else {
                    $A = [];
                    if($this->isComplex($this->dtype)) {
                        for($i=0; $i<$size; $i++) {
                            $v = $F[$idx];
                            $A[$i] = C($v->real,$v->imag);
                            $idx++;
                        }
                    } else {
                        for($i=0; $i<$size; $i++) {
                            $A[$i] = $F[$idx];
                            $idx++;
                        }
                    }
                }
                return $A;
            }
                
            protected function genShape($A)
            {
                $shape = [];
                while(is_array($A) || $A instanceof ArrayObject) {
                    $shape[] = count($A);
                    $A = $A[0];
                }
                return $shape;
            }
        
            protected function checkShape(array $shape)
            {
                foreach($shape as $num) {
                    if(!is_int($num)) {
                        throw new InvalidArgumentException(
                            "Invalid shape numbers. It gives ".gettype($num));
                    }
                    if($num<=0) {
                        throw new InvalidArgumentException(
                            "Invalid shape numbers. It gives ".$num);
                    }
                }
            }

            public function toArray()
            {
                if(count($this->shape)==0) {
                    $v = $this->buffer[$this->offset];
                    if($this->isComplex($this->dtype)) {
                        $v = C($v->real,$v->imag);
                    }
                    return $v;
                }
                $idx = $this->offset;
                return $this->flat2Array($this->buffer, $idx, $this->shape);
            }

            public function shape() : array { return $this->shape; }

            public function ndim() : int { return count($this->shape); }
        
            public function dtype() { return $this->dtype; }
        
            public function buffer() : ArrayAccess { return $this->buffer; }
        
            public function offset() : int { return $this->offset; }
        
            public function size() : int { return $this->buffer->count(); }
        
            public function reshape(array $shape) : NDArray
            {
                if(array_product($shape)==array_product($this->shape)) {
                    $this->shape = $shape;
                } else {
                    throw new \Exception("unmatch shape");
                }
                return $this;
            }
            public function offsetExists( $offset ) : bool { throw new \Excpetion('not implement'); }
            public function offsetGet( $offset ) : mixed { throw new \Excpetion('not implement'); }
            public function offsetSet( $offset , $value ) : void { throw new \Excpetion('not implement'); }
            public function offsetUnset( $offset ) : void { throw new \Excpetion('not implement'); }
            public function count() : int  { throw new \Excpetion('not implement'); }
            public function  getIterator() : Traversable  { throw new \Excpetion('not implement'); }
        };
        return $ndarray;
    }

    public function alloc(array $shape,?int $dtype=null, ?int $flags=null)
    {
        $ndarray = $this->hostArray(null,dtype:$dtype,shape:$shape);
        return $this->array($ndarray, dtype:$dtype, flags:$flags);
    }

    public function zeros(array $shape,?int $dtype=null, ?int $flags=null)
    {
        $ndarray = $this->hostArray(null,dtype:$dtype,shape:$shape);
        return $this->array($ndarray, dtype:$dtype, flags:$flags);
    }

    public function zerosLike(NDArray $x,?int $dtype=null, ?int $flags=null)
    {
        // argument $dtype is dummy
        return $this->zeros($x->shape(),dtype:$x->dtype(), flags:$flags);
    }

    public function ones(array $shape, ?int $dtype=null, ?int $flags=null)
    {
        $ndarray = $this->hostArray(null,dtype:$dtype,shape:$shape);
        $buffer = $ndarray->buffer();
        $dtype = $ndarray->dtype();
        $value = 1;
        if($this->isComplex($dtype)) {
            $value = $this->toComplex($value);
        }
        $size = count($buffer);
        for($i=0;$i<$size;++$i) {
            $buffer[$i] = $value;
        }
        return $this->array($ndarray, dtype:$dtype, flags:$flags);
    }

    public function full(array $shape, mixed $value ,?int $dtype=null, ?int $flags=null)
    {
        $ndarray = $this->hostArray(null,dtype:$dtype,shape:$shape);
        $buffer = $ndarray->buffer();
        $size = count($buffer);
        for($i=0;$i<$size;++$i) {
            $buffer[$i] = $value;
        }
        return $this->array($ndarray, dtype:$dtype, flags:$flags);
    }

    public function isComplex($dtype) : bool
    {
        return $dtype==NDArray::complex64||$dtype==NDArray::complex128;
    }

    public function toComplex(mixed $array) : mixed
    {
        if(!is_array($array)) {
            if(is_numeric($array)) {
                return C($array,i:0);
            } else {
                return C($array->real,i:$array->imag);
            }
        }
        $cArray = [];
        foreach($array as $value) {
            $cArray[] = $this->toComplex($value);
        }
        return $cArray;
    }

    protected function buildValByType(float|int $value, int $dtype) : float|int|object
    {
        if($this->isComplex($dtype)) {
            $value = $this->toComplex($value);
        }
        return $value;
    }

    protected function complementTrans(?bool $trans,?bool $conj,int $dtype) : array
    {
        $trans = $trans ?? false;
        if($this->isComplex($dtype)) {
            $conj = $conj ?? $trans;
        } else {
            $conj = $conj ?? false;
        }
        return [$trans,$conj];
    }

    protected function transToCode(bool $trans,bool $conj) : int
    {
        if($trans) {
            return $conj ? BLAS::ConjTrans : BLAS::Trans;
        } else {
            return $conj ? BLAS::ConjNoTrans : BLAS::NoTrans;
        }
    }

    protected function abs(float|int|object $value) : float
    {
        if(is_numeric($value)) {
            return abs($value);
        }
        $abs = sqrt(($value->real)**2+($value->imag)**2);
        return $abs;
    }

    protected function copy(NDArray $x,?NDArray $y=null) : NDArray
    {
        $blas = $this->getBlas();

        if($y==null) {
            $y = $this->zeros($x->shape(),dtype:$x->dtype());
        }
        [$N,$XX,$offX,$incX,$YY,$offY,$incY,$queue,$events] = $this->translate_copy($x,$y);
        $blas->copy($N,$XX,$offX,$incX,$YY,$offY,$incY,$queue,$events);
        $events->wait();
        return $y;
    }

    protected function isclose(NDArray $a, NDArray $b, ?float $rtol=null, ?float $atol=null) : bool
    {
        $blas = $this->getBlas();

        $isCpx = $this->isComplex($a->dtype());
        if($rtol===null) {
            $rtol = $isCpx?C(1e-04):1e-04;
        }
        if($atol===null) {
            $atol = 1e-07;
        }
        if($a->shape()!=$b->shape()) {
            return false;
        }
        // diff = b - a
        $alpha =  $isCpx?C(-1):-1;
        $diffs = $this->copy($b);
        $blas->axpy(...$this->translate_axpy($a,$diffs,$alpha));
        $iDiffMax = $this->zeros([],dtype:NDArray::int32);
        $blas->iamax(...$this->translate_amin($diffs,output:$iDiffMax));
        $diff = $this->abs($diffs->toNDArray()->buffer()[$iDiffMax->toArray()]);

        // close = atol + rtol * b
        $scalB = $this->copy($b);
        $blas->scal(...$this->translate_scal($rtol,$scalB));
        $iCloseMax = $this->zeros([],dtype:NDArray::int32);
        $blas->iamax(...$this->translate_amin($scalB,output:$iCloseMax));
        $close = $atol+$this->abs($scalB->toNDArray()->buffer()[$iCloseMax->toArray()]);

        return $diff < $close;
    }

    public function NDArrayCL(
        object $queue, mixed $buffer=null, ?int $dtype=null, ?array $shape = null,
        ?int $offset=null, ?int $flags=null,
        ?object $service=null        
    ) : NDArray
    {
        $arrayCL = new class (
            $queue, buffer:$buffer, dtype:$dtype, shape:$shape,
            offset:$offset, flags:$flags,
            service:$service
        ) implements NDArray {
            static protected $valueSizeTable = [
                NDArray::bool  => 1,
                NDArray::int8  => 1,
                NDArray::int16 => 2,
                NDArray::int32 => 4,
                NDArray::int64 => 8,
                NDArray::uint8 => 1,
                NDArray::uint16 => 2,
                NDArray::uint32 => 4,
                NDArray::uint64 => 8,
                NDArray::float8 => 1,
                NDArray::float16 => 2,
                NDArray::float32 => 4,
                NDArray::float64 => 8,
                NDArray::complex16 => 2,
                NDArray::complex32 => 4,
                NDArray::complex64 => 8,
                NDArray::complex128 => 16,
            ];
            protected object $buffer;
            protected int $size;
            protected int $dtype;
            protected int $offset;
            protected array $shape;
            protected int $flags;
            protected object $service;
            protected object $context;
            protected object $queue;
            public function __construct(
                object $queue, mixed $buffer=null, ?int $dtype=null, ?array $shape = null,
                ?int $offset=null, ?int $flags=null,
                ?object $service=null)
            {
                if($service===null) {
                    throw new InvalidArgumentException("No service specified.");
                }
                $this->service = $service;
                //$this->clBufferFactory = $service->buffer(Service::LV_ACCELERATED);
                $context = $queue->getContext();
                $this->context = $context; 
                $this->queue = $queue;
                if($dtype===null) {
                    $dtype = NDArray::float32;
                } else {
                    $dtype = $dtype;
                }
                if($offset===null) {
                    $offset = 0;
                }
                if($flags===null) {
                    $flags = OpenCL::CL_MEM_READ_WRITE;
                }
        
                $this->assertShape($shape);
                $this->shape = $shape;
                $this->flags = $flags;
                $size = (int)array_product($shape);
                if($buffer instanceof DeviceBuffer) {
                    if($buffer->bytes()
                        < ($size + $offset)*static::$valueSizeTable[$dtype]) {
                        throw new InvalidArgumentException("Invalid dimension size");
                    }
                    $this->dtype  = $dtype;
                    $this->buffer = $buffer;
                    $this->offset = $offset;
                } elseif($buffer===null) {
                    $size = (int)array_product($shape);
                    $this->buffer = $this->newBuffer($context,$size,$dtype,$flags);
                    $this->dtype  = $dtype;
                    $this->offset = 0;
                } elseif($buffer instanceof LinearBuffer) {
                    if($offset===null||!is_int($offset)) {
                        throw new InvalidArgumentException("Must specify offset with the buffer");
                    }
                    $size = (int)array_product($shape);
                    if($size > count($buffer)-$offset) {
                        throw new InvalidArgumentException("host buffer is too small");
                    }
                    $this->buffer = $this->newBuffer($context,
                            $size, $buffer->dtype(), $flags,
                            $buffer, $offset);
                    $this->dtype = $buffer->dtype();
                    $this->offset = 0;
                } else {
                    if(is_object($buffer)) {
                        $typename = get_class($buffer);
                    } else {
                        $typename = gettype($buffer);
                    }
                    throw new InvalidArgumentException("Invalid type of array: ".$typename);
                }
            }
        
            protected function newBuffer(
                object $context, int $size, int $dtype, int $flags=0,
                ?object $hostBuffer=null, int $hostOffset=0)
            {
                //if(!extension_loaded('rindow_opencl')) {
                //    throw new LogicException("rindow_opencl extension is not loaded.");
                //}
                //return new OpenCLBuffer($context,static::$valueSizeTable[$dtype]*$size,
                //    $flags,$hostBuffer,$hostOffset,$dtype);
                $bytes = static::$valueSizeTable[$dtype]*$size;
                return $this->service->getOpenCL()->Buffer($context,$bytes,
                    $flags,$hostBuffer,$hostOffset,$dtype);
            }
        
            protected function assertShape(array $shape)
            {
                foreach($shape as $num) {
                    if(!is_int($num)) {
                        throw new InvalidArgumentException(
                            "Invalid shape numbers. It gives ".gettype($num));
                    }
                    if($num<=0) {
                        throw new InvalidArgumentException(
                            "Invalid shape numbers. It gives ".$num);
                    }
                }
            }
        
            public function shape() : array
            {
                return $this->shape;
            }
        
            public function ndim() : int
            {
                return count($this->shape);
            }
        
            public function dtype()
            {
                return $this->dtype;
            }
        
            public function flags()
            {
                return $this->flags;
            }
        
            public function buffer() : ArrayAccess
            {
                return $this->buffer;
            }
        
            public function offset() : int
            {
                return $this->offset;
            }
        
            public function valueSize() : int
            {
                return static::$valueSizeTable[$this->dtype];
            }
        
            public function size() : int
            {
                return (int)array_product($this->shape);
            }
        
            public function reshape(array $shape) : NDArray
            {
                $this->assertShape($shape);
                if($this->size()!=array_product($shape)) {
                    throw new InvalidArgumentException("Unmatch size to reshape: ".
                        "[".implode(',',$this->shape())."]=>[".implode(',',$shape)."]");
                }
                $newArray = new static($this->queue,$this->buffer,
                    $this->dtype,$shape,$this->offset,$this->flags, service:$this->service);
                return $newArray;
            }
        
            public function toArray()
            {
                $ndarray = $this->toNDArray();
                $array = $ndarray->toArray();
                return $array;
            }
        
            public function toNDArray(
                ?bool $blocking_read=null,?EventList $waitEvents=null,
                ?EventList &$events=null) : NDArray
            {
                $blocking_read = $blocking_read ?? true;
                $array = $this->service->hostArray(null,dtype:$this->dtype,shape:$this->shape);
                $valueSize = static::$valueSizeTable[$this->dtype];
                $size = array_product($this->shape);
                $bytes = $size*$valueSize; 
                $this->buffer->read(
                    $this->queue,
                    $array->buffer(),
                    size:$bytes,
                    offset:$this->offset*$valueSize,
                    host_offset:0,
                    blocking_read:$blocking_read,
                    events:$events,
                    wait_events:$waitEvents,
                );
                return $array;
            }
            public function offsetExists( $offset ) : bool { throw new \Excpetion('not implement'); }
            public function offsetGet( $offset ) : mixed { throw new \Excpetion('not implement'); }
            public function offsetSet( $offset , $value ) : void { throw new \Excpetion('not implement'); }
            public function offsetUnset( $offset ) : void { throw new \Excpetion('not implement'); }
            public function count() : int  { throw new \Excpetion('not implement'); }
            public function  getIterator() : Traversable  { throw new \Excpetion('not implement'); }
        };

        return $arrayCL;
    }

    public function array(mixed $array, ?int $dtype=null, ?int $flags=null) : NDArray
    {
        if($array instanceof NDArray) {
            $buffer = $array->buffer();
            if($buffer instanceof LinearBuffer) {
                ;
            } elseif($buffer instanceof DeviceBuffer) {
                return $array;
            } else {
                throw new InvalidArgumentException('Unsuppored buffer type.');
            }
        } elseif(is_array($array) || is_numeric($array)) {
            $array = $this->hostArray($array,dtype:$dtype);
        } else {
            throw new InvalidArgumentException('input value must be NDArray or array');
        }
        if($flags==null) {
            $flags = OpenCL::CL_MEM_READ_WRITE;
        }
        $flags = $flags | OpenCL::CL_MEM_COPY_HOST_PTR;

        $arrayCL = $this->NDArrayCL(
            $this->queue,
            buffer:$array->buffer(), dtype:$array->dtype(), shape:$array->shape(),
            offset:$array->offset(), flags:$flags, service:$this
        );
        return $arrayCL;
    }
}