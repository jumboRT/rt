#ifndef RT_MATH_MATH_HH
#define RT_MATH_MATH_HH

#include <cmath>

namespace rt {
	template<class T>
	T floor(const T& arg) {
		return std::floor(arg);
	}

	template<class T>
	T ceil(const T& arg) {
		return std::ceil(arg);
	}

	template<class T>
	T abs(const T& arg) {
		return std::abs(arg);
	}

	template<class T>
	T sqrt(const T& arg) {
		return std::sqrt(arg);
	}

	template<class T>
	T& min(T& a, T& b) {
		return a < b ? a : b;
	}

	template<class T>
	const T& min(const T& a, const T& b) {
		return a < b ? a : b;
	}

	template<class T>
	T& max(T& a, T& b) {
		return a > b ? a : b;
	}

	template<class T>
	const T& max(const T& a, const T& b) {
		return a > b ? a : b;
	}

	template<class T>
	T lerp(const T& a, const T& b, const T& t) {
		return a + t * (b - a);
	}

	template<class T>
	void swap(T& a, T& b) {
		T tmp = a;
		a = b;
		b = tmp;
	}
}

#endif
