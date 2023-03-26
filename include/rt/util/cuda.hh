#ifndef RT_UTIL_CUDA_HH
#define RT_UTIL_CUDA_HH

#ifdef __CUDACC__
#define RT_DEVICE __host__ __device__
#else
#define RT_DEVICE
#endif

#endif
