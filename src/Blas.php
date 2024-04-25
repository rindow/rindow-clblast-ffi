<?php
namespace Rindow\CLBlast\FFI;

use Interop\Polite\Math\Matrix\NDArray;
use Interop\Polite\Math\Matrix\BLAS as BLASIF;
use InvalidArgumentException;
use RuntimeException;
use FFI;
use Rindow\OpenCL\FFI\Buffer as DeviceBuffer;
use Rindow\OpenCL\FFI\CommandQueue;
use Rindow\OpenCL\FFI\EventList;


class Blas
{
    use Utils;

    const CLBlastSuccess = 0;
    const CLBlastNotImplemented = -1024;
    protected FFI $ffi;
    protected object $alt;

    public function __construct(FFI $ffi, object $alt)
    {
        $this->ffi = $ffi;
        $this->alt = $alt;
    }

    /**
     *  X := alpha * X
     */
    public function scal(
        int $n,
        float|object $alpha,
        DeviceBuffer $X, int $offsetX, int $incX,
        CommandQueue $queue,// Rindow\OpenCL\CommandQueue
        EventList $event=null,   // Rindow\OpenCL\EventList
        ) : void
    {
        $ffi = $this->ffi;
        $alt = $this->alt;
        $buffer_p = $ffi->cast("cl_mem",$X->_getId());
        $queue_p = $ffi->cast("cl_command_queue*",FFI::addr($queue->_getId()));
        $event_p = null;
        if($event) {
            $event_obj = $event->_ffi()->new("cl_event[1]");
            $event_p = $ffi->cast("cl_event[1]",$event_obj);
        }
        switch($X->dtype()) {
            case NDArray::float32:{
                $status = $ffi->CLBlastSscal(
                    $n,$alpha,
                    $buffer_p,$offsetX,$incX,
                    $queue_p,$event_p);
                break;
            }
            case NDArray::float64:{
                $status = $ffi->CLBlastDscal(
                    $n,$alpha,
                    $buffer_p,$offsetX,$incX,
                    $queue_p,$event_p);
                break;
            }
            case NDArray::complex64:{
                $alpha = $this->toComplex($alpha,$X->dtype());
                $status = $alt->CLBlastCscal(
                    $n,$alpha,
                    $buffer_p,$offsetX,$incX,
                    $queue_p,$event_p);
                break;
            }
            case NDArray::complex128:{
                $alpha = $this->toComplex($alpha,$X->dtype());
                $status = $alt->CLBlastZscal(
                    $n,$alpha,
                    $buffer_p,$offsetX,$incX,
                    $queue_p,$event_p);
                break;
            }
            default: {
                throw new InvalidArgumentException('Unsuppored data type');
            }
        }
        if($status!=self::CLBlastSuccess) {
            throw new RuntimeException("CLBlast?scal error=$status", $status);
        }
    
        if($event) {
            $event->_move($event_obj);
        }
    }

