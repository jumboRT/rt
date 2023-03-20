#ifndef RT_MATH_MATH_HH
#define RT_MATH_MATH_HH

#include <cmath>

namespace rt {
	template<class T>
	constexpr T floor(const T& value) {
		// FIXME: dit, of "using std::floor" en dan gewoon "floor()"
		// dat tweede lijdt misschien tot infinite recursion
		return std::floor(value);
	}

	template<class T>
	constexpr T ceil(const T& value) {
		return std::ceil(value);
	}

	template<class T>
	constexpr T abs(const T& value) {
		return std::abs(value);
	}

	template<class T>
	constexpr T& min(T& lhs, T& rhs) {
		return lhs < rhs ? lhs : rhs;
	}

	template<class T>
	constexpr const T& min(const T& lhs, const T& rhs) {
		return lhs < rhs ? lhs : rhs;
	}

	template<class T>
	constexpr T& max(T& lhs, T& rhs) {
		return lhs > rhs ? lhs : rhs;
	}

	template<class T>
	constexpr const T& max(const T& lhs, const T& rhs) {
		return lhs > rhs ? lhs : rhs;
	}

	template<class T>
	constexpr T sqrt(const T& value) {
		return std::sqrt(value);
	}

	// FIXME: volgorde van arguments onduidelijk
	// FIXME: moet lerp wel *zo* generic?
	// FIXME: moeten alle functies in deze file eigenljk wel *zo* generic?
	template<class T, class U>
	constexpr U lerp(const T& time, const U& lhs, const U& rhs) {
		return lhs * (1 - time) + rhs * time;
	}
}

#endif
