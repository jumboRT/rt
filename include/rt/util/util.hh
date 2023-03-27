#ifndef RT_UTIL_UTIL_HH
#define RT_UTIL_UTIL_HH

#include <utility>

#ifdef __CUDACC__
#define RT_DEVICE __host__ __device__
#else
#define RT_DEVICE
#endif

namespace rt {
	template<class T>
	RT_DEVICE void swap(T& a, T& b) {
		T tmp(std::move(a));
		a = std::move(b);
		b = std::move(tmp);
	}
}

#endif
