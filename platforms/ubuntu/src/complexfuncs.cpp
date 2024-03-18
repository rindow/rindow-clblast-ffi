#define CL_TARGET_OPENCL_VERSION 120
#include <CL/cl.h>
#include <stdio.h>
#include <clblast.h>
#include <clblast_c.h>
#include <complex>
#include <iostream>

extern "C" {
CLBlastStatusCode RindowCLBlastCscal(const size_t n,
                                          const cl_float2 *alpha,
                                          cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event) noexcept
{
    clblast::StatusCode status;
    try {
        status = clblast::Scal(
            n,
            std::complex<float>(alpha->s[0],alpha->s[1]),
            x_buffer, x_offset, x_inc,
            queue, event
        );
    } catch(std::exception &e) {
        const char *msg = e.what();
        fprintf(stderr,"CLBlast:%s\n",msg);
        status = (clblast::StatusCode)-1;
    } catch (...) {
        fprintf(stderr,"CLBlast: unknown error\n");
        status = (clblast::StatusCode)-1;
    }
    return (CLBlastStatusCode)status;
}

CLBlastStatusCode RindowCLBlastZscal(const size_t n,
                                          const cl_double2 *alpha,
                                          cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event) noexcept
{
    clblast::StatusCode status;
    try {
        status = clblast::Scal(
            n,
            std::complex<double>(alpha->s[0],alpha->s[1]),
            x_buffer, x_offset, x_inc,
            queue, event
        );
    } catch(std::exception &e) {
        const char *msg = e.what();
        fprintf(stderr,"CLBlast:%s\n",msg);
        status = (clblast::StatusCode)-1;
    } catch (...) {
        fprintf(stderr,"CLBlast: unknown error\n");
        status = (clblast::StatusCode)-1;
    }
    return (CLBlastStatusCode)status;
}

CLBlastStatusCode RindowCLBlastCaxpy(const size_t n,
                                          const cl_float2 *alpha,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event)
{
    clblast::StatusCode status;
    try {
        status = clblast::Axpy(
            n,
            std::complex<float>(alpha->s[0],alpha->s[1]),
            x_buffer, x_offset, x_inc,
            y_buffer, y_offset, y_inc,
            queue, event
        );
    } catch(std::exception &e) {
        const char *msg = e.what();
        fprintf(stderr,"CLBlast:%s\n",msg);
        status = (clblast::StatusCode)-1;
    } catch (...) {
        fprintf(stderr,"CLBlast: unknown error\n");
        status = (clblast::StatusCode)-1;
    }
    return (CLBlastStatusCode)status;
}
CLBlastStatusCode RindowCLBlastZaxpy(const size_t n,
                                          const cl_double2 *alpha,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event)
{
    clblast::StatusCode status;
    try {
        status = clblast::Axpy(
            n,
            std::complex<double>(alpha->s[0],alpha->s[1]),
            x_buffer, x_offset, x_inc,
            y_buffer, y_offset, y_inc,
            queue, event
        );
    } catch(std::exception &e) {
        const char *msg = e.what();
        fprintf(stderr,"CLBlast:%s\n",msg);
        status = (clblast::StatusCode)-1;
    } catch (...) {
        fprintf(stderr,"CLBlast: unknown error\n");
        status = (clblast::StatusCode)-1;
    }
    return (CLBlastStatusCode)status;
}

CLBlastStatusCode RindowCLBlastCgemv(const CLBlastLayout layout, const CLBlastTranspose a_transpose,
                                          const size_t m, const size_t n,
                                          const cl_float2 *alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          const cl_float2 *beta,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event)
{
    clblast::StatusCode status;
    try {
        status = clblast::Gemv(
            static_cast<clblast::Layout>(layout),
            static_cast<clblast::Transpose>(a_transpose),
            m, n,
            std::complex<float>(alpha->s[0],alpha->s[1]),
            a_buffer, a_offset, a_ld,
            x_buffer, x_offset, x_inc,
            std::complex<float>(beta->s[0],beta->s[1]),
            y_buffer, y_offset, y_inc,
            queue, event
        );
    } catch(std::exception &e) {
        const char *msg = e.what();
        fprintf(stderr,"CLBlast:%s\n",msg);
        status = (clblast::StatusCode)-1;
    } catch (...) {
        fprintf(stderr,"CLBlast: unknown error\n");
        status = (clblast::StatusCode)-1;
    }
    return (CLBlastStatusCode)status;
}
CLBlastStatusCode RindowCLBlastZgemv(const CLBlastLayout layout, const CLBlastTranspose a_transpose,
                                          const size_t m, const size_t n,
                                          const cl_double2 *alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          const cl_double2 *beta,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event)
{
    clblast::StatusCode status;
    try {
        status = clblast::Gemv(
            static_cast<clblast::Layout>(layout),
            static_cast<clblast::Transpose>(a_transpose),
            m, n,
            std::complex<double>(alpha->s[0],alpha->s[1]),
            a_buffer, a_offset, a_ld,
            x_buffer, x_offset, x_inc,
            std::complex<double>(beta->s[0],beta->s[1]),
            y_buffer, y_offset, y_inc,
            queue, event
        );
    } catch(std::exception &e) {
        const char *msg = e.what();
        fprintf(stderr,"CLBlast:%s\n",msg);
        status = (clblast::StatusCode)-1;
    } catch (...) {
        fprintf(stderr,"CLBlast: unknown error\n");
        status = (clblast::StatusCode)-1;
    }
    return (CLBlastStatusCode)status;
}

CLBlastStatusCode RindowCLBlastCgemm(const CLBlastLayout layout, const CLBlastTranspose a_transpose, const CLBlastTranspose b_transpose,
                                          const size_t m, const size_t n, const size_t k,
                                          const cl_float2 *alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                          const cl_float2 *beta,
                                          cl_mem c_buffer, const size_t c_offset, const size_t c_ld,
                                          cl_command_queue* queue, cl_event* event)
{
    clblast::StatusCode status;
    try {
        status = clblast::Gemm(
            static_cast<clblast::Layout>(layout),
            static_cast<clblast::Transpose>(a_transpose),
            static_cast<clblast::Transpose>(b_transpose),
            m, n, k,
            std::complex<float>(alpha->s[0],alpha->s[1]),
            a_buffer, a_offset, a_ld,
            b_buffer, b_offset, b_ld,
            std::complex<float>(beta->s[0],beta->s[1]),
            c_buffer, c_offset, c_ld,
            queue, event
        );
    } catch(std::exception &e) {
        const char *msg = e.what();
        fprintf(stderr,"CLBlast:%s\n",msg);
        status = (clblast::StatusCode)-1;
    } catch (...) {
        fprintf(stderr,"CLBlast: unknown error\n");
        status = (clblast::StatusCode)-1;
    }
    return (CLBlastStatusCode)status;
}

CLBlastStatusCode RindowCLBlastZgemm(const CLBlastLayout layout, const CLBlastTranspose a_transpose, const CLBlastTranspose b_transpose,
                                          const size_t m, const size_t n, const size_t k,
                                          const cl_double2 *alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                          const cl_double2 *beta,
                                          cl_mem c_buffer, const size_t c_offset, const size_t c_ld,
                                          cl_command_queue* queue, cl_event* event)
{
    clblast::StatusCode status;
    try {
        status = clblast::Gemm(
            static_cast<clblast::Layout>(layout),
            static_cast<clblast::Transpose>(a_transpose),
            static_cast<clblast::Transpose>(b_transpose),
            m, n, k,
            std::complex<double>(alpha->s[0],alpha->s[1]),
            a_buffer, a_offset, a_ld,
            b_buffer, b_offset, b_ld,
            std::complex<double>(beta->s[0],beta->s[1]),
            c_buffer, c_offset, c_ld,
            queue, event
        );
    } catch(std::exception &e) {
        const char *msg = e.what();
        fprintf(stderr,"CLBlast:%s\n",msg);
        status = (clblast::StatusCode)-1;
    } catch (...) {
        fprintf(stderr,"CLBlast: unknown error\n");
        status = (clblast::StatusCode)-1;
    }
    return (CLBlastStatusCode)status;
}

CLBlastStatusCode RindowCLBlastCsymm(const CLBlastLayout layout, const CLBlastSide side, const CLBlastTriangle triangle,
                                          const size_t m, const size_t n,
                                          const cl_float2 *alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                          const cl_float2 *beta,
                                          cl_mem c_buffer, const size_t c_offset, const size_t c_ld,
                                          cl_command_queue* queue, cl_event* event)
{
    clblast::StatusCode status;
    try {
        status = clblast::Symm(
            static_cast<clblast::Layout>(layout),
            static_cast<clblast::Side>(side),
            static_cast<clblast::Triangle>(triangle),
            m, n,
            std::complex<float>(alpha->s[0],alpha->s[1]),
            a_buffer, a_offset, a_ld,
            b_buffer, b_offset, b_ld,
            std::complex<float>(beta->s[0],beta->s[1]),
            c_buffer, c_offset, c_ld,
            queue, event
        );
    } catch(std::exception &e) {
        const char *msg = e.what();
        fprintf(stderr,"CLBlast:%s\n",msg);
        status = (clblast::StatusCode)-1;
    } catch (...) {
        fprintf(stderr,"CLBlast: unknown error\n");
        status = (clblast::StatusCode)-1;
    }
    return (CLBlastStatusCode)status;
}
CLBlastStatusCode RindowCLBlastZsymm(const CLBlastLayout layout, const CLBlastSide side, const CLBlastTriangle triangle,
                                          const size_t m, const size_t n,
                                          const cl_double2 *alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                          const cl_double2 *beta,
                                          cl_mem c_buffer, const size_t c_offset, const size_t c_ld,
                                          cl_command_queue* queue, cl_event* event)
{
    clblast::StatusCode status;
    try {
        status = clblast::Symm(
            static_cast<clblast::Layout>(layout),
            static_cast<clblast::Side>(side),
            static_cast<clblast::Triangle>(triangle),
            m, n,
            std::complex<double>(alpha->s[0],alpha->s[1]),
            a_buffer, a_offset, a_ld,
            b_buffer, b_offset, b_ld,
            std::complex<double>(beta->s[0],beta->s[1]),
            c_buffer, c_offset, c_ld,
            queue, event
        );
    } catch(std::exception &e) {
        const char *msg = e.what();
        fprintf(stderr,"CLBlast:%s\n",msg);
        status = (clblast::StatusCode)-1;
    } catch (...) {
        fprintf(stderr,"CLBlast: unknown error\n");
        status = (clblast::StatusCode)-1;
    }
    return (CLBlastStatusCode)status;
}
CLBlastStatusCode RindowCLBlastCsyrk(const CLBlastLayout layout, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose,
                                          const size_t n, const size_t k,
                                          const cl_float2 *alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const cl_float2 *beta,
                                          cl_mem c_buffer, const size_t c_offset, const size_t c_ld,
                                          cl_command_queue* queue, cl_event* event)
{
    clblast::StatusCode status;
    try {
        status = clblast::Syrk(
            static_cast<clblast::Layout>(layout),
            static_cast<clblast::Triangle>(triangle),
            static_cast<clblast::Transpose>(a_transpose),
            n, k,
            std::complex<float>(alpha->s[0],alpha->s[1]),
            a_buffer, a_offset, a_ld,
            std::complex<float>(beta->s[0],beta->s[1]),
            c_buffer, c_offset, c_ld,
            queue, event
        );
    } catch(std::exception &e) {
        const char *msg = e.what();
        fprintf(stderr,"CLBlast:%s\n",msg);
        status = (clblast::StatusCode)-1;
    } catch (...) {
        fprintf(stderr,"CLBlast: unknown error\n");
        status = (clblast::StatusCode)-1;
    }
    return (CLBlastStatusCode)status;
}
CLBlastStatusCode RindowCLBlastZsyrk(const CLBlastLayout layout, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose,
                                          const size_t n, const size_t k,
                                          const cl_double2 *alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const cl_double2 *beta,
                                          cl_mem c_buffer, const size_t c_offset, const size_t c_ld,
                                          cl_command_queue* queue, cl_event* event)
{
    clblast::StatusCode status;
    try {
        status = clblast::Syrk(
            static_cast<clblast::Layout>(layout),
            static_cast<clblast::Triangle>(triangle),
            static_cast<clblast::Transpose>(a_transpose),
            n, k,
            std::complex<double>(alpha->s[0],alpha->s[1]),
            a_buffer, a_offset, a_ld,
            std::complex<double>(beta->s[0],beta->s[1]),
            c_buffer, c_offset, c_ld,
            queue, event
        );
    } catch(std::exception &e) {
        const char *msg = e.what();
        fprintf(stderr,"CLBlast:%s\n",msg);
        status = (clblast::StatusCode)-1;
    } catch (...) {
        fprintf(stderr,"CLBlast: unknown error\n");
        status = (clblast::StatusCode)-1;
    }
    return (CLBlastStatusCode)status;
}

CLBlastStatusCode RindowCLBlastCsyr2k(const CLBlastLayout layout, const CLBlastTriangle triangle, const CLBlastTranspose ab_transpose,
                                           const size_t n, const size_t k,
                                           const cl_float2 *alpha,
                                           const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                           const cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                           const cl_float2 *beta,
                                           cl_mem c_buffer, const size_t c_offset, const size_t c_ld,
                                           cl_command_queue* queue, cl_event* event)
{
    clblast::StatusCode status;
    try {
        status = clblast::Syr2k(
            static_cast<clblast::Layout>(layout),
            static_cast<clblast::Triangle>(triangle),
            static_cast<clblast::Transpose>(ab_transpose),
            n, k,
            std::complex<float>(alpha->s[0],alpha->s[1]),
            a_buffer, a_offset, a_ld,
            b_buffer, b_offset, b_ld,
            std::complex<float>(beta->s[0],beta->s[1]),
            c_buffer, c_offset, c_ld,
            queue, event
        );
    } catch(std::exception &e) {
        const char *msg = e.what();
        fprintf(stderr,"CLBlast:%s\n",msg);
        status = (clblast::StatusCode)-1;
    } catch (...) {
        fprintf(stderr,"CLBlast: unknown error\n");
        status = (clblast::StatusCode)-1;
    }
    return (CLBlastStatusCode)status;
}
CLBlastStatusCode RindowCLBlastZsyr2k(const CLBlastLayout layout, const CLBlastTriangle triangle, const CLBlastTranspose ab_transpose,
                                           const size_t n, const size_t k,
                                           const cl_double2 *alpha,
                                           const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                           const cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                           const cl_double2 *beta,
                                           cl_mem c_buffer, const size_t c_offset, const size_t c_ld,
                                           cl_command_queue* queue, cl_event* event)
{
    clblast::StatusCode status;
    try {
        status = clblast::Syr2k(
            static_cast<clblast::Layout>(layout),
            static_cast<clblast::Triangle>(triangle),
            static_cast<clblast::Transpose>(ab_transpose),
            n, k,
            std::complex<double>(alpha->s[0],alpha->s[1]),
            a_buffer, a_offset, a_ld,
            b_buffer, b_offset, b_ld,
            std::complex<double>(beta->s[0],beta->s[1]),
            c_buffer, c_offset, c_ld,
            queue, event
        );
    } catch(std::exception &e) {
        const char *msg = e.what();
        fprintf(stderr,"CLBlast:%s\n",msg);
        status = (clblast::StatusCode)-1;
    } catch (...) {
        fprintf(stderr,"CLBlast: unknown error\n");
        status = (clblast::StatusCode)-1;
    }
    return (CLBlastStatusCode)status;
}
CLBlastStatusCode RindowCLBlastCtrmm(const CLBlastLayout layout, const CLBlastSide side, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose, const CLBlastDiagonal diagonal,
                                          const size_t m, const size_t n,
                                          const cl_float2 *alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                          cl_command_queue* queue, cl_event* event)
{
    clblast::StatusCode status;
    try {
        status = clblast::Trmm(
            static_cast<clblast::Layout>(layout),
            static_cast<clblast::Side>(side),
            static_cast<clblast::Triangle>(triangle),
            static_cast<clblast::Transpose>(a_transpose),
            static_cast<clblast::Diagonal>(diagonal),
            m, n,
            std::complex<float>(alpha->s[0],alpha->s[1]),
            a_buffer, a_offset, a_ld,
            b_buffer, b_offset, b_ld,
            queue, event
        );
    } catch(std::exception &e) {
        const char *msg = e.what();
        fprintf(stderr,"CLBlast:%s\n",msg);
        status = (clblast::StatusCode)-1;
    } catch (...) {
        fprintf(stderr,"CLBlast: unknown error\n");
        status = (clblast::StatusCode)-1;
    }
    return (CLBlastStatusCode)status;
}
CLBlastStatusCode RindowCLBlastZtrmm(const CLBlastLayout layout, const CLBlastSide side, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose, const CLBlastDiagonal diagonal,
                                          const size_t m, const size_t n,
                                          const cl_double2 *alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                          cl_command_queue* queue, cl_event* event)
{
    clblast::StatusCode status;
    try {
        status = clblast::Trmm(
            static_cast<clblast::Layout>(layout),
            static_cast<clblast::Side>(side),
            static_cast<clblast::Triangle>(triangle),
            static_cast<clblast::Transpose>(a_transpose),
            static_cast<clblast::Diagonal>(diagonal),
            m, n,
            std::complex<double>(alpha->s[0],alpha->s[1]),
            a_buffer, a_offset, a_ld,
            b_buffer, b_offset, b_ld,
            queue, event
        );
    } catch(std::exception &e) {
        const char *msg = e.what();
        fprintf(stderr,"CLBlast:%s\n",msg);
        status = (clblast::StatusCode)-1;
    } catch (...) {
        fprintf(stderr,"CLBlast: unknown error\n");
        status = (clblast::StatusCode)-1;
    }
    return (CLBlastStatusCode)status;
}

CLBlastStatusCode RindowCLBlastCtrsm(const CLBlastLayout layout, const CLBlastSide side, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose, const CLBlastDiagonal diagonal,
                                          const size_t m, const size_t n,
                                          const cl_float2 *alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                          cl_command_queue* queue, cl_event* event)
{
    clblast::StatusCode status;
    try {
        status = clblast::Trsm(
            static_cast<clblast::Layout>(layout),
            static_cast<clblast::Side>(side),
            static_cast<clblast::Triangle>(triangle),
            static_cast<clblast::Transpose>(a_transpose),
            static_cast<clblast::Diagonal>(diagonal),
            m, n,
            std::complex<float>(alpha->s[0],alpha->s[1]),
            a_buffer, a_offset, a_ld,
            b_buffer, b_offset, b_ld,
            queue, event
        );
    } catch(std::exception &e) {
        const char *msg = e.what();
        fprintf(stderr,"CLBlast:%s\n",msg);
        status = (clblast::StatusCode)-1;
    } catch (...) {
        fprintf(stderr,"CLBlast: unknown error\n");
        status = (clblast::StatusCode)-1;
    }
    return (CLBlastStatusCode)status;
}
CLBlastStatusCode RindowCLBlastZtrsm(const CLBlastLayout layout, const CLBlastSide side, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose, const CLBlastDiagonal diagonal,
                                          const size_t m, const size_t n,
                                          const cl_double2 *alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                          cl_command_queue* queue, cl_event* event)
{
    clblast::StatusCode status;
    try {
        status = clblast::Trsm(
            static_cast<clblast::Layout>(layout),
            static_cast<clblast::Side>(side),
            static_cast<clblast::Triangle>(triangle),
            static_cast<clblast::Transpose>(a_transpose),
            static_cast<clblast::Diagonal>(diagonal),
            m, n,
            std::complex<double>(alpha->s[0],alpha->s[1]),
            a_buffer, a_offset, a_ld,
            b_buffer, b_offset, b_ld,
            queue, event
        );
    } catch(std::exception &e) {
        const char *msg = e.what();
        fprintf(stderr,"CLBlast:%s\n",msg);
        status = (clblast::StatusCode)-1;
    } catch (...) {
        fprintf(stderr,"CLBlast: unknown error\n");
        status = (clblast::StatusCode)-1;
    }
    return (CLBlastStatusCode)status;
}

CLBlastStatusCode RindowCLBlastComatcopy(const CLBlastLayout layout, const CLBlastTranspose a_transpose,
                                              const size_t m, const size_t n,
                                              const cl_float2 *alpha,
                                              const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                              cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                              cl_command_queue* queue, cl_event* event)
{
    clblast::StatusCode status;
    try {
        status = clblast::Omatcopy(
            static_cast<clblast::Layout>(layout),
            static_cast<clblast::Transpose>(a_transpose),
            m, n,
            std::complex<float>(alpha->s[0],alpha->s[1]),
            a_buffer, a_offset, a_ld,
            b_buffer, b_offset, b_ld,
            queue, event
        );
    } catch(std::exception &e) {
        const char *msg = e.what();
        fprintf(stderr,"CLBlast:%s\n",msg);
        status = (clblast::StatusCode)-1;
    } catch (...) {
        fprintf(stderr,"CLBlast: unknown error\n");
        status = (clblast::StatusCode)-1;
    }
    return (CLBlastStatusCode)status;
}

CLBlastStatusCode RindowCLBlastZomatcopy(const CLBlastLayout layout, const CLBlastTranspose a_transpose,
                                              const size_t m, const size_t n,
                                              const cl_double2 *alpha,
                                              const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                              cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                              cl_command_queue* queue, cl_event* event)
{
    clblast::StatusCode status;
    try {
        status = clblast::Omatcopy(
            static_cast<clblast::Layout>(layout),
            static_cast<clblast::Transpose>(a_transpose),
            m, n,
            std::complex<double>(alpha->s[0],alpha->s[1]),
            a_buffer, a_offset, a_ld,
            b_buffer, b_offset, b_ld,
            queue, event
        );
    } catch(std::exception &e) {
        const char *msg = e.what();
        fprintf(stderr,"CLBlast:%s\n",msg);
        status = (clblast::StatusCode)-1;
    } catch (...) {
        fprintf(stderr,"CLBlast: unknown error\n");
        status = (clblast::StatusCode)-1;
    }
    return (CLBlastStatusCode)status;
}
CLBlastStatusCode RindowCLBlastCgemmStridedBatched(const CLBlastLayout layout, const CLBlastTranspose a_transpose, const CLBlastTranspose b_transpose,
                                                        const size_t m, const size_t n, const size_t k,
                                                        const cl_float2 *alpha,
                                                        const cl_mem a_buffer, const size_t a_offset, const size_t a_ld, const size_t a_stride,
                                                        const cl_mem b_buffer, const size_t b_offset, const size_t b_ld, const size_t b_stride,
                                                        const cl_float2 *beta,
                                                        cl_mem c_buffer, const size_t c_offset, const size_t c_ld, const size_t c_stride,
                                                        const size_t batch_count,
                                                        cl_command_queue* queue, cl_event* event)
{
    clblast::StatusCode status;
    try {
        status = clblast::GemmStridedBatched(
            static_cast<clblast::Layout>(layout),
            static_cast<clblast::Transpose>(a_transpose),
            static_cast<clblast::Transpose>(b_transpose),
            m, n, k,
            std::complex<float>(alpha->s[0],alpha->s[1]),
            a_buffer, a_offset, a_ld, a_stride,
            b_buffer, b_offset, b_ld, b_stride,
            std::complex<float>(beta->s[0],beta->s[1]),
            c_buffer, c_offset, c_ld, c_stride,
            batch_count,
            queue, event
        );
    } catch(std::exception &e) {
        const char *msg = e.what();
        fprintf(stderr,"CLBlast:%s\n",msg);
        status = (clblast::StatusCode)-1;
    } catch (...) {
        fprintf(stderr,"CLBlast: unknown error\n");
        status = (clblast::StatusCode)-1;
    }
    return (CLBlastStatusCode)status;
}
CLBlastStatusCode RindowCLBlastZgemmStridedBatched(const CLBlastLayout layout, const CLBlastTranspose a_transpose, const CLBlastTranspose b_transpose,
                                                        const size_t m, const size_t n, const size_t k,
                                                        const cl_double2 *alpha,
                                                        const cl_mem a_buffer, const size_t a_offset, const size_t a_ld, const size_t a_stride,
                                                        const cl_mem b_buffer, const size_t b_offset, const size_t b_ld, const size_t b_stride,
                                                        const cl_double2 *beta,
                                                        cl_mem c_buffer, const size_t c_offset, const size_t c_ld, const size_t c_stride,
                                                        const size_t batch_count,
                                                        cl_command_queue* queue, cl_event* event)
{
    clblast::StatusCode status;
    try {
        status = clblast::GemmStridedBatched(
            static_cast<clblast::Layout>(layout),
            static_cast<clblast::Transpose>(a_transpose),
            static_cast<clblast::Transpose>(b_transpose),
            m, n, k,
            std::complex<double>(alpha->s[0],alpha->s[1]),
            a_buffer, a_offset, a_ld, a_stride,
            b_buffer, b_offset, b_ld, b_stride,
            std::complex<double>(beta->s[0],beta->s[1]),
            c_buffer, c_offset, c_ld, c_stride,
            batch_count,
            queue, event
        );
    } catch(std::exception &e) {
        const char *msg = e.what();
        fprintf(stderr,"CLBlast:%s\n",msg);
        status = (clblast::StatusCode)-1;
    } catch (...) {
        fprintf(stderr,"CLBlast: unknown error\n");
        status = (clblast::StatusCode)-1;
    }
    return (CLBlastStatusCode)status;
}

}