    /**
     *  Y := alpha * X + Y
     */
    public function axpy(
        int $n,
        float|object $alpha,
        DeviceBuffer $X, int $offsetX, int $incX,
        DeviceBuffer $Y, int $offsetY, int $incY,
        CommandQueue $queue,// Rindow\OpenCL\CommandQueue
        EventList $event=null,   // Rindow\OpenCL\EventList
        ) : void
    {
        $ffi = $this->ffi;
        $alt = $this->alt;
        // Check Buffer X and Y
        if($X->dtype()!=$Y->dtype()) {
            throw new InvalidArgumentException("Unmatch data type for X and Y");
        }
        $bufferX_p = $ffi->cast("cl_mem",$X->_getId());
        $bufferY_p = $ffi->cast("cl_mem",$Y->_getId());
        $queue_p = $ffi->cast("cl_command_queue*",FFI::addr($queue->_getId()));
        $event_p = null;
        if($event) {
            $event_obj = $event->_ffi()->new("cl_event[1]");
            $event_p = $ffi->cast("cl_event[1]",$event_obj);
        }

        switch($X->dtype()) {
            case NDArray::float32:{
                $status = $ffi->CLBlastSaxpy($n,$alpha,
                    $bufferX_p,$offsetX,$incX,
                    $bufferY_p,$offsetY,$incY,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::float64:{
                $status = $ffi->CLBlastDaxpy($n,$alpha,
                    $bufferX_p,$offsetX,$incX,
                    $bufferY_p,$offsetY,$incY,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::complex64:{
                $alpha = $this->toComplex($alpha,$X->dtype());
                $status = $alt->CLBlastCaxpy($n,$alpha,
                    $bufferX_p,$offsetX,$incX,
                    $bufferY_p,$offsetY,$incY,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::complex128:{
                $alpha = $this->toComplex($alpha,$X->dtype());
                $status = $alt->CLBlastZaxpy($n,$alpha,
                    $bufferX_p,$offsetX,$incX,
                    $bufferY_p,$offsetY,$incY,
                    $queue_p,$event_p
                );
                break;
            }
            default: {
                throw new InvalidArgumentException('Unsuppored data type');
            }
        }
        if($status!=self::CLBlastSuccess) {
            throw new RuntimeException("CLBlast?axpy error=$status", $status);
        }
        if($event) {
            $event->_move($event_obj);
        }
    }

    public function dot(
        int $n,
        DeviceBuffer $R, int $offsetR,
        DeviceBuffer $X, int $offsetX, int $incX,
        DeviceBuffer $Y, int $offsetY, int $incY,
        CommandQueue $queue,// Rindow\OpenCL\CommandQueue
        EventList $event=null,   // Rindow\OpenCL\EventList
        ) : void
    {
        $ffi = $this->ffi;
        // Check Buffer X and Y
        if($X->dtype()!=$Y->dtype()) {
            throw new InvalidArgumentException("Unmatch data type for X and Y");
        }
        if($R->dtype()!=0 && $X->dtype()!=$R->dtype()) {
            throw new InvalidArgumentException("Unmatch data type for X and R");
        }
        $bufferR_p = $ffi->cast("cl_mem",$R->_getId());
        $bufferX_p = $ffi->cast("cl_mem",$X->_getId());
        $bufferY_p = $ffi->cast("cl_mem",$Y->_getId());
        $queue_p = $ffi->cast("cl_command_queue*",FFI::addr($queue->_getId()));
        $event_p = null;
        if($event) {
            $event_obj = $event->_ffi()->new("cl_event[1]");
            $event_p = $ffi->cast("cl_event[1]",$event_obj);
        }

        switch($X->dtype()) {
            case NDArray::float32:{
                $status = $ffi->CLBlastSdot($n,
                    $bufferR_p,$offsetR,
                    $bufferX_p,$offsetX,$incX,
                    $bufferY_p,$offsetY,$incY,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::float64:{
                $status = $ffi->CLBlastDdot($n,
                    $bufferR_p,$offsetR,
                    $bufferX_p,$offsetX,$incX,
                    $bufferY_p,$offsetY,$incY,
                    $queue_p,$event_p
                );
                break;
            }
            default: {
                throw new InvalidArgumentException('Unsuppored data type');
            }
        }
        if($status!=self::CLBlastSuccess) {
            throw new RuntimeException("CLBlast?dot error=$status", $status);
        }
        if($event) {
            $event->_move($event_obj);
        }
    }

    public function dotc(
        int $n,
        DeviceBuffer $R, int $offsetR,
        DeviceBuffer $X, int $offsetX, int $incX,
        DeviceBuffer $Y, int $offsetY, int $incY,
        CommandQueue $queue,// Rindow\OpenCL\CommandQueue
        EventList $event=null,   // Rindow\OpenCL\EventList
        ) : void
    {
        $ffi = $this->ffi;
        // Check Buffer X and Y
        if($X->dtype()!=$Y->dtype()) {
            throw new InvalidArgumentException("Unmatch data type for X and Y");
        }
        if($R->dtype()!=0 && $X->dtype()!=$R->dtype()) {
            throw new InvalidArgumentException("Unmatch data type for X and R");
        }
        $bufferR_p = $ffi->cast("cl_mem",$R->_getId());
        $bufferX_p = $ffi->cast("cl_mem",$X->_getId());
        $bufferY_p = $ffi->cast("cl_mem",$Y->_getId());
        $queue_p = $ffi->cast("cl_command_queue*",FFI::addr($queue->_getId()));
        $event_p = null;
        if($event) {
            $event_obj = $event->_ffi()->new("cl_event[1]");
            $event_p = $ffi->cast("cl_event[1]",$event_obj);
        }

        switch($X->dtype()) {
            case NDArray::complex64:{
                $status = $ffi->CLBlastCdotc($n,
                    $bufferR_p,$offsetR,
                    $bufferX_p,$offsetX,$incX,
                    $bufferY_p,$offsetY,$incY,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::complex128:{
                $status = $ffi->CLBlastZdotc($n,
                    $bufferR_p,$offsetR,
                    $bufferX_p,$offsetX,$incX,
                    $bufferY_p,$offsetY,$incY,
                    $queue_p,$event_p
                );
                break;
            }
            default: {
                throw new InvalidArgumentException('Unsuppored data type');
            }
        }
        if($status!=self::CLBlastSuccess) {
            throw new RuntimeException("CLBlast?dot error=$status", $status);
        }
        if($event) {
            $event->_move($event_obj);
        }
    }

    public function dotu(
        int $n,
        DeviceBuffer $R, int $offsetR,
        DeviceBuffer $X, int $offsetX, int $incX,
        DeviceBuffer $Y, int $offsetY, int $incY,
        CommandQueue $queue,// Rindow\OpenCL\CommandQueue
        EventList $event=null,   // Rindow\OpenCL\EventList
        ) : void
    {
        $ffi = $this->ffi;
        // Check Buffer X and Y
        if($X->dtype()!=$Y->dtype()) {
            throw new InvalidArgumentException("Unmatch data type for X and Y");
        }
        if($R->dtype()!=0 && $X->dtype()!=$R->dtype()) {
            throw new InvalidArgumentException("Unmatch data type for X and R");
        }
        $bufferR_p = $ffi->cast("cl_mem",$R->_getId());
        $bufferX_p = $ffi->cast("cl_mem",$X->_getId());
        $bufferY_p = $ffi->cast("cl_mem",$Y->_getId());
        $queue_p = $ffi->cast("cl_command_queue*",FFI::addr($queue->_getId()));
        $event_p = null;
        if($event) {
            $event_obj = $event->_ffi()->new("cl_event[1]");
            $event_p = $ffi->cast("cl_event[1]",$event_obj);
        }

        switch($X->dtype()) {
            case NDArray::complex64:{
                $status = $ffi->CLBlastCdotu($n,
                    $bufferR_p,$offsetR,
                    $bufferX_p,$offsetX,$incX,
                    $bufferY_p,$offsetY,$incY,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::complex128:{
                $status = $ffi->CLBlastZdotu($n,
                    $bufferR_p,$offsetR,
                    $bufferX_p,$offsetX,$incX,
                    $bufferY_p,$offsetY,$incY,
                    $queue_p,$event_p
                );
                break;
            }
            default: {
                throw new InvalidArgumentException('Unsuppored data type');
            }
        }
        if($status!=self::CLBlastSuccess) {
            throw new RuntimeException("CLBlast?dot error=$status", $status);
        }
        if($event) {
            $event->_move($event_obj);
        }
    }

    public function asum(
        int $n,
        DeviceBuffer $R, int $offsetR,
        DeviceBuffer $X, int $offsetX, int $incX,
        CommandQueue $queue,
        EventList $event=null
    ) : void
    {
        $ffi = $this->ffi;
        // Check Buffer X and R
        if($R->dtype()!=0 && $X->dtype()!=$R->dtype()) {
            throw new InvalidArgumentException("Unmatch data type for X and R");
        }
        $bufferR_p = $ffi->cast("cl_mem",$R->_getId());
        $bufferX_p = $ffi->cast("cl_mem",$X->_getId());
        $queue_p = $ffi->cast("cl_command_queue*",FFI::addr($queue->_getId()));
        $event_p = null;
        if($event) {
            $event_obj = $event->_ffi()->new("cl_event[1]");
            $event_p = $ffi->cast("cl_event[1]",$event_obj);
        }

        switch($X->dtype()) {
            case NDArray::float32:{
                $status = $ffi->CLBlastSasum($n,
                    $bufferR_p,$offsetR,
                    $bufferX_p,$offsetX,$incX,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::float64:{
                $status = $ffi->CLBlastDasum($n,
                    $bufferR_p,$offsetR,
                    $bufferX_p,$offsetX,$incX,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::complex64:{
                $status = $ffi->CLBlastScasum($n,
                    $bufferR_p,$offsetR,
                    $bufferX_p,$offsetX,$incX,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::complex128:{
                $status = $ffi->CLBlastDzasum($n,
                    $bufferR_p,$offsetR,
                    $bufferX_p,$offsetX,$incX,
                    $queue_p,$event_p
                );
                break;
            }
            default: {
                throw new InvalidArgumentException('Unsuppored data type');
            }
        }
        if($status!=self::CLBlastSuccess) {
            throw new RuntimeException("CLBlast?asum error=$status", $status);
        }
        if($event) {
            $event->_move($event_obj);
        }
    }

    public function iamax(
        int $n,
        DeviceBuffer $R, int $offsetR,
        DeviceBuffer $X, int $offsetX, int $incX,
        CommandQueue $queue,
        EventList $event=null
    ) : void
    {
        $ffi = $this->ffi;
        $bufferR_p = $ffi->cast("cl_mem",$R->_getId());
        $bufferX_p = $ffi->cast("cl_mem",$X->_getId());
        $queue_p = $ffi->cast("cl_command_queue*",FFI::addr($queue->_getId()));
        $event_p = null;
        if($event) {
            $event_obj = $event->_ffi()->new("cl_event[1]");
            $event_p = $ffi->cast("cl_event[1]",$event_obj);
        }

        switch($X->dtype()) {
            case NDArray::float32:{
                $status = $ffi->CLBlastiSamax($n,
                    $bufferR_p,$offsetR,
                    $bufferX_p,$offsetX,$incX,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::float64:{
                $status = $ffi->CLBlastiDamax($n,
                    $bufferR_p,$offsetR,
                    $bufferX_p,$offsetX,$incX,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::complex64:{
                $status = $ffi->CLBlastiCamax($n,
                    $bufferR_p,$offsetR,
                    $bufferX_p,$offsetX,$incX,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::complex128:{
                $status = $ffi->CLBlastiZamax($n,
                    $bufferR_p,$offsetR,
                    $bufferX_p,$offsetX,$incX,
                    $queue_p,$event_p
                );
                break;
            }
            default: {
                throw new InvalidArgumentException('Unsuppored data type');
            }
        }
        if($status!=self::CLBlastSuccess) {
            throw new RuntimeException("CLBlast?iamax error=$status", $status);
        }
        if($event) {
            $event->_move($event_obj);
        }
    }

    public function iamin(
        int $n,
        DeviceBuffer $R, int $offsetR,
        DeviceBuffer $X, int $offsetX, int $incX,
        CommandQueue $queue,
        EventList $event=null
    ) : void
    {
        $ffi = $this->ffi;
        $bufferR_p = $ffi->cast("cl_mem",$R->_getId());
        $bufferX_p = $ffi->cast("cl_mem",$X->_getId());
        $queue_p = $ffi->cast("cl_command_queue*",FFI::addr($queue->_getId()));
        $event_p = null;
        if($event) {
            $event_obj = $event->_ffi()->new("cl_event[1]");
            $event_p = $ffi->cast("cl_event[1]",$event_obj);
        }

        switch($X->dtype()) {
            case NDArray::float32:{
                $status = $ffi->CLBlastiSamin($n,
                    $bufferR_p,$offsetR,
                    $bufferX_p,$offsetX,$incX,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::float64:{
                $status = $ffi->CLBlastiDamin($n,
                    $bufferR_p,$offsetR,
                    $bufferX_p,$offsetX,$incX,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::complex64:{
                $status = $ffi->CLBlastiCamin($n,
                    $bufferR_p,$offsetR,
                    $bufferX_p,$offsetX,$incX,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::complex128:{
                $status = $ffi->CLBlastiZamin($n,
                    $bufferR_p,$offsetR,
                    $bufferX_p,$offsetX,$incX,
                    $queue_p,$event_p
                );
                break;
            }
            default: {
                throw new InvalidArgumentException('Unsuppored data type');
            }
        }
        if($status!=self::CLBlastSuccess) {
            throw new RuntimeException("CLBlast?iamin error=$status", $status);
        }
        if($event) {
            $event->_move($event_obj);
        }
    }

    public function copy(
        int $n,
        DeviceBuffer $X, int $offsetX, int $incX,
        DeviceBuffer $Y, int $offsetY, int $incY,
        CommandQueue $queue,// Rindow\OpenCL\CommandQueue
        EventList $event=null,   // Rindow\OpenCL\EventList
        ) : void
    {
        $ffi = $this->ffi;
        // Check Buffer X and Y
        if($X->dtype()!=$Y->dtype()) {
            throw new InvalidArgumentException("Unmatch data type for X and Y");
        }
        $bufferX_p = $ffi->cast("cl_mem",$X->_getId());
        $bufferY_p = $ffi->cast("cl_mem",$Y->_getId());
        $queue_p = $ffi->cast("cl_command_queue*",FFI::addr($queue->_getId()));
        $event_p = null;
        if($event) {
            $event_obj = $event->_ffi()->new("cl_event[1]");
            $event_p = $ffi->cast("cl_event[1]",$event_obj);
        }

        switch($X->dtype()) {
            case NDArray::float32:{
                $status = $ffi->CLBlastScopy($n,
                    $bufferX_p,$offsetX,$incX,
                    $bufferY_p,$offsetY,$incY,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::float64:{
                $status = $ffi->CLBlastDcopy($n,
                    $bufferX_p,$offsetX,$incX,
                    $bufferY_p,$offsetY,$incY,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::complex64:{
                $status = $ffi->CLBlastCcopy($n,
                    $bufferX_p,$offsetX,$incX,
                    $bufferY_p,$offsetY,$incY,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::complex128:{
                $status = $ffi->CLBlastZcopy($n,
                    $bufferX_p,$offsetX,$incX,
                    $bufferY_p,$offsetY,$incY,
                    $queue_p,$event_p
                );
                break;
            }
            default: {
                if($incX!=1||$incY!=1) {
                    throw new InvalidArgumentException("clEnqueueCopyBuffer not supports incX and incY.");
                }
                $value_size = $X->value_size();
                $bytes = $value_size*$n;
                $src_offset = $value_size*$offsetX;
                $dst_offset = $value_size*$offsetY;
                try {
                    $Y->copy($queue,$X,$bytes,$src_offset,$dst_offset,$event);
                } catch(RuntimeException $e) {
                    $status = $e->getCode();
                    throw new RuntimeException("CLBlast?copy error=$status", $status, $e);
                }
                // skip to move raw event 
                return;
            }
        }
        if($status!=self::CLBlastSuccess) {
            throw new RuntimeException("CLBlast?copy error=$status", $status);
        }
        if($event) {
            $event->_move($event_obj);
        }
    }

    public function nrm2(
        int $n,
        DeviceBuffer $R, int $offsetR,
        DeviceBuffer $X, int $offsetX, int $incX,
        CommandQueue $queue,
        EventList $event=null
    ) : void
    {
        $ffi = $this->ffi;
        // Check Buffer X and R
        if($R->dtype()!=0 && $X->dtype()!=$R->dtype()) {
            throw new InvalidArgumentException("Unmatch data type for X and R");
        }
        $bufferR_p = $ffi->cast("cl_mem",$R->_getId());
        $bufferX_p = $ffi->cast("cl_mem",$X->_getId());
        $queue_p = $ffi->cast("cl_command_queue*",FFI::addr($queue->_getId()));
        $event_p = null;
        if($event) {
            $event_obj = $event->_ffi()->new("cl_event[1]");
            $event_p = $ffi->cast("cl_event[1]",$event_obj);
        }

        switch($X->dtype()) {
            case NDArray::float32:{
                $status = $ffi->CLBlastSnrm2($n,
                    $bufferR_p,$offsetR,
                    $bufferX_p,$offsetX,$incX,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::float64:{
                $status = $ffi->CLBlastDnrm2($n,
                    $bufferR_p,$offsetR,
                    $bufferX_p,$offsetX,$incX,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::complex64:{
                $status = $ffi->CLBlastScnrm2($n,
                    $bufferR_p,$offsetR,
                    $bufferX_p,$offsetX,$incX,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::complex128:{
                $status = $ffi->CLBlastDznrm2($n,
                    $bufferR_p,$offsetR,
                    $bufferX_p,$offsetX,$incX,
                    $queue_p,$event_p
                );
                break;
            }
            default: {
                throw new InvalidArgumentException('Unsuppored data type');
            }
        }
        if($status!=self::CLBlastSuccess) {
            throw new RuntimeException("CLBlast?iamin error=$status", $status);
        }
        if($event) {
            $event->_move($event_obj);
        }
    }

    public function swap(
        int $n,
        DeviceBuffer $X, int $offsetX, int $incX,
        DeviceBuffer $Y, int $offsetY, int $incY,
        CommandQueue $queue,// Rindow\OpenCL\CommandQueue
        EventList $event=null,   // Rindow\OpenCL\EventList
        ) : void
    {
        $ffi = $this->ffi;
        // Check Buffer X and Y
        if($X->dtype()!=$Y->dtype()) {
            throw new InvalidArgumentException("Unmatch data type for X and Y");
        }
        $bufferX_p = $ffi->cast("cl_mem",$X->_getId());
        $bufferY_p = $ffi->cast("cl_mem",$Y->_getId());
        $queue_p = $ffi->cast("cl_command_queue*",FFI::addr($queue->_getId()));
        $event_p = null;
        if($event) {
            $event_obj = $event->_ffi()->new("cl_event[1]");
            $event_p = $ffi->cast("cl_event[1]",$event_obj);
        }

        switch($X->dtype()) {
            case NDArray::float32:{
                $status = $ffi->CLBlastSswap($n,
                    $bufferX_p,$offsetX,$incX,
                    $bufferY_p,$offsetY,$incY,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::float64:{
                $status = $ffi->CLBlastDswap($n,
                    $bufferX_p,$offsetX,$incX,
                    $bufferY_p,$offsetY,$incY,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::complex64:{
                $status = $ffi->CLBlastCswap($n,
                    $bufferX_p,$offsetX,$incX,
                    $bufferY_p,$offsetY,$incY,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::complex128:{
                $status = $ffi->CLBlastZswap($n,
                    $bufferX_p,$offsetX,$incX,
                    $bufferY_p,$offsetY,$incY,
                    $queue_p,$event_p
                );
                break;
            }
            default: {
                throw new InvalidArgumentException('Unsuppored data type');
            }
        }
        if($status!=self::CLBlastSuccess) {
            throw new RuntimeException("CLBlast?copy error=$status", $status);
        }
        if($event) {
            $event->_move($event_obj);
        }
    }

    public function rotg(
        DeviceBuffer $A, int $offsetA,
        DeviceBuffer $B, int $offsetB,
        DeviceBuffer $C, int $offsetC,
        DeviceBuffer $S, int $offsetS,
        CommandQueue $queue,// Rindow\OpenCL\CommandQueue
        EventList $event=null,   // Rindow\OpenCL\EventList
        ) : void
    {
        $ffi= $this->ffi;

        //// Check Buffer A
        //$this->assert_vector_buffer_spec("A", $A, 1, $offsetA, 1);
        //// Check Buffer B
        //$this->assert_vector_buffer_spec("B", $B, 1, $offsetB, 1);
        //// Check Buffer C
        //$this->assert_vector_buffer_spec("C", $C, 1, $offsetC, 1);
        //// Check Buffer S
        //$this->assert_vector_buffer_spec("S", $S, 1, $offsetS, 1);

        // Check Buffer A and B and C and S
        $dtype = $A->dtype();
        if($dtype!=$B->dtype()||$dtype!=$C->dtype()||$dtype!=$S->dtype()) {
            throw new InvalidArgumentException("Unmatch data type for A,B,C and S");
        }
        $bufferA_p = $ffi->cast("cl_mem",$A->_getId());
        $bufferB_p = $ffi->cast("cl_mem",$B->_getId());
        $bufferC_p = $ffi->cast("cl_mem",$C->_getId());
        $bufferS_p = $ffi->cast("cl_mem",$S->_getId());
        $queue_p = $ffi->cast("cl_command_queue*",FFI::addr($queue->_getId()));
        $event_p = null;
        if($event) {
            $event_obj = $event->_ffi()->new("cl_event[1]");
            $event_p = $ffi->cast("cl_event[1]",$event_obj);
        }

        switch($dtype) {
            case NDArray::float32:{
                $status = $ffi->CLBlastSrotg(
                    $bufferA_p,$offsetA,
                    $bufferB_p,$offsetB,
                    $bufferC_p,$offsetC,
                    $bufferS_p,$offsetS,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::float64:{
                $status = $ffi->CLBlastDrotg(
                    $bufferA_p,$offsetA,
                    $bufferB_p,$offsetB,
                    $bufferC_p,$offsetC,
                    $bufferS_p,$offsetS,
                    $queue_p,$event_p
                );
                break;
            }
            default: {
                throw new InvalidArgumentException('Unsuppored data type');
            }
        }
        if($status!=self::CLBlastSuccess) {
            if($status==self::CLBlastNotImplemented) {
                throw new RuntimeException("CLBlast?rotg error=$status: Not Implemented", $status);
            }
            throw new RuntimeException("CLBlast?rotg error=$status", $status);
        }
        if($event) {
            $event->_move($event_obj);
        }
    }

    public function rot(
        int $n,
        DeviceBuffer $X, int $offsetX, int $incX,
        DeviceBuffer $Y, int $offsetY, int $incY,
        float $cos,
        float $sin,
        CommandQueue $queue,// Rindow\OpenCL\CommandQueue
        EventList $event=null,   // Rindow\OpenCL\EventList
        ) : void
    {
        $ffi= $this->ffi;

        // Check Buffer A and B and C and S
        $dtype = $X->dtype();
        if($dtype!=$Y->dtype()) {
            throw new InvalidArgumentException("Unmatch data type for X and Y");
        }
        $bufferX_p = $ffi->cast("cl_mem",$X->_getId());
        $bufferY_p = $ffi->cast("cl_mem",$Y->_getId());
        $queue_p = $ffi->cast("cl_command_queue*",FFI::addr($queue->_getId()));
        $event_p = null;
        if($event) {
            $event_obj = $event->_ffi()->new("cl_event[1]");
            $event_p = $ffi->cast("cl_event[1]",$event_obj);
        }

        switch($dtype) {
            case NDArray::float32:{
                $status = $ffi->CLBlastSrot(
                    $n,
                    $bufferX_p,$offsetX,$incX,
                    $bufferY_p,$offsetY,$incY,
                    $cos,
                    $sin,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::float64:{
                $status = $ffi->CLBlastDrot(
                    $n,
                    $bufferX_p,$offsetX,$incX,
                    $bufferY_p,$offsetY,$incY,
                    $cos,
                    $sin,
                    $queue_p,$event_p
                );
                break;
            }
            default: {
                throw new InvalidArgumentException('Unsuppored data type');
            }
        }
        if($status!=self::CLBlastSuccess) {
            if($status==self::CLBlastNotImplemented) {
                throw new RuntimeException("CLBlast?rot error=$status: Not Implemented", $status);
            }
            throw new RuntimeException("CLBlast?rot error=$status", $status);
        }
        if($event) {
            $event->_move($event_obj);
        }
    }

    public function rotmg(
        DeviceBuffer $D1, int $offsetD1,
        DeviceBuffer $D2, int $offsetD2,
        DeviceBuffer $B1, int $offsetB1,
        DeviceBuffer $B2, int $offsetB2,
        DeviceBuffer $P,  int $offsetP,
        CommandQueue $queue,// Rindow\OpenCL\CommandQueue
        EventList $event=null,   // Rindow\OpenCL\EventList
        ) : void
    {
        $ffi= $this->ffi;

        //// Check Buffer A
        //$this->assert_vector_buffer_spec("A", $A, 1, $offsetA, 1);
        //// Check Buffer B
        //$this->assert_vector_buffer_spec("B", $B, 1, $offsetB, 1);
        //// Check Buffer C
        //$this->assert_vector_buffer_spec("C", $C, 1, $offsetC, 1);
        //// Check Buffer S
        //$this->assert_vector_buffer_spec("S", $S, 1, $offsetS, 1);

        // Check Buffer A and B and C and S
        $dtype = $D1->dtype();
        if($dtype!=$D2->dtype()||$dtype!=$B1->dtype()
            ||$dtype!=$B2->dtype()||$dtype!=$P->dtype()) {
            throw new InvalidArgumentException("Unmatch data type for A,B,C and S");
        }
        $bufferD1_p = $ffi->cast("cl_mem",$D1->_getId());
        $bufferD2_p = $ffi->cast("cl_mem",$D2->_getId());
        $bufferB1_p = $ffi->cast("cl_mem",$B1->_getId());
        $bufferB2_p = $ffi->cast("cl_mem",$B2->_getId());
        $bufferP_p = $ffi->cast("cl_mem",$P->_getId());
        $queue_p = $ffi->cast("cl_command_queue*",FFI::addr($queue->_getId()));
        $event_p = null;
        if($event) {
            $event_obj = $event->_ffi()->new("cl_event[1]");
            $event_p = $ffi->cast("cl_event[1]",$event_obj);
        }

        switch($dtype) {
            case NDArray::float32:{
                $status = $ffi->CLBlastSrotmg(
                    $bufferD1_p,$offsetD1,
                    $bufferD2_p,$offsetD2,
                    $bufferB1_p,$offsetB1,
                    $bufferB2_p,$offsetB2,
                    $bufferP_p,$offsetP,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::float64:{
                $status = $ffi->CLBlastDrotmg(
                    $bufferD1_p,$offsetD1,
                    $bufferD2_p,$offsetD2,
                    $bufferB1_p,$offsetB1,
                    $bufferB2_p,$offsetB2,
                    $bufferP_p,$offsetP,
                    $queue_p,$event_p
                );
                break;
            }
            default: {
                throw new InvalidArgumentException('Unsuppored data type');
            }
        }
        if($status!=self::CLBlastSuccess) {
            if($status==self::CLBlastNotImplemented) {
                throw new RuntimeException("CLBlast?rotmg error=$status: Not Implemented", $status);
            }
            throw new RuntimeException("CLBlast?rotmg error=$status", $status);
        }
        if($event) {
            $event->_move($event_obj);
        }
    }

    public function rotm(
        int $n,
        DeviceBuffer $X, int $offsetX, int $incX,
        DeviceBuffer $Y, int $offsetY, int $incY,
        DeviceBuffer $P, int $offsetP,
        CommandQueue $queue,// Rindow\OpenCL\CommandQueue
        EventList $event=null,   // Rindow\OpenCL\EventList
        ) : void
    {
        $ffi= $this->ffi;

        // Check Buffer A and B and C and S
        $dtype = $X->dtype();
        if($dtype!=$Y->dtype()) {
            throw new InvalidArgumentException("Unmatch data type for X and Y");
        }
        $bufferX_p = $ffi->cast("cl_mem",$X->_getId());
        $bufferY_p = $ffi->cast("cl_mem",$Y->_getId());
        $bufferP_p = $ffi->cast("cl_mem",$P->_getId());
        $queue_p = $ffi->cast("cl_command_queue*",FFI::addr($queue->_getId()));
        $event_p = null;
        if($event) {
            $event_obj = $event->_ffi()->new("cl_event[1]");
            $event_p = $ffi->cast("cl_event[1]",$event_obj);
        }

        switch($dtype) {
            case NDArray::float32:{
                $status = $ffi->CLBlastSrotm(
                    $n,
                    $bufferX_p,$offsetX,$incX,
                    $bufferY_p,$offsetY,$incY,
                    $bufferP_p,$offsetP,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::float64:{
                $status = $ffi->CLBlastDrotm(
                    $n,
                    $bufferX_p,$offsetX,$incX,
                    $bufferY_p,$offsetY,$incY,
                    $bufferP_p,$offsetP,
                    $queue_p,$event_p
                );
                break;
            }
            default: {
                throw new InvalidArgumentException('Unsuppored data type');
            }
        }
        if($status!=self::CLBlastSuccess) {
            if($status==self::CLBlastNotImplemented) {
                throw new RuntimeException("CLBlast?rotm error=$status: Not Implemented", $status);
            }
            throw new RuntimeException("CLBlast?rotm error=$status", $status);
        }
        if($event) {
            $event->_move($event_obj);
        }
    }

    public function gemv(
        int $order,
        int $trans,
        int $m,
        int $n,
        float|object $alpha,
        DeviceBuffer $A, int $offsetA, int $ldA,
        DeviceBuffer $X, int $offsetX, int $incX,
        float|object $beta,
        DeviceBuffer $Y, int $offsetY, int $incY,
        CommandQueue $queue,
        EventList $event=null
    ) : void
    {
        $ffi = $this->ffi;
        $alt = $this->alt;
        // Check Buffer A and X and Y
        if($A->dtype()!=$X->dtype()) {
            throw new InvalidArgumentException("Unmatch data type for A and X");
        }
        if($X->dtype()!=$Y->dtype()) {
            throw new InvalidArgumentException("Unmatch data type for X and Y");
        }
        // CLBlast does not support ConjNoTrans
        if($trans==BLASIF::ConjNoTrans) {
            throw new InvalidArgumentException("CLBlast does not support ConjNoTrans");
        }
        $bufferA_p = $ffi->cast("cl_mem",$A->_getId());
        $bufferX_p = $ffi->cast("cl_mem",$X->_getId());
        $bufferY_p = $ffi->cast("cl_mem",$Y->_getId());
        $queue_p = $ffi->cast("cl_command_queue*",FFI::addr($queue->_getId()));
        $event_p = null;
        if($event) {
            $event_obj = $event->_ffi()->new("cl_event[1]");
            $event_p = $ffi->cast("cl_event[1]",$event_obj);
        }

        switch($X->dtype()) {
            case NDArray::float32:{
                $status = $ffi->CLBlastSgemv(
                    $order,
                    $trans,
                    $m,$n,
                    $alpha,
                    $bufferA_p,$offsetA,$ldA,
                    $bufferX_p,$offsetX,$incX,
                    $beta,
                    $bufferY_p,$offsetY,$incY,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::float64:{
                $status = $ffi->CLBlastDgemv(
                    $order,
                    $trans,
                    $m,$n,
                    $alpha,
                    $bufferA_p,$offsetA,$ldA,
                    $bufferX_p,$offsetX,$incX,
                    $beta,
                    $bufferY_p,$offsetY,$incY,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::complex64:{
                $alpha = $this->toComplex($alpha,$X->dtype());
                $beta = $this->toComplex($beta,$X->dtype());
                $status = $alt->CLBlastCgemv(
                    $order,
                    $trans,
                    $m,$n,
                    $alpha,
                    $bufferA_p,$offsetA,$ldA,
                    $bufferX_p,$offsetX,$incX,
                    $beta,
                    $bufferY_p,$offsetY,$incY,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::complex128:{
                $alpha = $this->toComplex($alpha,$X->dtype());
                $beta = $this->toComplex($beta,$X->dtype());
                $status = $alt->CLBlastZgemv(
                    $order,
                    $trans,
                    $m,$n,
                    $alpha,
                    $bufferA_p,$offsetA,$ldA,
                    $bufferX_p,$offsetX,$incX,
                    $beta,
                    $bufferY_p,$offsetY,$incY,
                    $queue_p,$event_p
                );
                break;
            }
            default: {
                throw new InvalidArgumentException('Unsuppored data type');
            }
        }
        if($status!=self::CLBlastSuccess) {
            throw new RuntimeException("CLBlast?copy error=$status", $status);
        }
        if($event) {
            $event->_move($event_obj);
        }
    }

    public function gemm(
        int $order,
        int $transA,
        int $transB,
        int $m,
        int $n,
        int $k,
        float|object $alpha,
        DeviceBuffer $A, int $offsetA, int $ldA,
        DeviceBuffer $B, int $offsetB, int $ldB,
        float|object $beta,
        DeviceBuffer $C, int $offsetC, int $ldC,
        CommandQueue $queue,
        EventList $event=null
    ) : void
    {
        $ffi = $this->ffi;
        $alt = $this->alt;
        // Check Buffer A and X and B
        if($A->dtype()!=$B->dtype()) {
            throw new InvalidArgumentException("Unmatch data type for A and B");
        }
        if($A->dtype()!=$C->dtype()) {
            throw new InvalidArgumentException("Unmatch data type for A and C");
        }
        // CLBlast does not support ConjNoTrans
        if($transA==BLASIF::ConjNoTrans) {
            throw new InvalidArgumentException("CLBlast does not support ConjNoTrans");
        }
        if($transB==BLASIF::ConjNoTrans) {
            throw new InvalidArgumentException("CLBlast does not support ConjNoTrans");
        }
        $bufferA_p = $ffi->cast("cl_mem",$A->_getId());
        $bufferB_p = $ffi->cast("cl_mem",$B->_getId());
        $bufferC_p = $ffi->cast("cl_mem",$C->_getId());
        $queue_p = $ffi->cast("cl_command_queue*",FFI::addr($queue->_getId()));
        $event_p = null;
        if($event) {
            $event_obj = $event->_ffi()->new("cl_event[1]");
            $event_p = $ffi->cast("cl_event[1]",$event_obj);
        }

        switch($A->dtype()) {
            case NDArray::float32:{
                $status = $ffi->CLBlastSgemm(
                    $order,
                    $transA,
                    $transB,
                    $m,$n,$k,
                    $alpha,
                    $bufferA_p,$offsetA,$ldA,
                    $bufferB_p,$offsetB,$ldB,
                    $beta,
                    $bufferC_p,$offsetC,$ldC,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::float64:{
                $status = $ffi->CLBlastDgemm(
                    $order,
                    $transA,
                    $transB,
                    $m,$n,$k,
                    $alpha,
                    $bufferA_p,$offsetA,$ldA,
                    $bufferB_p,$offsetB,$ldB,
                    $beta,
                    $bufferC_p,$offsetC,$ldC,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::complex64:{
                $alpha = $this->toComplex($alpha,$A->dtype());
                $beta = $this->toComplex($beta,$A->dtype());
                $status = $alt->CLBlastCgemm(
                    $order,
                    $transA,
                    $transB,
                    $m,$n,$k,
                    $alpha,
                    $bufferA_p,$offsetA,$ldA,
                    $bufferB_p,$offsetB,$ldB,
                    $beta,
                    $bufferC_p,$offsetC,$ldC,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::complex128:{
                $alpha = $this->toComplex($alpha,$A->dtype());
                $beta = $this->toComplex($beta,$A->dtype());
                $status = $alt->CLBlastZgemm(
                    $order,
                    $transA,
                    $transB,
                    $m,$n,$k,
                    $alpha,
                    $bufferA_p,$offsetA,$ldA,
                    $bufferB_p,$offsetB,$ldB,
                    $beta,
                    $bufferC_p,$offsetC,$ldC,
                    $queue_p,$event_p
                );
                break;
            }
            default: {
                throw new InvalidArgumentException('Unsuppored data type');
            }
        }
        if($status!=self::CLBlastSuccess) {
            throw new RuntimeException("CLBlast?copy error=$status", $status);
        }
        if($event) {
            $event->_move($event_obj);
        }
    }

    public function symm(
        int $order,
        int $side,
        int $uplo,
        int $m,
        int $n,
        float|object $alpha,
        DeviceBuffer $A, int $offsetA, int $ldA,
        DeviceBuffer $B, int $offsetB, int $ldB,
        float|object $beta,
        DeviceBuffer $C, int $offsetC, int $ldC,
        CommandQueue $queue,
        EventList $event=null,
    ) : void
    {
        $ffi = $this->ffi;
        $alt = $this->alt;
        // Check Buffer A and X and B
        if($A->dtype()!=$B->dtype()) {
            throw new InvalidArgumentException("Unmatch data type for A and B");
        }
        if($A->dtype()!=$C->dtype()) {
            throw new InvalidArgumentException("Unmatch data type for A and C");
        }
        $bufferA_p = $ffi->cast("cl_mem",$A->_getId());
        $bufferB_p = $ffi->cast("cl_mem",$B->_getId());
        $bufferC_p = $ffi->cast("cl_mem",$C->_getId());
        $queue_p = $ffi->cast("cl_command_queue*",FFI::addr($queue->_getId()));
        $event_p = null;
        if($event) {
            $event_obj = $event->_ffi()->new("cl_event[1]");
            $event_p = $ffi->cast("cl_event[1]",$event_obj);
        }

        switch($A->dtype()) {
            case NDArray::float32:{
                $status = $ffi->CLBlastSsymm(
                    $order,
                    $side,
                    $uplo,
                    $m,$n,
                    $alpha,
                    $bufferA_p,$offsetA,$ldA,
                    $bufferB_p,$offsetB,$ldB,
                    $beta,
                    $bufferC_p,$offsetC,$ldC,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::float64:{
                $status = $ffi->CLBlastDsymm(
                    $order,
                    $side,
                    $uplo,
                    $m,$n,
                    $alpha,
                    $bufferA_p,$offsetA,$ldA,
                    $bufferB_p,$offsetB,$ldB,
                    $beta,
                    $bufferC_p,$offsetC,$ldC,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::complex64:{
                $alpha = $this->toComplex($alpha,$A->dtype());
                $beta = $this->toComplex($beta,$A->dtype());
                $status = $alt->CLBlastCsymm(
                    $order,
                    $side,
                    $uplo,
                    $m,$n,
                    $alpha,
                    $bufferA_p,$offsetA,$ldA,
                    $bufferB_p,$offsetB,$ldB,
                    $beta,
                    $bufferC_p,$offsetC,$ldC,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::complex128:{
                $alpha = $this->toComplex($alpha,$A->dtype());
                $beta = $this->toComplex($beta,$A->dtype());
                $status = $alt->CLBlastZsymm(
                    $order,
                    $side,
                    $uplo,
                    $m,$n,
                    $alpha,
                    $bufferA_p,$offsetA,$ldA,
                    $bufferB_p,$offsetB,$ldB,
                    $beta,
                    $bufferC_p,$offsetC,$ldC,
                    $queue_p,$event_p
                );
                break;
            }
            default: {
                throw new InvalidArgumentException('Unsuppored data type');
            }
        }
        if($status!=self::CLBlastSuccess) {
            throw new RuntimeException("CLBlast?symm error=$status", $status);
        }
        if($event) {
            $event->_move($event_obj);
        }
    }

    public function syrk(
        int $order,
        int $uplo,
        int $trans,
        int $n,
        int $k,
        float|object $alpha,
        DeviceBuffer $A, int $offsetA, int $ldA,
        float|object $beta,
        DeviceBuffer $C, int $offsetC, int $ldC,
        CommandQueue $queue,
        EventList $event=null,
    ) : void
    {
        $ffi = $this->ffi;
        $alt = $this->alt;
        // Check Buffer A and X and B
        if($A->dtype()!=$C->dtype()) {
            throw new InvalidArgumentException("Unmatch data type for A and C");
        }
        $bufferA_p = $ffi->cast("cl_mem",$A->_getId());
        $bufferC_p = $ffi->cast("cl_mem",$C->_getId());
        $queue_p = $ffi->cast("cl_command_queue*",FFI::addr($queue->_getId()));
        $event_p = null;
        if($event) {
            $event_obj = $event->_ffi()->new("cl_event[1]");
            $event_p = $ffi->cast("cl_event[1]",$event_obj);
        }

        switch($A->dtype()) {
            case NDArray::float32:{
                $status = $ffi->CLBlastSsyrk(
                    $order,
                    $uplo,
                    $trans,
                    $n,$k,
                    $alpha,
                    $bufferA_p,$offsetA,$ldA,
                    $beta,
                    $bufferC_p,$offsetC,$ldC,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::float64:{
                $status = $ffi->CLBlastDsyrk(
                    $order,
                    $uplo,
                    $trans,
                    $n,$k,
                    $alpha,
                    $bufferA_p,$offsetA,$ldA,
                    $beta,
                    $bufferC_p,$offsetC,$ldC,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::complex64:{
                $alpha = $this->toComplex($alpha,$A->dtype());
                $beta = $this->toComplex($beta,$A->dtype());
                $status = $alt->CLBlastCsyrk(
                    $order,
                    $uplo,
                    $trans,
                    $n,$k,
                    $alpha,
                    $bufferA_p,$offsetA,$ldA,
                    $beta,
                    $bufferC_p,$offsetC,$ldC,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::complex128:{
                $alpha = $this->toComplex($alpha,$A->dtype());
                $beta = $this->toComplex($beta,$A->dtype());
                $status = $alt->CLBlastZsyrk(
                    $order,
                    $uplo,
                    $trans,
                    $n,$k,
                    $alpha,
                    $bufferA_p,$offsetA,$ldA,
                    $beta,
                    $bufferC_p,$offsetC,$ldC,
                    $queue_p,$event_p
                );
                break;
            }
            default: {
                throw new InvalidArgumentException('Unsuppored data type');
            }
        }
        if($status!=self::CLBlastSuccess) {
            throw new RuntimeException("CLBlast?syrk error=$status", $status);
        }
        if($event) {
            $event->_move($event_obj);
        }
    }

    public function syr2k(
        int $order,
        int $uplo,
        int $trans,
        int $n,
        int $k,
        float|object $alpha,
        DeviceBuffer $A, int $offsetA, int $ldA,
        DeviceBuffer $B, int $offsetB, int $ldB,
        float|object $beta,
        DeviceBuffer $C, int $offsetC, int $ldC,
        CommandQueue $queue,
        EventList $event=null,
    ) : void
    {
        $ffi = $this->ffi;
        $alt = $this->alt;
        // Check Buffer A and X and B
        if($A->dtype()!=$B->dtype()) {
            throw new InvalidArgumentException("Unmatch data type for A and B");
        }
        if($A->dtype()!=$C->dtype()) {
            throw new InvalidArgumentException("Unmatch data type for A and C");
        }
        $bufferA_p = $ffi->cast("cl_mem",$A->_getId());
        $bufferB_p = $ffi->cast("cl_mem",$B->_getId());
        $bufferC_p = $ffi->cast("cl_mem",$C->_getId());
        $queue_p = $ffi->cast("cl_command_queue*",FFI::addr($queue->_getId()));
        $event_p = null;
        if($event) {
            $event_obj = $event->_ffi()->new("cl_event[1]");
            $event_p = $ffi->cast("cl_event[1]",$event_obj);
        }

        switch($A->dtype()) {
            case NDArray::float32:{
                $status = $ffi->CLBlastSsyr2k(
                    $order,
                    $uplo,
                    $trans,
                    $n,$k,
                    $alpha,
                    $bufferA_p,$offsetA,$ldA,
                    $bufferB_p,$offsetB,$ldB,
                    $beta,
                    $bufferC_p,$offsetC,$ldC,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::float64:{
                $status = $ffi->CLBlastDsyr2k(
                    $order,
                    $uplo,
                    $trans,
                    $n,$k,
                    $alpha,
                    $bufferA_p,$offsetA,$ldA,
                    $bufferB_p,$offsetB,$ldB,
                    $beta,
                    $bufferC_p,$offsetC,$ldC,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::complex64:{
                $alpha = $this->toComplex($alpha,$A->dtype());
                $beta = $this->toComplex($beta,$A->dtype());
                $status = $alt->CLBlastCsyr2k(
                    $order,
                    $uplo,
                    $trans,
                    $n,$k,
                    $alpha,
                    $bufferA_p,$offsetA,$ldA,
                    $bufferB_p,$offsetB,$ldB,
                    $beta,
                    $bufferC_p,$offsetC,$ldC,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::complex128:{
                $alpha = $this->toComplex($alpha,$A->dtype());
                $beta = $this->toComplex($beta,$A->dtype());
                $status = $alt->CLBlastZsyr2k(
                    $order,
                    $uplo,
                    $trans,
                    $n,$k,
                    $alpha,
                    $bufferA_p,$offsetA,$ldA,
                    $bufferB_p,$offsetB,$ldB,
                    $beta,
                    $bufferC_p,$offsetC,$ldC,
                    $queue_p,$event_p
                );
                break;
            }
            default: {
                throw new InvalidArgumentException('Unsuppored data type');
            }
        }
        if($status!=self::CLBlastSuccess) {
            throw new RuntimeException("CLBlast?syr2k error=$status", $status);
        }
        if($event) {
            $event->_move($event_obj);
        }
    }

    public function trmm(
        int $order,
        int $side,
        int $uplo,
        int $trans,
        int $diag,
        int $m,
        int $n,
        float|object $alpha,
        DeviceBuffer $A, int $offsetA, int $ldA,
        DeviceBuffer $B, int $offsetB, int $ldB,
        CommandQueue $queue,
        EventList $event=null,
    ) : void
    {
        $ffi = $this->ffi;
        $alt = $this->alt;
        // Check Buffer A and X and B
        if($A->dtype()!=$B->dtype()) {
            throw new InvalidArgumentException("Unmatch data type for A and B");
        }
        $bufferA_p = $ffi->cast("cl_mem",$A->_getId());
        $bufferB_p = $ffi->cast("cl_mem",$B->_getId());
        $queue_p = $ffi->cast("cl_command_queue*",FFI::addr($queue->_getId()));
        $event_p = null;
        if($event) {
            $event_obj = $event->_ffi()->new("cl_event[1]");
            $event_p = $ffi->cast("cl_event[1]",$event_obj);
        }

        switch($A->dtype()) {
            case NDArray::float32:{
                $status = $ffi->CLBlastStrmm(
                    $order,
                    $side,
                    $uplo,
                    $trans,
                    $diag,
                    $m,$n,
                    $alpha,
                    $bufferA_p,$offsetA,$ldA,
                    $bufferB_p,$offsetB,$ldB,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::float64:{
                $status = $ffi->CLBlastDtrmm(
                    $order,
                    $side,
                    $uplo,
                    $trans,
                    $diag,
                    $m,$n,
                    $alpha,
                    $bufferA_p,$offsetA,$ldA,
                    $bufferB_p,$offsetB,$ldB,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::complex64:{
                $alpha = $this->toComplex($alpha,$A->dtype());
                $status = $alt->CLBlastCtrmm(
                    $order,
                    $side,
                    $uplo,
                    $trans,
                    $diag,
                    $m,$n,
                    $alpha,
                    $bufferA_p,$offsetA,$ldA,
                    $bufferB_p,$offsetB,$ldB,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::complex128:{
                $alpha = $this->toComplex($alpha,$A->dtype());
                $status = $alt->CLBlastZtrmm(
                    $order,
                    $side,
                    $uplo,
                    $trans,
                    $diag,
                    $m,$n,
                    $alpha,
                    $bufferA_p,$offsetA,$ldA,
                    $bufferB_p,$offsetB,$ldB,
                    $queue_p,$event_p
                );
                break;
            }
            default: {
                throw new InvalidArgumentException('Unsuppored data type');
            }
        }
        if($status!=self::CLBlastSuccess) {
            throw new RuntimeException("CLBlast?syr2k error=$status", $status);
        }
        if($event) {
            $event->_move($event_obj);
        }
    }

    public function trsm(
        int $order,
        int $side,
        int $uplo,
        int $trans,
        int $diag,
        int $m,
        int $n,
        float|object $alpha,
        DeviceBuffer $A, int $offsetA, int $ldA,
        DeviceBuffer $B, int $offsetB, int $ldB,
        CommandQueue $queue,
        EventList $event=null,
    ) : void
    {
        $ffi = $this->ffi;
        $alt = $this->alt;
        // Check Buffer A and X and B
        if($A->dtype()!=$B->dtype()) {
            throw new InvalidArgumentException("Unmatch data type for A and B");
        }
        $bufferA_p = $ffi->cast("cl_mem",$A->_getId());
        $bufferB_p = $ffi->cast("cl_mem",$B->_getId());
        $queue_p = $ffi->cast("cl_command_queue*",FFI::addr($queue->_getId()));
        $event_p = null;
        if($event) {
            $event_obj = $event->_ffi()->new("cl_event[1]");
            $event_p = $ffi->cast("cl_event[1]",$event_obj);
        }

        switch($A->dtype()) {
            case NDArray::float32:{
                $status = $ffi->CLBlastStrsm(
                    $order,
                    $side,
                    $uplo,
                    $trans,
                    $diag,
                    $m,$n,
                    $alpha,
                    $bufferA_p,$offsetA,$ldA,
                    $bufferB_p,$offsetB,$ldB,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::float64:{
                $status = $ffi->CLBlastDtrsm(
                    $order,
                    $side,
                    $uplo,
                    $trans,
                    $diag,
                    $m,$n,
                    $alpha,
                    $bufferA_p,$offsetA,$ldA,
                    $bufferB_p,$offsetB,$ldB,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::complex64:{
                $alpha = $this->toComplex($alpha,$A->dtype());
                $status = $alt->CLBlastCtrsm(
                    $order,
                    $side,
                    $uplo,
                    $trans,
                    $diag,
                    $m,$n,
                    $alpha,
                    $bufferA_p,$offsetA,$ldA,
                    $bufferB_p,$offsetB,$ldB,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::complex128:{
                $alpha = $this->toComplex($alpha,$A->dtype());
                $status = $alt->CLBlastZtrsm(
                    $order,
                    $side,
                    $uplo,
                    $trans,
                    $diag,
                    $m,$n,
                    $alpha,
                    $bufferA_p,$offsetA,$ldA,
                    $bufferB_p,$offsetB,$ldB,
                    $queue_p,$event_p
                );
                break;
            }
            default: {
                throw new InvalidArgumentException('Unsuppored data type');
            }
        }
        if($status!=self::CLBlastSuccess) {
            throw new RuntimeException("CLBlast?syr2k error=$status", $status);
        }
        if($event) {
            $event->_move($event_obj);
        }
    }

    public function omatcopy(
        int $order,
        int $trans,
        int $m,
        int $n,
        float|object $alpha,
        DeviceBuffer $A, int $offsetA, int $ldA,
        DeviceBuffer $B, int $offsetB, int $ldB,
        CommandQueue $queue,
        EventList $event=null
    ) : void
    {
        $ffi = $this->ffi;
        $alt = $this->alt;
        // Check Buffer A and B
        if($A->dtype()!=$B->dtype()) {
            throw new InvalidArgumentException("Unmatch data type for A and B");
        }
        // CLBlast does not support ConjNoTrans
        if($trans==BLASIF::ConjNoTrans) {
            throw new InvalidArgumentException("CLBlast does not support ConjNoTrans");
        }
        $bufferA_p = $ffi->cast("cl_mem",$A->_getId());
        $bufferB_p = $ffi->cast("cl_mem",$B->_getId());
        $queue_p = $ffi->cast("cl_command_queue*",FFI::addr($queue->_getId()));
        $event_p = null;
        if($event) {
            $event_obj = $event->_ffi()->new("cl_event[1]");
            $event_p = $ffi->cast("cl_event[1]",$event_obj);
        }

        switch($A->dtype()) {
            case NDArray::float32:{
                $status = $ffi->CLBlastSomatcopy(
                    $order,
                    $trans,
                    $m,$n,
                    $alpha,
                    $bufferA_p, $offsetA, $ldA,
                    $bufferB_p, $offsetB, $ldB,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::float64:{
                $status = $ffi->CLBlastDomatcopy(
                    $order,
                    $trans,
                    $m,$n,
                    $alpha,
                    $bufferA_p, $offsetA, $ldA,
                    $bufferB_p, $offsetB, $ldB,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::complex64:{
                $alpha = $this->toComplex($alpha,$A->dtype());
                $status = $alt->CLBlastComatcopy(
                    $order,
                    $trans,
                    $m,$n,
                    $alpha,
                    $bufferA_p, $offsetA, $ldA,
                    $bufferB_p, $offsetB, $ldB,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::complex128:{
                $alpha = $this->toComplex($alpha,$A->dtype());
                $status = $alt->CLBlastZomatcopy(
                    $order,
                    $trans,
                    $m,$n,
                    $alpha,
                    $bufferA_p, $offsetA, $ldA,
                    $bufferB_p, $offsetB, $ldB,
                    $queue_p,$event_p
                );
                break;
            }
            default: {
                throw new InvalidArgumentException('Unsuppored data type');
            }
        }
        if($status!=self::CLBlastSuccess) {
            throw new RuntimeException("CLBlast?omatcopy error=$status", $status);
        }
        if($event) {
            $event->_move($event_obj);
        }
    }

}