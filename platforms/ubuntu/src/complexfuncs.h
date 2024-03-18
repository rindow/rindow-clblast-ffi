#define FFI_SCOPE "Rindow\\CLBlast\\FFI"
//#define FFI_LIB "librindowclblast.so"

/////////////////////////////////////////////
typedef int8_t                      cl_char;
typedef uint8_t                     cl_uchar;
typedef int16_t                     cl_short;
typedef uint16_t                    cl_ushort;
typedef int32_t                     cl_int;
typedef uint32_t                    cl_uint;
typedef int64_t                     cl_long;
typedef uint64_t                    cl_ulong;
typedef uint16_t                    cl_half;
typedef float                       cl_float;
typedef double                      cl_double;

typedef union _cl_float2 {
    cl_float   s[2];
} cl_float2;
typedef union _cl_double2 {
    cl_double   s[2];
} cl_double2;
//typedef enum CLBlastStatusCode_ {
//  CLBlastSuccess                   =   0, // CL_SUCCESS
//} CLBlastStatusCode;
typedef int CLBlastStatusCode;

/////////////////////////////////////////////
typedef struct _cl_platform_id *    cl_platform_id;
typedef struct _cl_device_id *      cl_device_id;
typedef struct _cl_context *        cl_context;
typedef struct _cl_command_queue *  cl_command_queue;
typedef struct _cl_mem *            cl_mem;
typedef struct _cl_program *        cl_program;
typedef struct _cl_kernel *         cl_kernel;
typedef struct _cl_event *          cl_event;
typedef struct _cl_sampler *        cl_sampler;
/////////////////////////////////////////////

// Matrix layout and transpose types
typedef enum CLBlastLayout_ { CLBlastLayoutRowMajor = 101,
                              CLBlastLayoutColMajor = 102 } CLBlastLayout;
typedef enum CLBlastTranspose_ { CLBlastTransposeNo = 111, CLBlastTransposeYes = 112,
                                 CLBlastTransposeConjugate = 113 } CLBlastTranspose;
typedef enum CLBlastTriangle_ { CLBlastTriangleUpper = 121,
                                CLBlastTriangleLower = 122 } CLBlastTriangle;
typedef enum CLBlastDiagonal_ { CLBlastDiagonalNonUnit = 131,
                                CLBlastDiagonalUnit = 132 } CLBlastDiagonal;
typedef enum CLBlastSide_ { CLBlastSideLeft = 141, CLBlastSideRight = 142 } CLBlastSide;
typedef enum CLBlastKernelMode_ { CLBlastKernelModeCrossCorrelation = 151, CLBlastKernelModeConvolution = 152 } CLBlastKernelMode;

// Precision enum (values in bits)
typedef enum CLBlastPrecision_ { CLBlastPrecisionHalf = 16, CLBlastPrecisionSingle = 32,
                                 CLBlastPrecisionDouble = 64, CLBlastPrecisionComplexSingle = 3232,
                                 CLBlastPrecisionComplexDouble = 6464 } CLBlastPrecision;


