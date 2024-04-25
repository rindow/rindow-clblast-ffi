The CLBlast interface for FFI on PHP
====================================
Status:
[![Build Status](https://github.com/rindow/rindow-clblast-ffi/workflows/tests/badge.svg)](https://github.com/rindow/rindow-clblast-ffi/actions)
[![Downloads](https://img.shields.io/packagist/dt/rindow/rindow-clblast-ffi)](https://packagist.org/packages/rindow/rindow-clblast-ffi)
[![Latest Stable Version](https://img.shields.io/packagist/v/rindow/rindow-clblast-ffi)](https://packagist.org/packages/rindow/rindow-clblast-ffi)
[![License](https://img.shields.io/packagist/l/rindow/rindow-clblast-ffi)](https://packagist.org/packages/rindow/rindow-clblast-ffi)

"The CLBlast ffi" is a interface for the CLBlast library. Available in libraries with FFI interface.

Please see the documents about Buffer objects on [Rindow Mathematics](https://rindow.github.io/mathematics/acceleration/opencl.html#rindow-clblast-ffi) web pages.

Requirements
============

- PHP 8.1 or PHP8.2 or PHP8.3
- CLBlast 1.5.1 or later

How to setup OpenCL & CLBlast
=============================
You can download and setup pre-built CLBlast binaries.
Please download the binaries for your platform.

- https://github.com/CNugteren/CLBlast/releases


### Windows
CLBlast and OpenBLAS DLL's path to Windows PATH environment variable.

```shell
C:\tmp>PATH %PATH%;/path/to/OpenBLAS/bin;/path/to/CLBlast-Library/lib
C:\tmp>cd /some/app/directory
C:\app\dir>composer require rindow/rindow-clblast-ffi
```

### Ubuntu
On Linux, you first need to set up OpenCL.

For example, in the case of Ubuntu standard AMD driver, install as follows
```shell
$ sudo apt install clinfo
$ sudo apt install mesa-opencl-icd
$ sudo mkdir -p /usr/local/usr/lib
$ sudo ln -s /usr/lib/clc /usr/local/usr/lib/clc
```
Ubuntu standard OpenCL drivers include:
- mesa-opencl-icd
- beignet-opencl-icd
- intel-opencl-icd
- nvidia-opencl-icd-xxx
- pocl-opencl-icd


Next, Setup clblast. 

Install clbast on Ubuntu 22.04 or Debian 12 or later.
```shell
$ sudo apt install libclblast1
```

If you use Ubuntu 20.04 or Debian 11,
download and Extract Archive file and Pack to deb
```shell
$ cd /some/app/directory
$ composer require rindow/rindow-clblast-ffi
$ cp vendor/rindow/rindow-clblast-ffi/clblast-packdeb.sh .
$ sh ./clblast-packdeb.sh
$ sudo apt install ./clblast_X.X.X_amd64.deb
```

And then, Please install rindow-clblast-ffi if you have not already done so.
```shell
$ cd /some/app/directory
$ composer require rindow/rindow-clblast-ffi
```
