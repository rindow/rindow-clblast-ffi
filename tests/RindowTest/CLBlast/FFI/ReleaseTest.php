<?php
namespace RindowTest\OpenCL\FFI\ReleaseTest;

use PHPUnit\Framework\TestCase;
use Rindow\CLBlast\FFI\CLBlastFactory;
use Rindow\CLBlast\FFI\Blas;
use Rindow\CLBlast\FFI\Math;
use FFI;

class ReleaseTest extends TestCase
{
    public function testFFINotLoaded()
    {
        $factory = new CLBlastFactory();
        if(extension_loaded('ffi')) {
            if($factory->isAvailable()) {
                $blas = $factory->Blas();
                $math = $factory->Math();
                $this->assertInstanceof(Blas::class,$blas);
                $this->assertInstanceof(Math::class,$math);
            } else {
                $this->assertTrue(true);
            }
        } else {
            $this->assertFalse($factory->isAvailable());
        }
    }
}