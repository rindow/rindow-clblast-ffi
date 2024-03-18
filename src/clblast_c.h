#define FFI_SCOPE "Rindow\\CLBlast\\FFI"
//#define FFI_LIB "clblast.dll"

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

/////////////////////////////////////////////
//typedef struct _cl_platform_id *    cl_platform_id;
//typedef struct _cl_device_id *      cl_device_id;
//typedef struct _cl_context *        cl_context;
//typedef struct _cl_command_queue *  cl_command_queue;
//typedef struct _cl_mem *            cl_mem;
//typedef struct _cl_program *        cl_program;
//typedef struct _cl_kernel *         cl_kernel;
//typedef struct _cl_event *          cl_event;
//typedef struct _cl_sampler *        cl_sampler;
/////////////////////////////////////////////
/////////////////////////////////////////////
typedef void*           cl_id_porinter;
typedef cl_id_porinter  cl_platform_id;
typedef cl_id_porinter  cl_device_id;
typedef cl_id_porinter  cl_context;
typedef cl_id_porinter  cl_command_queue;
typedef cl_id_porinter  cl_mem;
typedef cl_id_porinter  cl_program;
typedef cl_id_porinter  cl_kernel;
typedef cl_id_porinter  cl_event;
typedef cl_id_porinter  cl_sampler;
/////////////////////////////////////////////


// Status codes. These codes can be returned by functions declared in this header file. The error
// codes match either the standard OpenCL error codes or the clBLAS error codes. 
typedef enum CLBlastStatusCode_ {

  // Status codes in common with the OpenCL standard
  CLBlastSuccess                   =   0, // CL_SUCCESS
  CLBlastOpenCLCompilerNotAvailable=  -3, // CL_COMPILER_NOT_AVAILABLE
  CLBlastTempBufferAllocFailure    =  -4, // CL_MEM_OBJECT_ALLOCATION_FAILURE
  CLBlastOpenCLOutOfResources      =  -5, // CL_OUT_OF_RESOURCES
  CLBlastOpenCLOutOfHostMemory     =  -6, // CL_OUT_OF_HOST_MEMORY
  CLBlastOpenCLBuildProgramFailure = -11, // CL_BUILD_PROGRAM_FAILURE: OpenCL compilation error
  CLBlastInvalidValue              = -30, // CL_INVALID_VALUE
  CLBlastInvalidCommandQueue       = -36, // CL_INVALID_COMMAND_QUEUE
  CLBlastInvalidMemObject          = -38, // CL_INVALID_MEM_OBJECT
  CLBlastInvalidBinary             = -42, // CL_INVALID_BINARY
  CLBlastInvalidBuildOptions       = -43, // CL_INVALID_BUILD_OPTIONS
  CLBlastInvalidProgram            = -44, // CL_INVALID_PROGRAM
  CLBlastInvalidProgramExecutable  = -45, // CL_INVALID_PROGRAM_EXECUTABLE
  CLBlastInvalidKernelName         = -46, // CL_INVALID_KERNEL_NAME
  CLBlastInvalidKernelDefinition   = -47, // CL_INVALID_KERNEL_DEFINITION
  CLBlastInvalidKernel             = -48, // CL_INVALID_KERNEL
  CLBlastInvalidArgIndex           = -49, // CL_INVALID_ARG_INDEX
  CLBlastInvalidArgValue           = -50, // CL_INVALID_ARG_VALUE
  CLBlastInvalidArgSize            = -51, // CL_INVALID_ARG_SIZE
  CLBlastInvalidKernelArgs         = -52, // CL_INVALID_KERNEL_ARGS
  CLBlastInvalidLocalNumDimensions = -53, // CL_INVALID_WORK_DIMENSION: Too many thread dimensions
  CLBlastInvalidLocalThreadsTotal  = -54, // CL_INVALID_WORK_GROUP_SIZE: Too many threads in total
  CLBlastInvalidLocalThreadsDim    = -55, // CL_INVALID_WORK_ITEM_SIZE: ... or for a specific dimension
  CLBlastInvalidGlobalOffset       = -56, // CL_INVALID_GLOBAL_OFFSET
  CLBlastInvalidEventWaitList      = -57, // CL_INVALID_EVENT_WAIT_LIST
  CLBlastInvalidEvent              = -58, // CL_INVALID_EVENT
  CLBlastInvalidOperation          = -59, // CL_INVALID_OPERATION
  CLBlastInvalidBufferSize         = -61, // CL_INVALID_BUFFER_SIZE
  CLBlastInvalidGlobalWorkSize     = -63, // CL_INVALID_GLOBAL_WORK_SIZE

  // Status codes in common with the clBLAS library
  CLBlastNotImplemented            = -1024, // Routine or functionality not implemented yet
  CLBlastInvalidMatrixA            = -1022, // Matrix A is not a valid OpenCL buffer
  CLBlastInvalidMatrixB            = -1021, // Matrix B is not a valid OpenCL buffer
  CLBlastInvalidMatrixC            = -1020, // Matrix C is not a valid OpenCL buffer
  CLBlastInvalidVectorX            = -1019, // Vector X is not a valid OpenCL buffer
  CLBlastInvalidVectorY            = -1018, // Vector Y is not a valid OpenCL buffer
  CLBlastInvalidDimension          = -1017, // Dimensions M, N, and K have to be larger than zero
  CLBlastInvalidLeadDimA           = -1016, // LD of A is smaller than the matrix's first dimension
  CLBlastInvalidLeadDimB           = -1015, // LD of B is smaller than the matrix's first dimension
  CLBlastInvalidLeadDimC           = -1014, // LD of C is smaller than the matrix's first dimension
  CLBlastInvalidIncrementX         = -1013, // Increment of vector X cannot be zero
  CLBlastInvalidIncrementY         = -1012, // Increment of vector Y cannot be zero
  CLBlastInsufficientMemoryA       = -1011, // Matrix A's OpenCL buffer is too small
  CLBlastInsufficientMemoryB       = -1010, // Matrix B's OpenCL buffer is too small
  CLBlastInsufficientMemoryC       = -1009, // Matrix C's OpenCL buffer is too small
  CLBlastInsufficientMemoryX       = -1008, // Vector X's OpenCL buffer is too small
  CLBlastInsufficientMemoryY       = -1007, // Vector Y's OpenCL buffer is too small

  // Custom additional status codes for CLBlast
  CLBlastInsufficientMemoryTemp    = -2050, // Temporary buffer provided to GEMM routine is too small
  CLBlastInvalidBatchCount         = -2049, // The batch count needs to be positive
  CLBlastInvalidOverrideKernel     = -2048, // Trying to override parameters for an invalid kernel
  CLBlastMissingOverrideParameter  = -2047, // Missing override parameter(s) for the target kernel
  CLBlastInvalidLocalMemUsage      = -2046, // Not enough local memory available on this device
  CLBlastNoHalfPrecision           = -2045, // Half precision (16-bits) not supported by the device
  CLBlastNoDoublePrecision         = -2044, // Double precision (64-bits) not supported by the device
  CLBlastInvalidVectorScalar       = -2043, // The unit-sized vector is not a valid OpenCL buffer
  CLBlastInsufficientMemoryScalar  = -2042, // The unit-sized vector's OpenCL buffer is too small
  CLBlastDatabaseError             = -2041, // Entry for the device was not found in the database
  CLBlastUnknownError              = -2040, // A catch-all error code representing an unspecified error
  CLBlastUnexpectedError           = -2039, // A catch-all error code representing an unexpected exception
} CLBlastStatusCode;

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

// =================================================================================================
// BLAS level-1 (vector-vector) routines
// =================================================================================================