CLBlastStatusCode RindowCLBlastCscal(const size_t n,
                                          const void *alpha,
                                          cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode RindowCLBlastZscal(const size_t n,
                                          const void *alpha,
                                          cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode RindowCLBlastCaxpy(const size_t n,
                                          const void *alpha,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode RindowCLBlastZaxpy(const size_t n,
                                          const void *alpha,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode RindowCLBlastCgemv(const CLBlastLayout layout, const CLBlastTranspose a_transpose,
                                          const size_t m, const size_t n,
                                          const void *alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          const void *beta,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode RindowCLBlastZgemv(const CLBlastLayout layout, const CLBlastTranspose a_transpose,
                                          const size_t m, const size_t n,
                                          const void *alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          const void *beta,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode RindowCLBlastCgemm(const CLBlastLayout layout, const CLBlastTranspose a_transpose, const CLBlastTranspose b_transpose,
                                          const size_t m, const size_t n, const size_t k,
                                          const void *alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                          const void *beta,
                                          cl_mem c_buffer, const size_t c_offset, const size_t c_ld,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode RindowCLBlastZgemm(const CLBlastLayout layout, const CLBlastTranspose a_transpose, const CLBlastTranspose b_transpose,
                                          const size_t m, const size_t n, const size_t k,
                                          const void *alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                          const void *beta,
                                          cl_mem c_buffer, const size_t c_offset, const size_t c_ld,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode RindowCLBlastCsymm(const CLBlastLayout layout, const CLBlastSide side, const CLBlastTriangle triangle,
                                          const size_t m, const size_t n,
                                          const void *alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                          const void *beta,
                                          cl_mem c_buffer, const size_t c_offset, const size_t c_ld,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode RindowCLBlastZsymm(const CLBlastLayout layout, const CLBlastSide side, const CLBlastTriangle triangle,
                                          const size_t m, const size_t n,
                                          const void *alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                          const void *beta,
                                          cl_mem c_buffer, const size_t c_offset, const size_t c_ld,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode RindowCLBlastCsyrk(const CLBlastLayout layout, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose,
                                          const size_t n, const size_t k,
                                          const void *alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const void *beta,
                                          cl_mem c_buffer, const size_t c_offset, const size_t c_ld,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode RindowCLBlastZsyrk(const CLBlastLayout layout, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose,
                                          const size_t n, const size_t k,
                                          const void *alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const void *beta,
                                          cl_mem c_buffer, const size_t c_offset, const size_t c_ld,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode RindowCLBlastCsyr2k(const CLBlastLayout layout, const CLBlastTriangle triangle, const CLBlastTranspose ab_transpose,
                                           const size_t n, const size_t k,
                                           const void *alpha,
                                           const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                           const cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                           const void *beta,
                                           cl_mem c_buffer, const size_t c_offset, const size_t c_ld,
                                           cl_command_queue* queue, cl_event* event);
CLBlastStatusCode RindowCLBlastZsyr2k(const CLBlastLayout layout, const CLBlastTriangle triangle, const CLBlastTranspose ab_transpose,
                                           const size_t n, const size_t k,
                                           const void *alpha,
                                           const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                           const cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                           const void *beta,
                                           cl_mem c_buffer, const size_t c_offset, const size_t c_ld,
                                           cl_command_queue* queue, cl_event* event);
CLBlastStatusCode RindowCLBlastCtrmm(const CLBlastLayout layout, const CLBlastSide side, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose, const CLBlastDiagonal diagonal,
                                          const size_t m, const size_t n,
                                          const void *alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode RindowCLBlastZtrmm(const CLBlastLayout layout, const CLBlastSide side, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose, const CLBlastDiagonal diagonal,
                                          const size_t m, const size_t n,
                                          const void *alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode RindowCLBlastCtrsm(const CLBlastLayout layout, const CLBlastSide side, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose, const CLBlastDiagonal diagonal,
                                          const size_t m, const size_t n,
                                          const void *alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode RindowCLBlastZtrsm(const CLBlastLayout layout, const CLBlastSide side, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose, const CLBlastDiagonal diagonal,
                                          const size_t m, const size_t n,
                                          const void *alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode RindowCLBlastComatcopy(const CLBlastLayout layout, const CLBlastTranspose a_transpose,
                                              const size_t m, const size_t n,
                                              const void *alpha,
                                              const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                              cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                              cl_command_queue* queue, cl_event* event);
CLBlastStatusCode RindowCLBlastZomatcopy(const CLBlastLayout layout, const CLBlastTranspose a_transpose,
                                              const size_t m, const size_t n,
                                              const void *alpha,
                                              const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                              cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                              cl_command_queue* queue, cl_event* event);
CLBlastStatusCode RindowCLBlastCgemmStridedBatched(const CLBlastLayout layout, const CLBlastTranspose a_transpose, const CLBlastTranspose b_transpose,
                                                        const size_t m, const size_t n, const size_t k,
                                                        const void *alpha,
                                                        const cl_mem a_buffer, const size_t a_offset, const size_t a_ld, const size_t a_stride,
                                                        const cl_mem b_buffer, const size_t b_offset, const size_t b_ld, const size_t b_stride,
                                                        const void *beta,
                                                        cl_mem c_buffer, const size_t c_offset, const size_t c_ld, const size_t c_stride,
                                                        const size_t batch_count,
                                                        cl_command_queue* queue, cl_event* event);
CLBlastStatusCode RindowCLBlastZgemmStridedBatched(const CLBlastLayout layout, const CLBlastTranspose a_transpose, const CLBlastTranspose b_transpose,
                                                        const size_t m, const size_t n, const size_t k,
                                                        const void *alpha,
                                                        const cl_mem a_buffer, const size_t a_offset, const size_t a_ld, const size_t a_stride,
                                                        const cl_mem b_buffer, const size_t b_offset, const size_t b_ld, const size_t b_stride,
                                                        const void *beta,
                                                        cl_mem c_buffer, const size_t c_offset, const size_t c_ld, const size_t c_stride,
                                                        const size_t batch_count,
                                                        cl_command_queue* queue, cl_event* event);



