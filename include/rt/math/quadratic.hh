#ifndef RT_MATH_QUADRATIC_HH
#define RT_MATH_QUADRATIC_HH

#include "rt/math/math.hh"

namespace rt {
	// https://stackoverflow.com/a/50065711
	template<class T>
	T product_diff(const T &a, const T &b, const T &c, const T &d) {
		T e = fma(a, b, -d * c);
		T f = fma(c, d, -d * c);

		return e - f;
	}

	template<class T>
	bool quadratic(const T &a, const T &b, const T &c, T &t0, T &t1) {
		T discriminant = product_diff(b, b, 4 * a, c);

		if (discriminant < 0) {
			return false;
		}

		T root = sqrt(discriminant);
		T q = -0.5f * (b + (b < 0 ? -root : root));

		t0 = q / a;
		t1 = c / q;

		if (t0 > t1) {
			swap(t0, t1);
		}

		return true;
	}
}

#endif