// Generate givens plane rotation: SROTG/DROTG
CLBlastStatusCode CLBlastSrotg(cl_mem sa_buffer, const size_t sa_offset,
                                          cl_mem sb_buffer, const size_t sb_offset,
                                          cl_mem sc_buffer, const size_t sc_offset,
                                          cl_mem ss_buffer, const size_t ss_offset,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastDrotg(cl_mem sa_buffer, const size_t sa_offset,
                                          cl_mem sb_buffer, const size_t sb_offset,
                                          cl_mem sc_buffer, const size_t sc_offset,
                                          cl_mem ss_buffer, const size_t ss_offset,
                                          cl_command_queue* queue, cl_event* event);

// Generate modified givens plane rotation: SROTMG/DROTMG
CLBlastStatusCode CLBlastSrotmg(cl_mem sd1_buffer, const size_t sd1_offset,
                                           cl_mem sd2_buffer, const size_t sd2_offset,
                                           cl_mem sx1_buffer, const size_t sx1_offset,
                                           const cl_mem sy1_buffer, const size_t sy1_offset,
                                           cl_mem sparam_buffer, const size_t sparam_offset,
                                           cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastDrotmg(cl_mem sd1_buffer, const size_t sd1_offset,
                                           cl_mem sd2_buffer, const size_t sd2_offset,
                                           cl_mem sx1_buffer, const size_t sx1_offset,
                                           const cl_mem sy1_buffer, const size_t sy1_offset,
                                           cl_mem sparam_buffer, const size_t sparam_offset,
                                           cl_command_queue* queue, cl_event* event);

// Apply givens plane rotation: SROT/DROT
CLBlastStatusCode CLBlastSrot(const size_t n,
                                         cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                         cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                         const float cos,
                                         const float sin,
                                         cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastDrot(const size_t n,
                                         cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                         cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                         const double cos,
                                         const double sin,
                                         cl_command_queue* queue, cl_event* event);

// Apply modified givens plane rotation: SROTM/DROTM
CLBlastStatusCode CLBlastSrotm(const size_t n,
                                          cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_mem sparam_buffer, const size_t sparam_offset,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastDrotm(const size_t n,
                                          cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_mem sparam_buffer, const size_t sparam_offset,
                                          cl_command_queue* queue, cl_event* event);

// Swap two vectors: SSWAP/DSWAP/CSWAP/ZSWAP/HSWAP
CLBlastStatusCode CLBlastSswap(const size_t n,
                                          cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastDswap(const size_t n,
                                          cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastCswap(const size_t n,
                                          cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastZswap(const size_t n,
                                          cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastHswap(const size_t n,
                                          cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event);

// Vector scaling: SSCAL/DSCAL/CSCAL/ZSCAL/HSCAL
CLBlastStatusCode CLBlastSscal(const size_t n,
                                          const float alpha,
                                          cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastDscal(const size_t n,
                                          const double alpha,
                                          cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastCscal(const size_t n,
                                          const cl_float2 alpha,
                                          cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastZscal(const size_t n,
                                          const cl_double2 alpha,
                                          cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastHscal(const size_t n,
                                          const cl_half alpha,
                                          cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);

// Vector copy: SCOPY/DCOPY/CCOPY/ZCOPY/HCOPY
CLBlastStatusCode CLBlastScopy(const size_t n,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastDcopy(const size_t n,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastCcopy(const size_t n,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastZcopy(const size_t n,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastHcopy(const size_t n,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event);

// Vector-times-constant plus vector: SAXPY/DAXPY/CAXPY/ZAXPY/HAXPY
CLBlastStatusCode CLBlastSaxpy(const size_t n,
                                          const float alpha,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastDaxpy(const size_t n,
                                          const double alpha,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastCaxpy(const size_t n,
                                          const cl_float2 alpha,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastZaxpy(const size_t n,
                                          const cl_double2 alpha,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastHaxpy(const size_t n,
                                          const cl_half alpha,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event);

// Dot product of two vectors: SDOT/DDOT/HDOT
CLBlastStatusCode CLBlastSdot(const size_t n,
                                         cl_mem dot_buffer, const size_t dot_offset,
                                         const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                         const cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                         cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastDdot(const size_t n,
                                         cl_mem dot_buffer, const size_t dot_offset,
                                         const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                         const cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                         cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastHdot(const size_t n,
                                         cl_mem dot_buffer, const size_t dot_offset,
                                         const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                         const cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                         cl_command_queue* queue, cl_event* event);

// Dot product of two complex vectors: CDOTU/ZDOTU
CLBlastStatusCode CLBlastCdotu(const size_t n,
                                          cl_mem dot_buffer, const size_t dot_offset,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          const cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastZdotu(const size_t n,
                                          cl_mem dot_buffer, const size_t dot_offset,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          const cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event);

// Dot product of two complex vectors, one conjugated: CDOTC/ZDOTC
CLBlastStatusCode CLBlastCdotc(const size_t n,
                                          cl_mem dot_buffer, const size_t dot_offset,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          const cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastZdotc(const size_t n,
                                          cl_mem dot_buffer, const size_t dot_offset,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          const cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event);

// Euclidian norm of a vector: SNRM2/DNRM2/ScNRM2/DzNRM2/HNRM2
CLBlastStatusCode CLBlastSnrm2(const size_t n,
                                          cl_mem nrm2_buffer, const size_t nrm2_offset,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastDnrm2(const size_t n,
                                          cl_mem nrm2_buffer, const size_t nrm2_offset,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastScnrm2(const size_t n,
                                          cl_mem nrm2_buffer, const size_t nrm2_offset,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastDznrm2(const size_t n,
                                          cl_mem nrm2_buffer, const size_t nrm2_offset,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastHnrm2(const size_t n,
                                          cl_mem nrm2_buffer, const size_t nrm2_offset,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);

// Absolute sum of values in a vector: SASUM/DASUM/ScASUM/DzASUM/HASUM
CLBlastStatusCode CLBlastSasum(const size_t n,
                                          cl_mem asum_buffer, const size_t asum_offset,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastDasum(const size_t n,
                                          cl_mem asum_buffer, const size_t asum_offset,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastScasum(const size_t n,
                                          cl_mem asum_buffer, const size_t asum_offset,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastDzasum(const size_t n,
                                          cl_mem asum_buffer, const size_t asum_offset,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastHasum(const size_t n,
                                          cl_mem asum_buffer, const size_t asum_offset,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);

// Sum of values in a vector (non-BLAS function): SSUM/DSUM/ScSUM/DzSUM/HSUM
CLBlastStatusCode CLBlastSsum(const size_t n,
                                         cl_mem sum_buffer, const size_t sum_offset,
                                         const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                         cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastDsum(const size_t n,
                                         cl_mem sum_buffer, const size_t sum_offset,
                                         const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                         cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastScsum(const size_t n,
                                         cl_mem sum_buffer, const size_t sum_offset,
                                         const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                         cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastDzsum(const size_t n,
                                         cl_mem sum_buffer, const size_t sum_offset,
                                         const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                         cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastHsum(const size_t n,
                                         cl_mem sum_buffer, const size_t sum_offset,
                                         const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                         cl_command_queue* queue, cl_event* event);

// Index of absolute maximum value in a vector: iSAMAX/iDAMAX/iCAMAX/iZAMAX/iHAMAX
CLBlastStatusCode CLBlastiSamax(const size_t n,
                                          cl_mem imax_buffer, const size_t imax_offset,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastiDamax(const size_t n,
                                          cl_mem imax_buffer, const size_t imax_offset,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastiCamax(const size_t n,
                                          cl_mem imax_buffer, const size_t imax_offset,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastiZamax(const size_t n,
                                          cl_mem imax_buffer, const size_t imax_offset,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastiHamax(const size_t n,
                                          cl_mem imax_buffer, const size_t imax_offset,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);

// Index of absolute minimum value in a vector (non-BLAS function): iSAMIN/iDAMIN/iCAMIN/iZAMIN/iHAMIN
CLBlastStatusCode CLBlastiSamin(const size_t n,
                                          cl_mem imin_buffer, const size_t imin_offset,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastiDamin(const size_t n,
                                          cl_mem imin_buffer, const size_t imin_offset,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastiCamin(const size_t n,
                                          cl_mem imin_buffer, const size_t imin_offset,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastiZamin(const size_t n,
                                          cl_mem imin_buffer, const size_t imin_offset,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastiHamin(const size_t n,
                                          cl_mem imin_buffer, const size_t imin_offset,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);

// Index of maximum value in a vector (non-BLAS function): iSMAX/iDMAX/iCMAX/iZMAX/iHMAX
CLBlastStatusCode CLBlastiSmax(const size_t n,
                                         cl_mem imax_buffer, const size_t imax_offset,
                                         const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                         cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastiDmax(const size_t n,
                                         cl_mem imax_buffer, const size_t imax_offset,
                                         const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                         cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastiCmax(const size_t n,
                                         cl_mem imax_buffer, const size_t imax_offset,
                                         const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                         cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastiZmax(const size_t n,
                                         cl_mem imax_buffer, const size_t imax_offset,
                                         const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                         cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastiHmax(const size_t n,
                                         cl_mem imax_buffer, const size_t imax_offset,
                                         const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                         cl_command_queue* queue, cl_event* event);

// Index of minimum value in a vector (non-BLAS function): iSMIN/iDMIN/iCMIN/iZMIN/iHMIN
CLBlastStatusCode CLBlastiSmin(const size_t n,
                                         cl_mem imin_buffer, const size_t imin_offset,
                                         const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                         cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastiDmin(const size_t n,
                                         cl_mem imin_buffer, const size_t imin_offset,
                                         const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                         cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastiCmin(const size_t n,
                                         cl_mem imin_buffer, const size_t imin_offset,
                                         const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                         cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastiZmin(const size_t n,
                                         cl_mem imin_buffer, const size_t imin_offset,
                                         const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                         cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastiHmin(const size_t n,
                                         cl_mem imin_buffer, const size_t imin_offset,
                                         const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                         cl_command_queue* queue, cl_event* event);

// =================================================================================================
// BLAS level-2 (matrix-vector) routines
// =================================================================================================

// General matrix-vector multiplication: SGEMV/DGEMV/CGEMV/ZGEMV/HGEMV
CLBlastStatusCode CLBlastSgemv(const CLBlastLayout layout, const CLBlastTranspose a_transpose,
                                          const size_t m, const size_t n,
                                          const float alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          const float beta,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastDgemv(const CLBlastLayout layout, const CLBlastTranspose a_transpose,
                                          const size_t m, const size_t n,
                                          const double alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          const double beta,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastCgemv(const CLBlastLayout layout, const CLBlastTranspose a_transpose,
                                          const size_t m, const size_t n,
                                          const cl_float2 alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          const cl_float2 beta,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastZgemv(const CLBlastLayout layout, const CLBlastTranspose a_transpose,
                                          const size_t m, const size_t n,
                                          const cl_double2 alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          const cl_double2 beta,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastHgemv(const CLBlastLayout layout, const CLBlastTranspose a_transpose,
                                          const size_t m, const size_t n,
                                          const cl_half alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          const cl_half beta,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event);

// General banded matrix-vector multiplication: SGBMV/DGBMV/CGBMV/ZGBMV/HGBMV
CLBlastStatusCode CLBlastSgbmv(const CLBlastLayout layout, const CLBlastTranspose a_transpose,
                                          const size_t m, const size_t n, const size_t kl, const size_t ku,
                                          const float alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          const float beta,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastDgbmv(const CLBlastLayout layout, const CLBlastTranspose a_transpose,
                                          const size_t m, const size_t n, const size_t kl, const size_t ku,
                                          const double alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          const double beta,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastCgbmv(const CLBlastLayout layout, const CLBlastTranspose a_transpose,
                                          const size_t m, const size_t n, const size_t kl, const size_t ku,
                                          const cl_float2 alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          const cl_float2 beta,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastZgbmv(const CLBlastLayout layout, const CLBlastTranspose a_transpose,
                                          const size_t m, const size_t n, const size_t kl, const size_t ku,
                                          const cl_double2 alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          const cl_double2 beta,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastHgbmv(const CLBlastLayout layout, const CLBlastTranspose a_transpose,
                                          const size_t m, const size_t n, const size_t kl, const size_t ku,
                                          const cl_half alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          const cl_half beta,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event);

// Hermitian matrix-vector multiplication: CHEMV/ZHEMV
CLBlastStatusCode CLBlastChemv(const CLBlastLayout layout, const CLBlastTriangle triangle,
                                          const size_t n,
                                          const cl_float2 alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          const cl_float2 beta,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastZhemv(const CLBlastLayout layout, const CLBlastTriangle triangle,
                                          const size_t n,
                                          const cl_double2 alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          const cl_double2 beta,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event);

// Hermitian banded matrix-vector multiplication: CHBMV/ZHBMV
CLBlastStatusCode CLBlastChbmv(const CLBlastLayout layout, const CLBlastTriangle triangle,
                                          const size_t n, const size_t k,
                                          const cl_float2 alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          const cl_float2 beta,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastZhbmv(const CLBlastLayout layout, const CLBlastTriangle triangle,
                                          const size_t n, const size_t k,
                                          const cl_double2 alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          const cl_double2 beta,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event);

// Hermitian packed matrix-vector multiplication: CHPMV/ZHPMV
CLBlastStatusCode CLBlastChpmv(const CLBlastLayout layout, const CLBlastTriangle triangle,
                                          const size_t n,
                                          const cl_float2 alpha,
                                          const cl_mem ap_buffer, const size_t ap_offset,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          const cl_float2 beta,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastZhpmv(const CLBlastLayout layout, const CLBlastTriangle triangle,
                                          const size_t n,
                                          const cl_double2 alpha,
                                          const cl_mem ap_buffer, const size_t ap_offset,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          const cl_double2 beta,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event);

// Symmetric matrix-vector multiplication: SSYMV/DSYMV/HSYMV
CLBlastStatusCode CLBlastSsymv(const CLBlastLayout layout, const CLBlastTriangle triangle,
                                          const size_t n,
                                          const float alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          const float beta,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastDsymv(const CLBlastLayout layout, const CLBlastTriangle triangle,
                                          const size_t n,
                                          const double alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          const double beta,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastHsymv(const CLBlastLayout layout, const CLBlastTriangle triangle,
                                          const size_t n,
                                          const cl_half alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          const cl_half beta,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event);

// Symmetric banded matrix-vector multiplication: SSBMV/DSBMV/HSBMV
CLBlastStatusCode CLBlastSsbmv(const CLBlastLayout layout, const CLBlastTriangle triangle,
                                          const size_t n, const size_t k,
                                          const float alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          const float beta,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastDsbmv(const CLBlastLayout layout, const CLBlastTriangle triangle,
                                          const size_t n, const size_t k,
                                          const double alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          const double beta,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastHsbmv(const CLBlastLayout layout, const CLBlastTriangle triangle,
                                          const size_t n, const size_t k,
                                          const cl_half alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          const cl_half beta,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event);

// Symmetric packed matrix-vector multiplication: SSPMV/DSPMV/HSPMV
CLBlastStatusCode CLBlastSspmv(const CLBlastLayout layout, const CLBlastTriangle triangle,
                                          const size_t n,
                                          const float alpha,
                                          const cl_mem ap_buffer, const size_t ap_offset,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          const float beta,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastDspmv(const CLBlastLayout layout, const CLBlastTriangle triangle,
                                          const size_t n,
                                          const double alpha,
                                          const cl_mem ap_buffer, const size_t ap_offset,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          const double beta,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastHspmv(const CLBlastLayout layout, const CLBlastTriangle triangle,
                                          const size_t n,
                                          const cl_half alpha,
                                          const cl_mem ap_buffer, const size_t ap_offset,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          const cl_half beta,
                                          cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_command_queue* queue, cl_event* event);

// Triangular matrix-vector multiplication: STRMV/DTRMV/CTRMV/ZTRMV/HTRMV
CLBlastStatusCode CLBlastStrmv(const CLBlastLayout layout, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose, const CLBlastDiagonal diagonal,
                                          const size_t n,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastDtrmv(const CLBlastLayout layout, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose, const CLBlastDiagonal diagonal,
                                          const size_t n,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastCtrmv(const CLBlastLayout layout, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose, const CLBlastDiagonal diagonal,
                                          const size_t n,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastZtrmv(const CLBlastLayout layout, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose, const CLBlastDiagonal diagonal,
                                          const size_t n,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastHtrmv(const CLBlastLayout layout, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose, const CLBlastDiagonal diagonal,
                                          const size_t n,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);

// Triangular banded matrix-vector multiplication: STBMV/DTBMV/CTBMV/ZTBMV/HTBMV
CLBlastStatusCode CLBlastStbmv(const CLBlastLayout layout, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose, const CLBlastDiagonal diagonal,
                                          const size_t n, const size_t k,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastDtbmv(const CLBlastLayout layout, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose, const CLBlastDiagonal diagonal,
                                          const size_t n, const size_t k,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastCtbmv(const CLBlastLayout layout, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose, const CLBlastDiagonal diagonal,
                                          const size_t n, const size_t k,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastZtbmv(const CLBlastLayout layout, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose, const CLBlastDiagonal diagonal,
                                          const size_t n, const size_t k,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastHtbmv(const CLBlastLayout layout, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose, const CLBlastDiagonal diagonal,
                                          const size_t n, const size_t k,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);

// Triangular packed matrix-vector multiplication: STPMV/DTPMV/CTPMV/ZTPMV/HTPMV
CLBlastStatusCode CLBlastStpmv(const CLBlastLayout layout, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose, const CLBlastDiagonal diagonal,
                                          const size_t n,
                                          const cl_mem ap_buffer, const size_t ap_offset,
                                          cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastDtpmv(const CLBlastLayout layout, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose, const CLBlastDiagonal diagonal,
                                          const size_t n,
                                          const cl_mem ap_buffer, const size_t ap_offset,
                                          cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastCtpmv(const CLBlastLayout layout, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose, const CLBlastDiagonal diagonal,
                                          const size_t n,
                                          const cl_mem ap_buffer, const size_t ap_offset,
                                          cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastZtpmv(const CLBlastLayout layout, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose, const CLBlastDiagonal diagonal,
                                          const size_t n,
                                          const cl_mem ap_buffer, const size_t ap_offset,
                                          cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastHtpmv(const CLBlastLayout layout, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose, const CLBlastDiagonal diagonal,
                                          const size_t n,
                                          const cl_mem ap_buffer, const size_t ap_offset,
                                          cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);

// Solves a triangular system of equations: STRSV/DTRSV/CTRSV/ZTRSV
CLBlastStatusCode CLBlastStrsv(const CLBlastLayout layout, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose, const CLBlastDiagonal diagonal,
                                          const size_t n,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastDtrsv(const CLBlastLayout layout, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose, const CLBlastDiagonal diagonal,
                                          const size_t n,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastCtrsv(const CLBlastLayout layout, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose, const CLBlastDiagonal diagonal,
                                          const size_t n,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastZtrsv(const CLBlastLayout layout, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose, const CLBlastDiagonal diagonal,
                                          const size_t n,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);

// Solves a banded triangular system of equations: STBSV/DTBSV/CTBSV/ZTBSV
CLBlastStatusCode CLBlastStbsv(const CLBlastLayout layout, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose, const CLBlastDiagonal diagonal,
                                          const size_t n, const size_t k,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastDtbsv(const CLBlastLayout layout, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose, const CLBlastDiagonal diagonal,
                                          const size_t n, const size_t k,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastCtbsv(const CLBlastLayout layout, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose, const CLBlastDiagonal diagonal,
                                          const size_t n, const size_t k,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastZtbsv(const CLBlastLayout layout, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose, const CLBlastDiagonal diagonal,
                                          const size_t n, const size_t k,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);

// Solves a packed triangular system of equations: STPSV/DTPSV/CTPSV/ZTPSV
CLBlastStatusCode CLBlastStpsv(const CLBlastLayout layout, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose, const CLBlastDiagonal diagonal,
                                          const size_t n,
                                          const cl_mem ap_buffer, const size_t ap_offset,
                                          cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastDtpsv(const CLBlastLayout layout, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose, const CLBlastDiagonal diagonal,
                                          const size_t n,
                                          const cl_mem ap_buffer, const size_t ap_offset,
                                          cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastCtpsv(const CLBlastLayout layout, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose, const CLBlastDiagonal diagonal,
                                          const size_t n,
                                          const cl_mem ap_buffer, const size_t ap_offset,
                                          cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastZtpsv(const CLBlastLayout layout, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose, const CLBlastDiagonal diagonal,
                                          const size_t n,
                                          const cl_mem ap_buffer, const size_t ap_offset,
                                          cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          cl_command_queue* queue, cl_event* event);

// General rank-1 matrix update: SGER/DGER/HGER
CLBlastStatusCode CLBlastSger(const CLBlastLayout layout,
                                         const size_t m, const size_t n,
                                         const float alpha,
                                         const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                         const cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                         cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                         cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastDger(const CLBlastLayout layout,
                                         const size_t m, const size_t n,
                                         const double alpha,
                                         const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                         const cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                         cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                         cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastHger(const CLBlastLayout layout,
                                         const size_t m, const size_t n,
                                         const cl_half alpha,
                                         const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                         const cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                         cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                         cl_command_queue* queue, cl_event* event);

// General rank-1 complex matrix update: CGERU/ZGERU
CLBlastStatusCode CLBlastCgeru(const CLBlastLayout layout,
                                          const size_t m, const size_t n,
                                          const cl_float2 alpha,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          const cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastZgeru(const CLBlastLayout layout,
                                          const size_t m, const size_t n,
                                          const cl_double2 alpha,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          const cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          cl_command_queue* queue, cl_event* event);

// General rank-1 complex conjugated matrix update: CGERC/ZGERC
CLBlastStatusCode CLBlastCgerc(const CLBlastLayout layout,
                                          const size_t m, const size_t n,
                                          const cl_float2 alpha,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          const cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastZgerc(const CLBlastLayout layout,
                                          const size_t m, const size_t n,
                                          const cl_double2 alpha,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          const cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          cl_command_queue* queue, cl_event* event);

// Hermitian rank-1 matrix update: CHER/ZHER
CLBlastStatusCode CLBlastCher(const CLBlastLayout layout, const CLBlastTriangle triangle,
                                         const size_t n,
                                         const float alpha,
                                         const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                         cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                         cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastZher(const CLBlastLayout layout, const CLBlastTriangle triangle,
                                         const size_t n,
                                         const double alpha,
                                         const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                         cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                         cl_command_queue* queue, cl_event* event);

// Hermitian packed rank-1 matrix update: CHPR/ZHPR
CLBlastStatusCode CLBlastChpr(const CLBlastLayout layout, const CLBlastTriangle triangle,
                                         const size_t n,
                                         const float alpha,
                                         const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                         cl_mem ap_buffer, const size_t ap_offset,
                                         cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastZhpr(const CLBlastLayout layout, const CLBlastTriangle triangle,
                                         const size_t n,
                                         const double alpha,
                                         const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                         cl_mem ap_buffer, const size_t ap_offset,
                                         cl_command_queue* queue, cl_event* event);

// Hermitian rank-2 matrix update: CHER2/ZHER2
CLBlastStatusCode CLBlastCher2(const CLBlastLayout layout, const CLBlastTriangle triangle,
                                          const size_t n,
                                          const cl_float2 alpha,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          const cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastZher2(const CLBlastLayout layout, const CLBlastTriangle triangle,
                                          const size_t n,
                                          const cl_double2 alpha,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          const cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          cl_command_queue* queue, cl_event* event);

// Hermitian packed rank-2 matrix update: CHPR2/ZHPR2
CLBlastStatusCode CLBlastChpr2(const CLBlastLayout layout, const CLBlastTriangle triangle,
                                          const size_t n,
                                          const cl_float2 alpha,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          const cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_mem ap_buffer, const size_t ap_offset,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastZhpr2(const CLBlastLayout layout, const CLBlastTriangle triangle,
                                          const size_t n,
                                          const cl_double2 alpha,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          const cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_mem ap_buffer, const size_t ap_offset,
                                          cl_command_queue* queue, cl_event* event);

// Symmetric rank-1 matrix update: SSYR/DSYR/HSYR
CLBlastStatusCode CLBlastSsyr(const CLBlastLayout layout, const CLBlastTriangle triangle,
                                         const size_t n,
                                         const float alpha,
                                         const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                         cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                         cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastDsyr(const CLBlastLayout layout, const CLBlastTriangle triangle,
                                         const size_t n,
                                         const double alpha,
                                         const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                         cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                         cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastHsyr(const CLBlastLayout layout, const CLBlastTriangle triangle,
                                         const size_t n,
                                         const cl_half alpha,
                                         const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                         cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                         cl_command_queue* queue, cl_event* event);

// Symmetric packed rank-1 matrix update: SSPR/DSPR/HSPR
CLBlastStatusCode CLBlastSspr(const CLBlastLayout layout, const CLBlastTriangle triangle,
                                         const size_t n,
                                         const float alpha,
                                         const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                         cl_mem ap_buffer, const size_t ap_offset,
                                         cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastDspr(const CLBlastLayout layout, const CLBlastTriangle triangle,
                                         const size_t n,
                                         const double alpha,
                                         const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                         cl_mem ap_buffer, const size_t ap_offset,
                                         cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastHspr(const CLBlastLayout layout, const CLBlastTriangle triangle,
                                         const size_t n,
                                         const cl_half alpha,
                                         const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                         cl_mem ap_buffer, const size_t ap_offset,
                                         cl_command_queue* queue, cl_event* event);

// Symmetric rank-2 matrix update: SSYR2/DSYR2/HSYR2
CLBlastStatusCode CLBlastSsyr2(const CLBlastLayout layout, const CLBlastTriangle triangle,
                                          const size_t n,
                                          const float alpha,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          const cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastDsyr2(const CLBlastLayout layout, const CLBlastTriangle triangle,
                                          const size_t n,
                                          const double alpha,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          const cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastHsyr2(const CLBlastLayout layout, const CLBlastTriangle triangle,
                                          const size_t n,
                                          const cl_half alpha,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          const cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          cl_command_queue* queue, cl_event* event);

// Symmetric packed rank-2 matrix update: SSPR2/DSPR2/HSPR2
CLBlastStatusCode CLBlastSspr2(const CLBlastLayout layout, const CLBlastTriangle triangle,
                                          const size_t n,
                                          const float alpha,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          const cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_mem ap_buffer, const size_t ap_offset,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastDspr2(const CLBlastLayout layout, const CLBlastTriangle triangle,
                                          const size_t n,
                                          const double alpha,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          const cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_mem ap_buffer, const size_t ap_offset,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastHspr2(const CLBlastLayout layout, const CLBlastTriangle triangle,
                                          const size_t n,
                                          const cl_half alpha,
                                          const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                          const cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                          cl_mem ap_buffer, const size_t ap_offset,
                                          cl_command_queue* queue, cl_event* event);

// =================================================================================================
// BLAS level-3 (matrix-matrix) routines
// =================================================================================================

// General matrix-matrix multiplication: SGEMM/DGEMM/CGEMM/ZGEMM/HGEMM
CLBlastStatusCode CLBlastSgemm(const CLBlastLayout layout, const CLBlastTranspose a_transpose, const CLBlastTranspose b_transpose,
                                          const size_t m, const size_t n, const size_t k,
                                          const float alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                          const float beta,
                                          cl_mem c_buffer, const size_t c_offset, const size_t c_ld,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastDgemm(const CLBlastLayout layout, const CLBlastTranspose a_transpose, const CLBlastTranspose b_transpose,
                                          const size_t m, const size_t n, const size_t k,
                                          const double alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                          const double beta,
                                          cl_mem c_buffer, const size_t c_offset, const size_t c_ld,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastCgemm(const CLBlastLayout layout, const CLBlastTranspose a_transpose, const CLBlastTranspose b_transpose,
                                          const size_t m, const size_t n, const size_t k,
                                          const cl_float2 alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                          const cl_float2 beta,
                                          cl_mem c_buffer, const size_t c_offset, const size_t c_ld,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastZgemm(const CLBlastLayout layout, const CLBlastTranspose a_transpose, const CLBlastTranspose b_transpose,
                                          const size_t m, const size_t n, const size_t k,
                                          const cl_double2 alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                          const cl_double2 beta,
                                          cl_mem c_buffer, const size_t c_offset, const size_t c_ld,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastHgemm(const CLBlastLayout layout, const CLBlastTranspose a_transpose, const CLBlastTranspose b_transpose,
                                          const size_t m, const size_t n, const size_t k,
                                          const cl_half alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                          const cl_half beta,
                                          cl_mem c_buffer, const size_t c_offset, const size_t c_ld,
                                          cl_command_queue* queue, cl_event* event);

// Symmetric matrix-matrix multiplication: SSYMM/DSYMM/CSYMM/ZSYMM/HSYMM
CLBlastStatusCode CLBlastSsymm(const CLBlastLayout layout, const CLBlastSide side, const CLBlastTriangle triangle,
                                          const size_t m, const size_t n,
                                          const float alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                          const float beta,
                                          cl_mem c_buffer, const size_t c_offset, const size_t c_ld,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastDsymm(const CLBlastLayout layout, const CLBlastSide side, const CLBlastTriangle triangle,
                                          const size_t m, const size_t n,
                                          const double alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                          const double beta,
                                          cl_mem c_buffer, const size_t c_offset, const size_t c_ld,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastCsymm(const CLBlastLayout layout, const CLBlastSide side, const CLBlastTriangle triangle,
                                          const size_t m, const size_t n,
                                          const cl_float2 alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                          const cl_float2 beta,
                                          cl_mem c_buffer, const size_t c_offset, const size_t c_ld,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastZsymm(const CLBlastLayout layout, const CLBlastSide side, const CLBlastTriangle triangle,
                                          const size_t m, const size_t n,
                                          const cl_double2 alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                          const cl_double2 beta,
                                          cl_mem c_buffer, const size_t c_offset, const size_t c_ld,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastHsymm(const CLBlastLayout layout, const CLBlastSide side, const CLBlastTriangle triangle,
                                          const size_t m, const size_t n,
                                          const cl_half alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                          const cl_half beta,
                                          cl_mem c_buffer, const size_t c_offset, const size_t c_ld,
                                          cl_command_queue* queue, cl_event* event);

// Hermitian matrix-matrix multiplication: CHEMM/ZHEMM
CLBlastStatusCode CLBlastChemm(const CLBlastLayout layout, const CLBlastSide side, const CLBlastTriangle triangle,
                                          const size_t m, const size_t n,
                                          const cl_float2 alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                          const cl_float2 beta,
                                          cl_mem c_buffer, const size_t c_offset, const size_t c_ld,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastZhemm(const CLBlastLayout layout, const CLBlastSide side, const CLBlastTriangle triangle,
                                          const size_t m, const size_t n,
                                          const cl_double2 alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                          const cl_double2 beta,
                                          cl_mem c_buffer, const size_t c_offset, const size_t c_ld,
                                          cl_command_queue* queue, cl_event* event);

// Rank-K update of a symmetric matrix: SSYRK/DSYRK/CSYRK/ZSYRK/HSYRK
CLBlastStatusCode CLBlastSsyrk(const CLBlastLayout layout, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose,
                                          const size_t n, const size_t k,
                                          const float alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const float beta,
                                          cl_mem c_buffer, const size_t c_offset, const size_t c_ld,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastDsyrk(const CLBlastLayout layout, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose,
                                          const size_t n, const size_t k,
                                          const double alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const double beta,
                                          cl_mem c_buffer, const size_t c_offset, const size_t c_ld,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastCsyrk(const CLBlastLayout layout, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose,
                                          const size_t n, const size_t k,
                                          const cl_float2 alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const cl_float2 beta,
                                          cl_mem c_buffer, const size_t c_offset, const size_t c_ld,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastZsyrk(const CLBlastLayout layout, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose,
                                          const size_t n, const size_t k,
                                          const cl_double2 alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const cl_double2 beta,
                                          cl_mem c_buffer, const size_t c_offset, const size_t c_ld,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastHsyrk(const CLBlastLayout layout, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose,
                                          const size_t n, const size_t k,
                                          const cl_half alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const cl_half beta,
                                          cl_mem c_buffer, const size_t c_offset, const size_t c_ld,
                                          cl_command_queue* queue, cl_event* event);

// Rank-K update of a hermitian matrix: CHERK/ZHERK
CLBlastStatusCode CLBlastCherk(const CLBlastLayout layout, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose,
                                          const size_t n, const size_t k,
                                          const float alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const float beta,
                                          cl_mem c_buffer, const size_t c_offset, const size_t c_ld,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastZherk(const CLBlastLayout layout, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose,
                                          const size_t n, const size_t k,
                                          const double alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          const double beta,
                                          cl_mem c_buffer, const size_t c_offset, const size_t c_ld,
                                          cl_command_queue* queue, cl_event* event);

// Rank-2K update of a symmetric matrix: SSYR2K/DSYR2K/CSYR2K/ZSYR2K/HSYR2K
CLBlastStatusCode CLBlastSsyr2k(const CLBlastLayout layout, const CLBlastTriangle triangle, const CLBlastTranspose ab_transpose,
                                           const size_t n, const size_t k,
                                           const float alpha,
                                           const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                           const cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                           const float beta,
                                           cl_mem c_buffer, const size_t c_offset, const size_t c_ld,
                                           cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastDsyr2k(const CLBlastLayout layout, const CLBlastTriangle triangle, const CLBlastTranspose ab_transpose,
                                           const size_t n, const size_t k,
                                           const double alpha,
                                           const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                           const cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                           const double beta,
                                           cl_mem c_buffer, const size_t c_offset, const size_t c_ld,
                                           cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastCsyr2k(const CLBlastLayout layout, const CLBlastTriangle triangle, const CLBlastTranspose ab_transpose,
                                           const size_t n, const size_t k,
                                           const cl_float2 alpha,
                                           const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                           const cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                           const cl_float2 beta,
                                           cl_mem c_buffer, const size_t c_offset, const size_t c_ld,
                                           cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastZsyr2k(const CLBlastLayout layout, const CLBlastTriangle triangle, const CLBlastTranspose ab_transpose,
                                           const size_t n, const size_t k,
                                           const cl_double2 alpha,
                                           const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                           const cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                           const cl_double2 beta,
                                           cl_mem c_buffer, const size_t c_offset, const size_t c_ld,
                                           cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastHsyr2k(const CLBlastLayout layout, const CLBlastTriangle triangle, const CLBlastTranspose ab_transpose,
                                           const size_t n, const size_t k,
                                           const cl_half alpha,
                                           const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                           const cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                           const cl_half beta,
                                           cl_mem c_buffer, const size_t c_offset, const size_t c_ld,
                                           cl_command_queue* queue, cl_event* event);

// Rank-2K update of a hermitian matrix: CHER2K/ZHER2K
CLBlastStatusCode CLBlastCher2k(const CLBlastLayout layout, const CLBlastTriangle triangle, const CLBlastTranspose ab_transpose,
                                           const size_t n, const size_t k,
                                           const cl_float2 alpha,
                                           const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                           const cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                           const float beta,
                                           cl_mem c_buffer, const size_t c_offset, const size_t c_ld,
                                           cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastZher2k(const CLBlastLayout layout, const CLBlastTriangle triangle, const CLBlastTranspose ab_transpose,
                                           const size_t n, const size_t k,
                                           const cl_double2 alpha,
                                           const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                           const cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                           const double beta,
                                           cl_mem c_buffer, const size_t c_offset, const size_t c_ld,
                                           cl_command_queue* queue, cl_event* event);

// Triangular matrix-matrix multiplication: STRMM/DTRMM/CTRMM/ZTRMM/HTRMM
CLBlastStatusCode CLBlastStrmm(const CLBlastLayout layout, const CLBlastSide side, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose, const CLBlastDiagonal diagonal,
                                          const size_t m, const size_t n,
                                          const float alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastDtrmm(const CLBlastLayout layout, const CLBlastSide side, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose, const CLBlastDiagonal diagonal,
                                          const size_t m, const size_t n,
                                          const double alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastCtrmm(const CLBlastLayout layout, const CLBlastSide side, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose, const CLBlastDiagonal diagonal,
                                          const size_t m, const size_t n,
                                          const cl_float2 alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastZtrmm(const CLBlastLayout layout, const CLBlastSide side, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose, const CLBlastDiagonal diagonal,
                                          const size_t m, const size_t n,
                                          const cl_double2 alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastHtrmm(const CLBlastLayout layout, const CLBlastSide side, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose, const CLBlastDiagonal diagonal,
                                          const size_t m, const size_t n,
                                          const cl_half alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                          cl_command_queue* queue, cl_event* event);

// Solves a triangular system of equations: STRSM/DTRSM/CTRSM/ZTRSM
CLBlastStatusCode CLBlastStrsm(const CLBlastLayout layout, const CLBlastSide side, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose, const CLBlastDiagonal diagonal,
                                          const size_t m, const size_t n,
                                          const float alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastDtrsm(const CLBlastLayout layout, const CLBlastSide side, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose, const CLBlastDiagonal diagonal,
                                          const size_t m, const size_t n,
                                          const double alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastCtrsm(const CLBlastLayout layout, const CLBlastSide side, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose, const CLBlastDiagonal diagonal,
                                          const size_t m, const size_t n,
                                          const cl_float2 alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                          cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastZtrsm(const CLBlastLayout layout, const CLBlastSide side, const CLBlastTriangle triangle, const CLBlastTranspose a_transpose, const CLBlastDiagonal diagonal,
                                          const size_t m, const size_t n,
                                          const cl_double2 alpha,
                                          const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                          cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                          cl_command_queue* queue, cl_event* event);

// =================================================================================================
// Extra non-BLAS routines (level-X)
// =================================================================================================

// Element-wise vector product (Hadamard): SHAD/DHAD/CHAD/ZHAD/HHAD
CLBlastStatusCode CLBlastShad(const size_t n,
                                         const float alpha,
                                         const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                         const cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                         const float beta,
                                         cl_mem z_buffer, const size_t z_offset, const size_t z_inc,
                                         cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastDhad(const size_t n,
                                         const double alpha,
                                         const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                         const cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                         const double beta,
                                         cl_mem z_buffer, const size_t z_offset, const size_t z_inc,
                                         cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastChad(const size_t n,
                                         const cl_float2 alpha,
                                         const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                         const cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                         const cl_float2 beta,
                                         cl_mem z_buffer, const size_t z_offset, const size_t z_inc,
                                         cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastZhad(const size_t n,
                                         const cl_double2 alpha,
                                         const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                         const cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                         const cl_double2 beta,
                                         cl_mem z_buffer, const size_t z_offset, const size_t z_inc,
                                         cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastHhad(const size_t n,
                                         const cl_half alpha,
                                         const cl_mem x_buffer, const size_t x_offset, const size_t x_inc,
                                         const cl_mem y_buffer, const size_t y_offset, const size_t y_inc,
                                         const cl_half beta,
                                         cl_mem z_buffer, const size_t z_offset, const size_t z_inc,
                                         cl_command_queue* queue, cl_event* event);

// Scaling and out-place transpose/copy (non-BLAS function): SOMATCOPY/DOMATCOPY/COMATCOPY/ZOMATCOPY/HOMATCOPY
CLBlastStatusCode CLBlastSomatcopy(const CLBlastLayout layout, const CLBlastTranspose a_transpose,
                                              const size_t m, const size_t n,
                                              const float alpha,
                                              const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                              cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                              cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastDomatcopy(const CLBlastLayout layout, const CLBlastTranspose a_transpose,
                                              const size_t m, const size_t n,
                                              const double alpha,
                                              const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                              cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                              cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastComatcopy(const CLBlastLayout layout, const CLBlastTranspose a_transpose,
                                              const size_t m, const size_t n,
                                              const cl_float2 alpha,
                                              const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                              cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                              cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastZomatcopy(const CLBlastLayout layout, const CLBlastTranspose a_transpose,
                                              const size_t m, const size_t n,
                                              const cl_double2 alpha,
                                              const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                              cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                              cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastHomatcopy(const CLBlastLayout layout, const CLBlastTranspose a_transpose,
                                              const size_t m, const size_t n,
                                              const cl_half alpha,
                                              const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                              cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                              cl_command_queue* queue, cl_event* event);

// Im2col function (non-BLAS function): SIM2COL/DIM2COL/CIM2COL/ZIM2COL/HIM2COL
CLBlastStatusCode CLBlastSim2col(const CLBlastKernelMode kernel_mode,
                                            const size_t channels, const size_t height, const size_t width, const size_t kernel_h, const size_t kernel_w, const size_t pad_h, const size_t pad_w, const size_t stride_h, const size_t stride_w, const size_t dilation_h, const size_t dilation_w,
                                            const cl_mem im_buffer, const size_t im_offset,
                                            cl_mem col_buffer, const size_t col_offset,
                                            cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastDim2col(const CLBlastKernelMode kernel_mode,
                                            const size_t channels, const size_t height, const size_t width, const size_t kernel_h, const size_t kernel_w, const size_t pad_h, const size_t pad_w, const size_t stride_h, const size_t stride_w, const size_t dilation_h, const size_t dilation_w,
                                            const cl_mem im_buffer, const size_t im_offset,
                                            cl_mem col_buffer, const size_t col_offset,
                                            cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastCim2col(const CLBlastKernelMode kernel_mode,
                                            const size_t channels, const size_t height, const size_t width, const size_t kernel_h, const size_t kernel_w, const size_t pad_h, const size_t pad_w, const size_t stride_h, const size_t stride_w, const size_t dilation_h, const size_t dilation_w,
                                            const cl_mem im_buffer, const size_t im_offset,
                                            cl_mem col_buffer, const size_t col_offset,
                                            cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastZim2col(const CLBlastKernelMode kernel_mode,
                                            const size_t channels, const size_t height, const size_t width, const size_t kernel_h, const size_t kernel_w, const size_t pad_h, const size_t pad_w, const size_t stride_h, const size_t stride_w, const size_t dilation_h, const size_t dilation_w,
                                            const cl_mem im_buffer, const size_t im_offset,
                                            cl_mem col_buffer, const size_t col_offset,
                                            cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastHim2col(const CLBlastKernelMode kernel_mode,
                                            const size_t channels, const size_t height, const size_t width, const size_t kernel_h, const size_t kernel_w, const size_t pad_h, const size_t pad_w, const size_t stride_h, const size_t stride_w, const size_t dilation_h, const size_t dilation_w,
                                            const cl_mem im_buffer, const size_t im_offset,
                                            cl_mem col_buffer, const size_t col_offset,
                                            cl_command_queue* queue, cl_event* event);

// Col2im function (non-BLAS function): SCOL2IM/DCOL2IM/CCOL2IM/ZCOL2IM/HCOL2IM
CLBlastStatusCode CLBlastScol2im(const CLBlastKernelMode kernel_mode,
                                            const size_t channels, const size_t height, const size_t width, const size_t kernel_h, const size_t kernel_w, const size_t pad_h, const size_t pad_w, const size_t stride_h, const size_t stride_w, const size_t dilation_h, const size_t dilation_w,
                                            const cl_mem col_buffer, const size_t col_offset,
                                            cl_mem im_buffer, const size_t im_offset,
                                            cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastDcol2im(const CLBlastKernelMode kernel_mode,
                                            const size_t channels, const size_t height, const size_t width, const size_t kernel_h, const size_t kernel_w, const size_t pad_h, const size_t pad_w, const size_t stride_h, const size_t stride_w, const size_t dilation_h, const size_t dilation_w,
                                            const cl_mem col_buffer, const size_t col_offset,
                                            cl_mem im_buffer, const size_t im_offset,
                                            cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastCcol2im(const CLBlastKernelMode kernel_mode,
                                            const size_t channels, const size_t height, const size_t width, const size_t kernel_h, const size_t kernel_w, const size_t pad_h, const size_t pad_w, const size_t stride_h, const size_t stride_w, const size_t dilation_h, const size_t dilation_w,
                                            const cl_mem col_buffer, const size_t col_offset,
                                            cl_mem im_buffer, const size_t im_offset,
                                            cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastZcol2im(const CLBlastKernelMode kernel_mode,
                                            const size_t channels, const size_t height, const size_t width, const size_t kernel_h, const size_t kernel_w, const size_t pad_h, const size_t pad_w, const size_t stride_h, const size_t stride_w, const size_t dilation_h, const size_t dilation_w,
                                            const cl_mem col_buffer, const size_t col_offset,
                                            cl_mem im_buffer, const size_t im_offset,
                                            cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastHcol2im(const CLBlastKernelMode kernel_mode,
                                            const size_t channels, const size_t height, const size_t width, const size_t kernel_h, const size_t kernel_w, const size_t pad_h, const size_t pad_w, const size_t stride_h, const size_t stride_w, const size_t dilation_h, const size_t dilation_w,
                                            const cl_mem col_buffer, const size_t col_offset,
                                            cl_mem im_buffer, const size_t im_offset,
                                            cl_command_queue* queue, cl_event* event);

// Batched convolution as GEMM (non-BLAS function): SCONVGEMM/DCONVGEMM/HCONVGEMM
CLBlastStatusCode CLBlastSconvgemm(const CLBlastKernelMode kernel_mode,
                                              const size_t channels, const size_t height, const size_t width, const size_t kernel_h, const size_t kernel_w, const size_t pad_h, const size_t pad_w, const size_t stride_h, const size_t stride_w, const size_t dilation_h, const size_t dilation_w, const size_t num_kernels, const size_t batch_count,
                                              const cl_mem im_buffer, const size_t im_offset,
                                              const cl_mem kernel_buffer, const size_t kernel_offset,
                                              cl_mem result_buffer, const size_t result_offset,
                                              cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastDconvgemm(const CLBlastKernelMode kernel_mode,
                                              const size_t channels, const size_t height, const size_t width, const size_t kernel_h, const size_t kernel_w, const size_t pad_h, const size_t pad_w, const size_t stride_h, const size_t stride_w, const size_t dilation_h, const size_t dilation_w, const size_t num_kernels, const size_t batch_count,
                                              const cl_mem im_buffer, const size_t im_offset,
                                              const cl_mem kernel_buffer, const size_t kernel_offset,
                                              cl_mem result_buffer, const size_t result_offset,
                                              cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastHconvgemm(const CLBlastKernelMode kernel_mode,
                                              const size_t channels, const size_t height, const size_t width, const size_t kernel_h, const size_t kernel_w, const size_t pad_h, const size_t pad_w, const size_t stride_h, const size_t stride_w, const size_t dilation_h, const size_t dilation_w, const size_t num_kernels, const size_t batch_count,
                                              const cl_mem im_buffer, const size_t im_offset,
                                              const cl_mem kernel_buffer, const size_t kernel_offset,
                                              cl_mem result_buffer, const size_t result_offset,
                                              cl_command_queue* queue, cl_event* event);

// Batched version of AXPY: SAXPYBATCHED/DAXPYBATCHED/CAXPYBATCHED/ZAXPYBATCHED/HAXPYBATCHED
CLBlastStatusCode CLBlastSaxpyBatched(const size_t n,
                                                 const float *alphas,
                                                 const cl_mem x_buffer, const size_t *x_offsets, const size_t x_inc,
                                                 cl_mem y_buffer, const size_t *y_offsets, const size_t y_inc,
                                                 const size_t batch_count,
                                                 cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastDaxpyBatched(const size_t n,
                                                 const double *alphas,
                                                 const cl_mem x_buffer, const size_t *x_offsets, const size_t x_inc,
                                                 cl_mem y_buffer, const size_t *y_offsets, const size_t y_inc,
                                                 const size_t batch_count,
                                                 cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastCaxpyBatched(const size_t n,
                                                 const cl_float2 *alphas,
                                                 const cl_mem x_buffer, const size_t *x_offsets, const size_t x_inc,
                                                 cl_mem y_buffer, const size_t *y_offsets, const size_t y_inc,
                                                 const size_t batch_count,
                                                 cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastZaxpyBatched(const size_t n,
                                                 const cl_double2 *alphas,
                                                 const cl_mem x_buffer, const size_t *x_offsets, const size_t x_inc,
                                                 cl_mem y_buffer, const size_t *y_offsets, const size_t y_inc,
                                                 const size_t batch_count,
                                                 cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastHaxpyBatched(const size_t n,
                                                 const cl_half *alphas,
                                                 const cl_mem x_buffer, const size_t *x_offsets, const size_t x_inc,
                                                 cl_mem y_buffer, const size_t *y_offsets, const size_t y_inc,
                                                 const size_t batch_count,
                                                 cl_command_queue* queue, cl_event* event);

// Batched version of GEMM: SGEMMBATCHED/DGEMMBATCHED/CGEMMBATCHED/ZGEMMBATCHED/HGEMMBATCHED
CLBlastStatusCode CLBlastSgemmBatched(const CLBlastLayout layout, const CLBlastTranspose a_transpose, const CLBlastTranspose b_transpose,
                                                 const size_t m, const size_t n, const size_t k,
                                                 const float *alphas,
                                                 const cl_mem a_buffer, const size_t *a_offsets, const size_t a_ld,
                                                 const cl_mem b_buffer, const size_t *b_offsets, const size_t b_ld,
                                                 const float *betas,
                                                 cl_mem c_buffer, const size_t *c_offsets, const size_t c_ld,
                                                 const size_t batch_count,
                                                 cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastDgemmBatched(const CLBlastLayout layout, const CLBlastTranspose a_transpose, const CLBlastTranspose b_transpose,
                                                 const size_t m, const size_t n, const size_t k,
                                                 const double *alphas,
                                                 const cl_mem a_buffer, const size_t *a_offsets, const size_t a_ld,
                                                 const cl_mem b_buffer, const size_t *b_offsets, const size_t b_ld,
                                                 const double *betas,
                                                 cl_mem c_buffer, const size_t *c_offsets, const size_t c_ld,
                                                 const size_t batch_count,
                                                 cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastCgemmBatched(const CLBlastLayout layout, const CLBlastTranspose a_transpose, const CLBlastTranspose b_transpose,
                                                 const size_t m, const size_t n, const size_t k,
                                                 const cl_float2 *alphas,
                                                 const cl_mem a_buffer, const size_t *a_offsets, const size_t a_ld,
                                                 const cl_mem b_buffer, const size_t *b_offsets, const size_t b_ld,
                                                 const cl_float2 *betas,
                                                 cl_mem c_buffer, const size_t *c_offsets, const size_t c_ld,
                                                 const size_t batch_count,
                                                 cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastZgemmBatched(const CLBlastLayout layout, const CLBlastTranspose a_transpose, const CLBlastTranspose b_transpose,
                                                 const size_t m, const size_t n, const size_t k,
                                                 const cl_double2 *alphas,
                                                 const cl_mem a_buffer, const size_t *a_offsets, const size_t a_ld,
                                                 const cl_mem b_buffer, const size_t *b_offsets, const size_t b_ld,
                                                 const cl_double2 *betas,
                                                 cl_mem c_buffer, const size_t *c_offsets, const size_t c_ld,
                                                 const size_t batch_count,
                                                 cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastHgemmBatched(const CLBlastLayout layout, const CLBlastTranspose a_transpose, const CLBlastTranspose b_transpose,
                                                 const size_t m, const size_t n, const size_t k,
                                                 const cl_half *alphas,
                                                 const cl_mem a_buffer, const size_t *a_offsets, const size_t a_ld,
                                                 const cl_mem b_buffer, const size_t *b_offsets, const size_t b_ld,
                                                 const cl_half *betas,
                                                 cl_mem c_buffer, const size_t *c_offsets, const size_t c_ld,
                                                 const size_t batch_count,
                                                 cl_command_queue* queue, cl_event* event);

// StridedBatched version of GEMM: SGEMMSTRIDEDBATCHED/DGEMMSTRIDEDBATCHED/CGEMMSTRIDEDBATCHED/ZGEMMSTRIDEDBATCHED/HGEMMSTRIDEDBATCHED
CLBlastStatusCode CLBlastSgemmStridedBatched(const CLBlastLayout layout, const CLBlastTranspose a_transpose, const CLBlastTranspose b_transpose,
                                                        const size_t m, const size_t n, const size_t k,
                                                        const float alpha,
                                                        const cl_mem a_buffer, const size_t a_offset, const size_t a_ld, const size_t a_stride,
                                                        const cl_mem b_buffer, const size_t b_offset, const size_t b_ld, const size_t b_stride,
                                                        const float beta,
                                                        cl_mem c_buffer, const size_t c_offset, const size_t c_ld, const size_t c_stride,
                                                        const size_t batch_count,
                                                        cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastDgemmStridedBatched(const CLBlastLayout layout, const CLBlastTranspose a_transpose, const CLBlastTranspose b_transpose,
                                                        const size_t m, const size_t n, const size_t k,
                                                        const double alpha,
                                                        const cl_mem a_buffer, const size_t a_offset, const size_t a_ld, const size_t a_stride,
                                                        const cl_mem b_buffer, const size_t b_offset, const size_t b_ld, const size_t b_stride,
                                                        const double beta,
                                                        cl_mem c_buffer, const size_t c_offset, const size_t c_ld, const size_t c_stride,
                                                        const size_t batch_count,
                                                        cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastCgemmStridedBatched(const CLBlastLayout layout, const CLBlastTranspose a_transpose, const CLBlastTranspose b_transpose,
                                                        const size_t m, const size_t n, const size_t k,
                                                        const cl_float2 alpha,
                                                        const cl_mem a_buffer, const size_t a_offset, const size_t a_ld, const size_t a_stride,
                                                        const cl_mem b_buffer, const size_t b_offset, const size_t b_ld, const size_t b_stride,
                                                        const cl_float2 beta,
                                                        cl_mem c_buffer, const size_t c_offset, const size_t c_ld, const size_t c_stride,
                                                        const size_t batch_count,
                                                        cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastZgemmStridedBatched(const CLBlastLayout layout, const CLBlastTranspose a_transpose, const CLBlastTranspose b_transpose,
                                                        const size_t m, const size_t n, const size_t k,
                                                        const cl_double2 alpha,
                                                        const cl_mem a_buffer, const size_t a_offset, const size_t a_ld, const size_t a_stride,
                                                        const cl_mem b_buffer, const size_t b_offset, const size_t b_ld, const size_t b_stride,
                                                        const cl_double2 beta,
                                                        cl_mem c_buffer, const size_t c_offset, const size_t c_ld, const size_t c_stride,
                                                        const size_t batch_count,
                                                        cl_command_queue* queue, cl_event* event);
CLBlastStatusCode CLBlastHgemmStridedBatched(const CLBlastLayout layout, const CLBlastTranspose a_transpose, const CLBlastTranspose b_transpose,
                                                        const size_t m, const size_t n, const size_t k,
                                                        const cl_half alpha,
                                                        const cl_mem a_buffer, const size_t a_offset, const size_t a_ld, const size_t a_stride,
                                                        const cl_mem b_buffer, const size_t b_offset, const size_t b_ld, const size_t b_stride,
                                                        const cl_half beta,
                                                        cl_mem c_buffer, const size_t c_offset, const size_t c_ld, const size_t c_stride,
                                                        const size_t batch_count,
                                                        cl_command_queue* queue, cl_event* event);

// =================================================================================================
// General matrix-matrix multiplication with temporary buffer from user (optional, for advanced users): SGEMM/DGEMM/CGEMM/ZGEMM/HGEMM
CLBlastStatusCode CLBlastSgemmWithTempBuffer(const CLBlastLayout layout, const CLBlastTranspose a_transpose, const CLBlastTranspose b_transpose,
                                                        const size_t m, const size_t n, const size_t k,
                                                        const float alpha,
                                                        const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                                        const cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                                        const float beta,
                                                        cl_mem c_buffer, const size_t c_offset, const size_t c_ld,
                                                        cl_command_queue* queue, cl_event* event, cl_mem temp_buffer);
CLBlastStatusCode CLBlastDgemmWithTempBuffer(const CLBlastLayout layout, const CLBlastTranspose a_transpose, const CLBlastTranspose b_transpose,
                                                        const size_t m, const size_t n, const size_t k,
                                                        const double alpha,
                                                        const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                                        const cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                                        const double beta,
                                                        cl_mem c_buffer, const size_t c_offset, const size_t c_ld,
                                                        cl_command_queue* queue, cl_event* event, cl_mem temp_buffer);
CLBlastStatusCode CLBlastCgemmWithTempBuffer(const CLBlastLayout layout, const CLBlastTranspose a_transpose, const CLBlastTranspose b_transpose,
                                                        const size_t m, const size_t n, const size_t k,
                                                        const cl_float2 alpha,
                                                        const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                                        const cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                                        const cl_float2 beta,
                                                        cl_mem c_buffer, const size_t c_offset, const size_t c_ld,
                                                        cl_command_queue* queue, cl_event* event, cl_mem temp_buffer);
CLBlastStatusCode CLBlastZgemmWithTempBuffer(const CLBlastLayout layout, const CLBlastTranspose a_transpose, const CLBlastTranspose b_transpose,
                                                        const size_t m, const size_t n, const size_t k,
                                                        const cl_double2 alpha,
                                                        const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                                        const cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                                        const cl_double2 beta,
                                                        cl_mem c_buffer, const size_t c_offset, const size_t c_ld,
                                                        cl_command_queue* queue, cl_event* event, cl_mem temp_buffer);
CLBlastStatusCode CLBlastHgemmWithTempBuffer(const CLBlastLayout layout, const CLBlastTranspose a_transpose, const CLBlastTranspose b_transpose,
                                                        const size_t m, const size_t n, const size_t k,
                                                        const cl_half alpha,
                                                        const cl_mem a_buffer, const size_t a_offset, const size_t a_ld,
                                                        const cl_mem b_buffer, const size_t b_offset, const size_t b_ld,
                                                        const cl_half beta,
                                                        cl_mem c_buffer, const size_t c_offset, const size_t c_ld,
                                                        cl_command_queue* queue, cl_event* event, cl_mem temp_buffer);

// =================================================================================================
// Retrieves the required size of the temporary buffer for the GEMM kernel: SGEMM/DGEMM/CGEMM/ZGEMM/HGEMM (optional)
CLBlastStatusCode CLBlastSGemmTempBufferSize(const CLBlastLayout layout, const CLBlastTranspose a_transpose, const CLBlastTranspose b_transpose,
                                                        const size_t m, const size_t n, const size_t k,
                                                        const size_t a_offset, const size_t a_ld,
                                                        const size_t b_offset, const size_t b_ld,
                                                        const size_t c_offset, const size_t c_ld,
                                                        cl_command_queue* queue,
                                                        size_t* temp_buffer_size);

CLBlastStatusCode CLBlastDGemmTempBufferSize(const CLBlastLayout layout, const CLBlastTranspose a_transpose, const CLBlastTranspose b_transpose,
                                                        const size_t m, const size_t n, const size_t k,
                                                        const size_t a_offset, const size_t a_ld,
                                                        const size_t b_offset, const size_t b_ld,
                                                        const size_t c_offset, const size_t c_ld,
                                                        cl_command_queue* queue,
                                                        size_t* temp_buffer_size);

CLBlastStatusCode CLBlastCGemmTempBufferSize(const CLBlastLayout layout, const CLBlastTranspose a_transpose, const CLBlastTranspose b_transpose,
                                                        const size_t m, const size_t n, const size_t k,
                                                        const size_t a_offset, const size_t a_ld,
                                                        const size_t b_offset, const size_t b_ld,
                                                        const size_t c_offset, const size_t c_ld,
                                                        cl_command_queue* queue,
                                                        size_t* temp_buffer_size);

CLBlastStatusCode CLBlastZGemmTempBufferSize(const CLBlastLayout layout, const CLBlastTranspose a_transpose, const CLBlastTranspose b_transpose,
                                                        const size_t m, const size_t n, const size_t k,
                                                        const size_t a_offset, const size_t a_ld,
                                                        const size_t b_offset, const size_t b_ld,
                                                        const size_t c_offset, const size_t c_ld,
                                                        cl_command_queue* queue,
                                                        size_t* temp_buffer_size);

CLBlastStatusCode CLBlastHGemmTempBufferSize(const CLBlastLayout layout, const CLBlastTranspose a_transpose, const CLBlastTranspose b_transpose,
                                                        const size_t m, const size_t n, const size_t k,
                                                        const size_t a_offset, const size_t a_ld,
                                                        const size_t b_offset, const size_t b_ld,
                                                        const size_t c_offset, const size_t c_ld,
                                                        cl_command_queue* queue,
                                                        size_t* temp_buffer_size);

// =================================================================================================

// CLBlast stores binaries of compiled kernels into a cache in case the same kernel is used later on
// for the same device. This cache can be cleared to free up system memory or in case of debugging.
CLBlastStatusCode CLBlastClearCache();

// The cache can also be pre-initialized for a specific device with all possible CLBLast kernels.
// Further CLBlast routine calls will then run at maximum speed.
CLBlastStatusCode CLBlastFillCache(const cl_device_id device);

// =================================================================================================

// Overrides tuning parameters for a specific device-precision-kernel combination. The next time
// the target routine is called it will re-compile and use the new parameters from then on.
CLBlastStatusCode CLBlastOverrideParameters(const cl_device_id device, const char* kernel_name,
                                                       const CLBlastPrecision precision, const size_t num_parameters,
                                                       const char** parameters_names, const size_t* parameters_values);

// =================================================================================================

