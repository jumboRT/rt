#ifndef RT_MATH_MATH_HH
#define RT_MATH_MATH_HH

#include <cmath>

namespace rt {
	template<class T>
	constexpr T floor(const T& arg) {
		return std::floor(arg);
	}

	template<class T>
	constexpr T ceil(const T& arg) {
		return std::ceil(arg);
	}

	template<class T>
	constexpr T abs(const T& arg) {
		return std::abs(arg);
	}

	template<class T>
	constexpr T sqrt(const T& arg) {
		return std::sqrt(arg);
	}

	template<class T>
	constexpr T& min(T& a, T& b) {
		return a < b ? a : b;
	}

	template<class T>
	constexpr const T& min(const T& a, const T& b) {
		return a < b ? a : b;
	}

	template<class T>
	constexpr T& max(T& a, T& b) {
		return a > b ? a : b;
	}

	template<class T>
	constexpr const T& max(const T& a, const T& b) {
		return a > b ? a : b;
	}

	template<class T>
	constexpr T lerp(const T& a, const T& b, const T& t) {
		return a + t * (b - a);
	}
}

#endif
