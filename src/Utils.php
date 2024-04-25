<?php
namespace Rindow\CLBlast\FFI;

use Interop\Polite\Math\Matrix\NDArray;
use InvalidArgumentException;

class cl_float2_t {
    /** @var array<float> $s */
    public array $s;
}

trait Utils
{
    protected function toComplex(object $from,int $dtype) : object
    {
        $ffi = $this->ffi;
        switch($dtype) {
            case NDArray::complex64: {
                /** @var cl_float2_t $to */
                $to = $ffi->new('cl_float2');
                $to->s[0] = $from->real;
                $to->s[1] = $from->imag;
                break;
            }
            case NDArray::complex128: {
                /** @var cl_float2_t $to */
                $to = $ffi->new('cl_double2');
                $to->s[0] = $from->real;
                $to->s[1] = $from->imag;
                break;
            }
            default: {
                throw new InvalidArgumentException('Unsuppored data type');
            }
        }
        return $to;
    }
}