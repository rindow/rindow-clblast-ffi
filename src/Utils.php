<?php
namespace Rindow\CLBlast\FFI;

use Interop\Polite\Math\Matrix\NDArray;

trait Utils
{
    protected function toComplex(object $from,int $dtype) : object
    {
        $ffi = $this->ffi;
        switch($dtype) {
            case NDArray::complex64: {
                $to = $ffi->new('cl_float2');
                $to->s[0] = $from->real;
                $to->s[1] = $from->imag;
                break;
            }
            case NDArray::complex128: {
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