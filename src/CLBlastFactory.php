<?php
namespace Rindow\CLBlast\FFI;

use FFI;
use FFI\Exception as FFIException;
use RuntimeException;
use Rindow\CLBlast\FFI\Platforms\LinuxPatch;

class CLBlastFactory
{
    private static ?FFI $ffi = null;
    public static ?FFI $ffipf = null;
    /** @var array<string> $libs_win */
    protected array $libs_win = ['clblast.dll'];
    /** @var array<string> $libs_linux */
    protected array $libs_linux = ['libclblast.so.1'];

    /**
     * @param array<string> $libFiles
     */
    public function __construct(
        string $headerFile=null,
        array $libFiles=null,
        )
    {
        if(self::$ffi!==null) {
            return;
        }
        if(!extension_loaded('ffi')) {
            return;
        }
        $headerFile = $headerFile ?? __DIR__ . "/clblast_c.h";

        if($libFiles==null) {
            if(PHP_OS=='Linux') {
                $libFiles = $this->libs_linux;
            } elseif(PHP_OS=='WINNT') {
                $libFiles = $this->libs_win;
            } else {
                throw new RuntimeException('Unknown operating system: "'.PHP_OS.'"');
            }
        }
        $code = file_get_contents($headerFile);
        // ***************************************************************
        // FFI Locator is incompletely implemented. It is often not found.
        // ***************************************************************
        //$pathname = FFIEnvLocator::resolve(...$libFiles);
        //if($pathname) {
        //    $ffi = FFI::cdef($code,$pathname);
        //    self::$ffi = $ffi;
        //}
        foreach ($libFiles as $filename) {
            try {
                $ffi = FFI::cdef($code,$filename);
            } catch(FFIException $e) {
                continue;
            }
            self::$ffi = $ffi;
            break;
        }

        // patch for linux
        $this->loadPlatformLib();
    }

    protected function loadPlatformLib() : void
    {
        if(PHP_OS!='Linux') {
            return;
        }
        $headerFile = __DIR__ . "/../platforms/ubuntu/src/complexfuncs.h";
        $filename = __DIR__ . "/../platforms/ubuntu/lib/librindowclblast.so";
        //self::$ffipf = FFI::load($headerFile);
        $code = file_get_contents($headerFile);
        $ffi = null;
        try {
            $ffi = FFI::cdef($code,$filename);
        } catch(FFIException $e) {
            $ffi = null;
        }
        self::$ffipf = $ffi;
    }

    public function isAvailable() : bool
    {
        return self::$ffi!==null;
        //$isAvailable = FFIEnvRuntime::isAvailable();
        //if(!$isAvailable) {
        //    return false;
        //}
        //$pathname = FFIEnvLocator::resolve(...$this->libs);
        //return $pathname!==null;
    }

    public function Blas(object $queue=null,object $service=null) : object
    {
        if(self::$ffi==null) {
            throw new RuntimeException('clblast library not loaded.');
        }
        $alt = self::$ffi;
        if(PHP_OS=='Linux') {
            $alt = new LinuxPatch(self::$ffipf);
        }
        return new Blas(self::$ffi, $alt);
    }

    public function Math(object $queue=null,object $service=null) : object
    {
        if(self::$ffi==null) {
            throw new RuntimeException('clblast library not loaded.');
        }
        $alt = self::$ffi;
        if(PHP_OS=='Linux') {
            $alt = new LinuxPatch(self::$ffipf);
        }
        return new Math(self::$ffi, $alt);
    }
}
