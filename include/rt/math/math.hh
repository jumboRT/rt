#ifndef RT_MATH_MATH_HH
#define RT_MATH_MATH_HH

#include "rt/util/cuda.hh"

#include <cmath>

namespace rt {
	typedef float real;

	template<class T>
	RT_DEVICE T floor(const T& arg) {
		return std::floor(arg);
	}

	template<class T>
	RT_DEVICE T ceil(const T& arg) {
		return std::ceil(arg);
	}

	template<class T>
	RT_DEVICE T abs(const T& arg) {
		return std::abs(arg);
	}

	template<class T>
	RT_DEVICE T sqrt(const T& arg) {
		return std::sqrt(arg);
	}

	template<class T>
	RT_DEVICE T sin(const T& arg) {
		return std::sin(arg);
	}

	template<class T>
	RT_DEVICE T cos(const T& arg) {
		return std::cos(arg);
	}

	template<class T>
	RT_DEVICE T tan(const T& arg) {
		return std::tan(arg);
	}

	template<class T>
	RT_DEVICE T fma(const T& a, const T& b, const T& c) {
		return std::fma(a, b, c);
	}

	template<class T>
	RT_DEVICE T& min(T& a, T& b) {
		return a < b ? a : b;
	}

	template<class T>
	RT_DEVICE const T& min(const T& a, const T& b) {
		return a < b ? a : b;
	}

	template<class T>
	RT_DEVICE T& max(T& a, T& b) {
		return a > b ? a : b;
	}

	template<class T>
	RT_DEVICE const T& max(const T& a, const T& b) {
		return a > b ? a : b;
	}

	template<class T>
	RT_DEVICE T lerp(const T& a, const T& b, const T& t) {
		return a + t * (b - a);
	}

	template<class T>
	RT_DEVICE void swap(T& a, T& b) {
		T tmp = a;
		a = b;
		b = tmp;
	}
}

#endif
