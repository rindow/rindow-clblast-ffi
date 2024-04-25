<?php
namespace Rindow\CLBlast\FFI;

use Interop\Polite\Math\Matrix\LinearBuffer as HostBuffer;
use Interop\Polite\Math\Matrix\NDArray;
use Interop\Polite\Math\Matrix\BLAS as BLASIF;
use InvalidArgumentException;
use OutOfRangeException;
use LogicException;
use RuntimeException;
use FFI;
use Rindow\OpenCL\FFI\Buffer as DeviceBuffer;
use Rindow\OpenCL\FFI\CommandQueue;
use Rindow\OpenCL\FFI\EventList;


class Math
{
    use Utils;

    const CLBlastSuccess = 0;
    const CROSS_CORRELATION = 151;
    const CONVOLUTION = 152;

    protected FFI $ffi;
    protected object $alt;

    public function __construct(FFI $ffi, object $alt)
    {
        $this->ffi = $ffi;
        $this->alt = $alt;
    }

    public function sum(
        int $n,
        DeviceBuffer $R, int $offsetR,
        DeviceBuffer $X, int $offsetX, int $incX,
        CommandQueue $queue,
        EventList $event=null
    ) : void
    {
        $ffi = $this->ffi;
        // Check Buffer X and R
        //if($X->dtype()!=$R->dtype()) {
        //    var_dump($X->dtype());
        //    var_dump($R->dtype());
        //    throw new InvalidArgumentException("Unmatch data type for X and R");
        //}
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
                $status = $ffi->CLBlastSsum($n,
                    $bufferR_p,$offsetR,
                    $bufferX_p,$offsetX,$incX,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::float64:{
                $status = $ffi->CLBlastDsum($n,
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
            throw new RuntimeException("CLBlast?sum error=$status", $status);
        }
        if($event) {
            $event->_move($event_obj);
        }
    }

    public function imax(
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
                $status = $ffi->CLBlastiSmax($n,
                    $bufferR_p,$offsetR,
                    $bufferX_p,$offsetX,$incX,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::float64:{
                $status = $ffi->CLBlastiDmax($n,
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
            throw new RuntimeException("CLBlast?imax error=$status", $status);
        }
        if($event) {
            $event->_move($event_obj);
        }
    }

    public function imin(
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
                $status = $ffi->CLBlastiSmin($n,
                    $bufferR_p,$offsetR,
                    $bufferX_p,$offsetX,$incX,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::float64:{
                $status = $ffi->CLBlastiDmin($n,
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
            throw new RuntimeException("CLBlast?imin error=$status", $status);
        }
        if($event) {
            $event->_move($event_obj);
        }
    }

    public function hadamard(
        int $n,
        float $alpha,
        DeviceBuffer $X, int $offsetX, int $incX,
        DeviceBuffer $Y, int $offsetY, int $incY,
        float $beta,
        DeviceBuffer $Z, int $offsetZ, int $incZ,
        CommandQueue $queue,
        EventList $event=null
    ) : void
    {
        $ffi = $this->ffi;
        // Check Buffer X and Y
        if($X->dtype()!=$Y->dtype()) {
            throw new InvalidArgumentException("Unmatch data type for X and Y");
        }
        $bufferX_p = $ffi->cast("cl_mem",$X->_getId());
        $bufferY_p = $ffi->cast("cl_mem",$Y->_getId());
        $bufferZ_p = $ffi->cast("cl_mem",$Z->_getId());
        $queue_p = $ffi->cast("cl_command_queue*",FFI::addr($queue->_getId()));
        $event_p = null;
        if($event) {
            $event_obj = $event->_ffi()->new("cl_event[1]");
            $event_p = $ffi->cast("cl_event[1]",$event_obj);
        }

        switch($X->dtype()) {
            case NDArray::float32:{
                $status = $ffi->CLBlastShad($n,$alpha,
                    $bufferX_p,$offsetX,$incX,
                    $bufferY_p,$offsetY,$incY,
                    $beta,
                    $bufferZ_p,$offsetZ,$incZ,
                    $queue_p,$event_p
                );
                break;
            }
            case NDArray::float64:{
                $status = $ffi->CLBlastDhad($n,$alpha,
                    $bufferX_p,$offsetX,$incX,
                    $bufferY_p,$offsetY,$incY,
                    $beta,
                    $bufferZ_p,$offsetZ,$incZ,
                    $queue_p,$event_p
                );
                break;
            }
            default: {
                throw new InvalidArgumentException('Unsuppored data type');
            }
        }
        if($status!=self::CLBlastSuccess) {
            throw new RuntimeException("CLBlast?had error=$status", $status);
        }
        if($event) {
            $event->_move($event_obj);
        }
    }

    public function im2col(
        int $kernel_mode,
        int $channels, int $height, int $width,
        int $kernel_h, int $kernel_w,
        int $pad_h, int $pad_w,
        int $stride_h, int $stride_w,
        int $dilation_h, int $dilation_w,
        DeviceBuffer $im_buffer, int $im_offset,
        DeviceBuffer $col_buffer, int $col_offset,
        CommandQueue $queue,
        EventList $event=null
    ) : void
    {
        $ffi = $this->ffi;
        // Check Buffer A and B
        if($im_buffer->dtype()!=$col_buffer->dtype()) {
            throw new InvalidArgumentException("Unmatch data type for im and col");
        }
        $im_buffer_p = $ffi->cast("cl_mem",$im_buffer->_getId());
        $col_buffer_p = $ffi->cast("cl_mem",$col_buffer->_getId());
        $queue_p = $ffi->cast("cl_command_queue*",FFI::addr($queue->_getId()));
        $event_p = null;
        if($event) {
            $event_obj = $event->_ffi()->new("cl_event[1]");
            $event_p = $ffi->cast("cl_event[1]",$event_obj);
        }

        switch($im_buffer->dtype()) {
            case NDArray::float32:{
                $status = $ffi->CLBlastSim2col(
                    $kernel_mode,
                    $channels,$height,$width,
                    $kernel_h,$kernel_w,
                    $pad_h,$pad_w,          // ** CAUTION ** Blast has the bug.
                    $stride_h,$stride_w,    // pad_h&w, stride_h&w must be the same.
                    $dilation_h,$dilation_w,
                    $im_buffer_p, $im_offset,
                    $col_buffer_p, $col_offset,
                    $queue_p, $event_p
                );
                break;
            }
            case NDArray::float64:{
                $status = $ffi->CLBlastDim2col(
                    $kernel_mode,
                    $channels,$height,$width,
                    $kernel_h,$kernel_w,
                    $pad_h,$pad_w,          // ** CAUTION ** Blast has the bug
                    $stride_h,$stride_w,    // pad_h&w, stride_h&w must be the same.
                    $dilation_h,$dilation_w,
                    $im_buffer_p, $im_offset,
                    $col_buffer_p, $col_offset,
                    $queue_p, $event_p
                );
                break;
            }
            default: {
                throw new InvalidArgumentException('Unsuppored data type');
            }
        }
        if($status!=self::CLBlastSuccess) {
            throw new RuntimeException("CLBlast?im2col error=$status", $status);
        }
        if($event) {
            $event->_move($event_obj);
        }

    }

    public function col2im(
        int $kernel_mode,
        int $channels, int $height, int $width,
        int $kernel_h, int $kernel_w,
        int $pad_h, int $pad_w,
        int $stride_h, int $stride_w,
        int $dilation_h, int $dilation_w,
        DeviceBuffer $col_buffer, int $col_offset,
        DeviceBuffer $im_buffer, int $im_offset,
        CommandQueue $queue,
        EventList $event=null
    ) : void
    {
        $ffi = $this->ffi;
        // Check Buffer A and B
        if($im_buffer->dtype()!=$col_buffer->dtype()) {
            throw new InvalidArgumentException("Unmatch data type for im and col");
        }
        $im_buffer_p = $ffi->cast("cl_mem",$im_buffer->_getId());
        $col_buffer_p = $ffi->cast("cl_mem",$col_buffer->_getId());
        $queue_p = $ffi->cast("cl_command_queue*",FFI::addr($queue->_getId()));
        $event_p = null;
        if($event) {
            $event_obj = $event->_ffi()->new("cl_event[1]");
            $event_p = $ffi->cast("cl_event[1]",$event_obj);
        }

        switch($im_buffer->dtype()) {
            case NDArray::float32:{
                $status = $ffi->CLBlastScol2im(
                    $kernel_mode,
                    $channels,$height,$width,
                    $kernel_h,$kernel_w,
                    $pad_h,$pad_h,        // ** CAUTION ** Blast has the bug.
                    $stride_h,$stride_h,  // pad_h&w, stride_h&w must be the same.
                    $dilation_h,$dilation_w,
                    $col_buffer_p, $col_offset,
                    $im_buffer_p, $im_offset,
                    $queue_p, $event_p
                );
                break;
            }
            case NDArray::float64:{
                $status = $ffi->CLBlastDcol2im(
                    $kernel_mode,
                    $channels,$height,$width,
                    $kernel_h,$kernel_w,
                    $pad_h,$pad_h,        // ** CAUTION ** Blast has the bug
                    $stride_h,$stride_h,  // pad_h&w, stride_h&w must be the same.
                    $dilation_h,$dilation_w,
                    $col_buffer_p, $col_offset,
                    $im_buffer_p, $im_offset,
                    $queue_p, $event_p
                );
                break;
            }
            default: {
                throw new InvalidArgumentException('Unsuppored data type');
            }
        }
        if($status!=self::CLBlastSuccess) {
            throw new RuntimeException("CLBlast?col2im error=$status", $status);
        }
        if($event) {
            $event->_move($event_obj);
        }
    }

    public function convgemm(
        int $kernel_mode,
        int $channels, int $height, int $width,
        int $kernel_h, int $kernel_w,
        int $pad_h, int $pad_w,
        int $stride_h, int $stride_w,
        int $dilation_h, int $dilation_w,
        int $num_kernels,
        int $batch_count,
        DeviceBuffer $im_buffer, int $im_offset,
        DeviceBuffer $kernel_buffer, int $kernel_offset,
        DeviceBuffer $result_buffer, int $result_offset,
        CommandQueue $queue,
        EventList $event=null
    ) : void
    {
        $ffi = $this->ffi;
        // Check Buffer A and B
        if($im_buffer->dtype()!=$kernel_buffer->dtype()) {
            throw new InvalidArgumentException("Unmatch data type for im and col");
        }
        $im_buffer_p = $ffi->cast("cl_mem",$im_buffer->_getId());
        $kernel_buffer_p = $ffi->cast("cl_mem",$kernel_buffer->_getId());
        $result_buffer_p = $ffi->cast("cl_mem",$result_buffer->_getId());
        $queue_p = $ffi->cast("cl_command_queue*",FFI::addr($queue->_getId()));
        $event_p = null;
        if($event) {
            $event_obj = $event->_ffi()->new("cl_event[1]");
            $event_p = $ffi->cast("cl_event[1]",$event_obj);
        }

        switch($im_buffer->dtype()) {
            case NDArray::float32:{
                $status = $ffi->CLBlastSconvgemm(
                    $kernel_mode,
                    $channels,$height,$width,
                    $kernel_h,$kernel_w,
                    $pad_h,$pad_h,        // ** CAUTION ** Blast has the bug.
                    $stride_h,$stride_h,  // pad_h&w, stride_h&w must be the same.
                    $dilation_h,$dilation_w,
                    $num_kernels, $batch_count,
                    $im_buffer_p, $im_offset,
                    $kernel_buffer_p, $kernel_offset,
                    $result_buffer_p, $result_offset,
                    $queue_p, $event_p
                );
                break;
            }
            case NDArray::float64:{
                $status = $ffi->CLBlastDconvgemm(
                    $kernel_mode,
                    $channels,$height,$width,
                    $kernel_h,$kernel_w,
                    $pad_h,$pad_h,        // ** CAUTION ** Blast has the bug.
                    $stride_h,$stride_h,  // pad_h&w, stride_h&w must be the same.
                    $dilation_h,$dilation_w,
                    $num_kernels, $batch_count,
                    $im_buffer_p, $im_offset,
                    $kernel_buffer_p, $kernel_offset,
                    $result_buffer_p, $result_offset,
                    $queue_p, $event_p
                );
                break;
            }
            default: {
                throw new InvalidArgumentException('Unsuppored data type');
            }
        }
        if($status!=self::CLBlastSuccess) {
            throw new RuntimeException("CLBlast?convgemm error=$status", $status);
        }
        if($event) {
            $event->_move($event_obj);
        }
    }

    public function axpyBatched(
        int $n,
        HostBuffer $alpha, int $offsetA,
        DeviceBuffer $X, HostBuffer $offsetsX, int $offsetX, int $incX,
        DeviceBuffer $Y, HostBuffer $offsetsY, int $offsetY, int $incY,
        int $batch_count,
        CommandQueue $queue, EventList $event=null
    ) : void
    {
        $ffi = $this->ffi;
        if($n<=0) {
            throw new InvalidArgumentException("n must be greater than zero");
        }
        if($offsetA<0) {
            throw new InvalidArgumentException("offsetA must be greater than zero or equal");
        }
        if($offsetX<0) {
            throw new InvalidArgumentException("offsetX must be greater than zero or equal");
        }
        if($offsetY<0) {
            throw new InvalidArgumentException("offsetY must be greater than zero or equal");
        }
        if($batch_count<0) {
            throw new InvalidArgumentException("batch_count must be greater than zero or equal");
        }
        if($offsetA+$batch_count>count($alpha)) {
            throw new InvalidArgumentException("alpha LinearBuffer is too small.");
        }
        if($offsetX+$batch_count>count($offsetsX)) {
            throw new InvalidArgumentException("offsetsX LinearBuffer is too small.");
        }
        if($offsetY+$batch_count>count($offsetsY)) {
            throw new InvalidArgumentException("offsetsY LinearBuffer is too small.");
        }
        if($offsetsX->dtype()!==NDArray::int64 && $offsetsX->dtype()!==NDArray::uint64) {
            throw new InvalidArgumentException("offsetsX LinearBuffer data type must be int64.");
        }
        if($offsetsY->dtype()!==NDArray::int64 && $offsetsY->dtype()!==NDArray::uint64) {
            throw new InvalidArgumentException("offsetsY LinearBuffer data type must be int64.");
        }
        // Check Buffer X and Y
        if($X->dtype()!=$Y->dtype()||$alpha->dtype()!=$X->dtype()) {
            throw new InvalidArgumentException("Unmatch data type for A,X and Y");
        }
        $X_p = $ffi->cast("cl_mem",$X->_getId());
        $Y_p = $ffi->cast("cl_mem",$Y->_getId());

        $queue_p = $ffi->cast("cl_command_queue*",FFI::addr($queue->_getId()));
        $event_p = null;
        if($event) {
            $event_obj = $event->_ffi()->new("cl_event[1]");
            $event_p = $ffi->cast("cl_event[1]",$event_obj);
        }

        switch($X->dtype()) {
            case NDArray::float32:{
                $status = $ffi->CLBlastSaxpyBatched(
                    $n, $alpha->addr($offsetA),
                    $X_p, $ffi->cast("size_t *",$offsetsX->addr($offsetX)), $incX,
                    $Y_p, $ffi->cast("size_t *",$offsetsY->addr($offsetY)), $incY,
                    $batch_count,
                    $queue_p, $event_p
                );
                break;
            }
            case NDArray::float64:{
                $status = $ffi->CLBlastDaxpyBatched(
                    $n, $alpha->addr($offsetA),
                    $X_p, $ffi->cast("size_t *",$offsetsX->addr($offsetX)), $incX,
                    $Y_p, $ffi->cast("size_t *",$offsetsY->addr($offsetY)), $incY,
                    $batch_count,
                    $queue_p, $event_p
                );
                break;
            }
            default: {
                throw new InvalidArgumentException('Unsuppored data type');
            }
        }
        if($status!=self::CLBlastSuccess) {
            throw new RuntimeException("CLBlast?axpyBatched error=$status", $status);
        }
        if($event) {
            $event->_move($event_obj);
        }
    }

    public function gemmBatched(
        int $order,
        int $transA,
        int $transB,
        int $m,
        int $n,
        int $k,
        HostBuffer $alpha, int $offsetAlpha,
        DeviceBuffer $A, HostBuffer $offsetsA, int $offsetA, int $ldA,
        DeviceBuffer $B, HostBuffer $offsetsB, int $offsetB, int $ldB,
        HostBuffer $beta, int $offsetBeta,
        DeviceBuffer $C, HostBuffer $offsetsC, int $offsetC, int $ldC,
        int $batch_count,
        CommandQueue $queue,
        EventList $event=null,
    ) : void
    {
        $ffi = $this->ffi;
        if($m<=0) {
            throw new InvalidArgumentException("m must be greater than zero");
        }
        if($n<=0) {
            throw new InvalidArgumentException("n must be greater than zero");
        }
        if($k<=0) {
            throw new InvalidArgumentException("k must be greater than zero");
        }
        if($offsetAlpha<0) {
            throw new InvalidArgumentException("offsetAlpha must be greater than zero or equal");
        }
        if($offsetA<0) {
            throw new InvalidArgumentException("offsetA must be greater than zero or equal");
        }
        if($offsetB<0) {
            throw new InvalidArgumentException("offsetB must be greater than zero or equal");
        }
        if($offsetBeta<0) {
            throw new InvalidArgumentException("offsetBeta must be greater than zero or equal");
        }
        if($offsetC<0) {
            throw new InvalidArgumentException("offsetC must be greater than zero or equal");
        }
        if($batch_count<0) {
            throw new InvalidArgumentException("batch_count must be greater than zero or equal");
        }
        if($offsetAlpha+$batch_count>count($alpha)) {
            throw new InvalidArgumentException("alpha LinearBuffer is too small.");
        }
        if($offsetA+$batch_count>count($offsetsA)) {
            throw new InvalidArgumentException("offsetsA LinearBuffer is too small.");
        }
        if($offsetB+$batch_count>count($offsetsB)) {
            throw new InvalidArgumentException("offsetsB LinearBuffer is too small.");
        }
        if($offsetBeta+$batch_count>count($beta)) {
            throw new InvalidArgumentException("beta LinearBuffer is too small.");
        }
        if($offsetC+$batch_count>count($offsetsC)) {
            throw new InvalidArgumentException("offsetsC LinearBuffer is too small.");
        }

        if($offsetsA->dtype()!==NDArray::int64 && $offsetsA->dtype()!==NDArray::uint64) {
            throw new InvalidArgumentException("offsetsX LinearBuffer data type must be int64.");
        }
        if($offsetsB->dtype()!==NDArray::int64 && $offsetsB->dtype()!==NDArray::uint64) {
            throw new InvalidArgumentException("offsetsY LinearBuffer data type must be int64.");
        }
        if($offsetsC->dtype()!==NDArray::int64 && $offsetsC->dtype()!==NDArray::uint64) {
            throw new InvalidArgumentException("offsetsY LinearBuffer data type must be int64.");
        }
        // Check Buffer X and Y
        if($A->dtype()!=$B->dtype()||$A->dtype()!=$C->dtype()||
            $A->dtype()!=$alpha->dtype()||$A->dtype()!=$beta->dtype()) {
            throw new InvalidArgumentException("Unmatch data type for A,B,C,alpha and beta");
        }
        $A_p = $ffi->cast("cl_mem",$A->_getId());
        $B_p = $ffi->cast("cl_mem",$B->_getId());
        $C_p = $ffi->cast("cl_mem",$C->_getId());

        $queue_p = $ffi->cast("cl_command_queue*",FFI::addr($queue->_getId()));
        $event_p = null;
        if($event) {
            $event_obj = $event->_ffi()->new("cl_event[1]");
            $event_p = $ffi->cast("cl_event[1]",$event_obj);
        }

        switch($A->dtype()) {
            case NDArray::float32:{
                $status = $ffi->CLBlastSgemmBatched(
                    $order,
                    $transA,
                    $transB,
                    $m, $n, $k,
                    $alpha->addr($offsetAlpha),
                    $A_p, $ffi->cast("size_t *",$offsetsA->addr($offsetA)), $ldA,
                    $B_p, $ffi->cast("size_t *",$offsetsB->addr($offsetB)), $ldB,
                    $beta->addr($offsetBeta),
                    $C_p, $ffi->cast("size_t *",$offsetsC->addr($offsetC)), $ldC,
                    $batch_count,
                    $queue_p, $event_p
                );
                break;
            }
            case NDArray::float64:{
                $status = $ffi->CLBlastDgemmBatched(
                    $order,
                    $transA,
                    $transB,
                    $m, $n, $k,
                    $alpha->addr($offsetAlpha),
                    $A_p, $ffi->cast("size_t *",$offsetsA->addr($offsetA)), $ldA,
                    $B_p, $ffi->cast("size_t *",$offsetsB->addr($offsetB)), $ldB,
                    $beta->addr($offsetBeta),
                    $C_p, $ffi->cast("size_t *",$offsetsC->addr($offsetC)), $ldC,
                    $batch_count,
                    $queue_p, $event_p
                );
                break;
            }
            default: {
                throw new InvalidArgumentException('Unsuppored data type');
            }
        }
        if($status!=self::CLBlastSuccess) {
            throw new RuntimeException("CLBlast?gemmBatched error=$status", $status);
        }
        if($event) {
            $event->_move($event_obj);
        }
    }

    public function gemmStridedBatched(
        int $order,
        int $transA,
        int $transB,
        int $m,
        int $n,
        int $k,
        float|object $alpha,
        DeviceBuffer $A, int $offsetA, int $ldA, int $strideA,
        DeviceBuffer $B, int $offsetB, int $ldB, int $strideB,
        float|object $beta,
        DeviceBuffer $C, int $offsetC, int $ldC, int $strideC,
        int $batch_count,
        CommandQueue $queue,
        EventList $event=null,
    ) : void
    {
        $ffi = $this->ffi;
        $alt = $this->alt;
        if($m<=0) {
            throw new InvalidArgumentException("m must be greater than zero");
        }
        if($n<=0) {
            throw new InvalidArgumentException("n must be greater than zero");
        }
        if($k<=0) {
            throw new InvalidArgumentException("k must be greater than zero");
        }
        if($offsetA<0) {
            throw new InvalidArgumentException("offsetA must be greater than zero or equal");
        }
        if($offsetB<0) {
            throw new InvalidArgumentException("offsetB must be greater than zero or equal");
        }
        if($offsetC<0) {
            throw new InvalidArgumentException("offsetC must be greater than zero or equal");
        }
        if($batch_count<0) {
            throw new InvalidArgumentException("batch_count must be greater than zero or equal");
        }

        // Check Buffer X and Y
        if($A->dtype()!=$B->dtype()||$A->dtype()!=$C->dtype()) {
            throw new InvalidArgumentException("Unmatch data type for A,B and C");
        }
        // CLBlast does not support ConjNoTrans
        if($transA==BLASIF::ConjNoTrans) {
            throw new InvalidArgumentException("CLBlast does not support ConjNoTrans");
        }
        if($transB==BLASIF::ConjNoTrans) {
            throw new InvalidArgumentException("CLBlast does not support ConjNoTrans");
        }
        $A_p = $ffi->cast("cl_mem",$A->_getId());
        $B_p = $ffi->cast("cl_mem",$B->_getId());
        $C_p = $ffi->cast("cl_mem",$C->_getId());

        $queue_p = $ffi->cast("cl_command_queue*",FFI::addr($queue->_getId()));
        $event_p = null;
        if($event) {
            $event_obj = $event->_ffi()->new("cl_event[1]");
            $event_p = $ffi->cast("cl_event[1]",$event_obj);
        }

        switch($A->dtype()) {
            case NDArray::float32:{
                $status = $ffi->CLBlastSgemmStridedBatched(
                    $order,
                    $transA,
                    $transB,
                    $m, $n, $k,
                    $alpha,
                    $A_p, $offsetA, $ldA,$strideA,
                    $B_p, $offsetB, $ldB,$strideB,
                    $beta,
                    $C_p, $offsetC, $ldC,$strideC,
                    $batch_count,
                    $queue_p, $event_p
                );
                break;
            }
            case NDArray::float64:{
                $status = $ffi->CLBlastDgemmStridedBatched(
                    $order,
                    $transA,
                    $transB,
                    $m, $n, $k,
                    $alpha,
                    $A_p, $offsetA, $ldA,$strideA,
                    $B_p, $offsetB, $ldB,$strideB,
                    $beta,
                    $C_p, $offsetC, $ldC,$strideC,
                    $batch_count,
                    $queue_p, $event_p
                );
                break;
            }
            case NDArray::complex64:{
                $alpha = $this->toComplex($alpha,$A->dtype());
                $beta = $this->toComplex($beta,$A->dtype());
                $status = $alt->CLBlastCgemmStridedBatched(
                    $order,
                    $transA,
                    $transB,
                    $m, $n, $k,
                    $alpha,
                    $A_p, $offsetA, $ldA,$strideA,
                    $B_p, $offsetB, $ldB,$strideB,
                    $beta,
                    $C_p, $offsetC, $ldC,$strideC,
                    $batch_count,
                    $queue_p, $event_p
                );
                break;
            }
            case NDArray::complex128:{
                $alpha = $this->toComplex($alpha,$A->dtype());
                $beta = $this->toComplex($beta,$A->dtype());
                $status = $alt->CLBlastZgemmStridedBatched(
                    $order,
                    $transA,
                    $transB,
                    $m, $n, $k,
                    $alpha,
                    $A_p, $offsetA, $ldA,$strideA,
                    $B_p, $offsetB, $ldB,$strideB,
                    $beta,
                    $C_p, $offsetC, $ldC,$strideC,
                    $batch_count,
                    $queue_p, $event_p
                );
                break;
            }
            default: {
                throw new InvalidArgumentException('Unsuppored data type');
            }
        }
        if($status!=self::CLBlastSuccess) {
            throw new RuntimeException("CLBlast?gemmBatched error=$status", $status);
        }
        if($event) {
            $event->_move($event_obj);
        }
    }
}