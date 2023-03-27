#ifndef RT_MATH_MATH_HH
#define RT_MATH_MATH_HH

#include "rt/util/util.hh"

#include <cmath>

namespace rt {
	typedef float float_t;

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
	RT_DEVICE T asin(const T& arg) {
		return std::asin(arg);
	}

	template<class T>
	RT_DEVICE T acos(const T& arg) {
		return std::acos(arg);
	}

	template<class T>
	RT_DEVICE T atan(const T& arg) {
		return std::atan(arg);
	}

	template<class T>
	RT_DEVICE T fma(const T& a, const T& b, const T& c) {
		return std::fma(a, b, c);
	}

	template<class T>
	RT_DEVICE constexpr T& min(T& a, T& b) {
		return a < b ? a : b;
	}

	template<class T>
	RT_DEVICE constexpr const T& min(const T& a, const T& b) {
		return a < b ? a : b;
	}

	template<class T>
	RT_DEVICE constexpr T& max(T& a, T& b) {
		return a > b ? a : b;
	}

	template<class T>
	RT_DEVICE constexpr const T& max(const T& a, const T& b) {
		return a > b ? a : b;
	}

	template<class T>
	RT_DEVICE constexpr T& clamp(T& a, T& b, T& c) {
		return min(max(a, b), c);
	}

	template<class T>
	RT_DEVICE constexpr const T& clamp(const T& a, const T& b, const T& c) {
		return min(max(a, b), c);
	}

	template<class T>
	RT_DEVICE T lerp(const T& a, const T& b, const T& t) {
		return fma(t, b - a, a);
	}
}

#endif
