#ifndef RT_MATH_RAY_HH
#define RT_MATH_RAY_HH

#include "rt/math/vector.hh"

namespace rt {
	template<class T, std::size_t N>
	class ray {
	public:
		vec<T, N> origin;
		vec<T, N> direction;
		T time;

		ray() = default;

		RT_DEVICE ray(const vec<T, N>& origin, const vec<T, N>& direction, const T& time) {
			this->origin = origin;
			this->direction = direction;
			this->time = time;
		}

		template<class U, std::size_t M>
		RT_DEVICE explicit ray(const ray<U, M>& arg) {
			origin = static_cast<vec<T, N>>(arg.origin);
			direction = static_cast<vec<T, N>>(arg.direction);
			time = static_cast<T>(arg.time);
		}

		RT_DEVICE vec<T, N> operator()(const float_t& t) const {
			return origin + direction * t;
		}

		RT_DEVICE friend bool operator==(const ray& a, const ray& b) {
			return a.origin == b.origin && a.direction == b.direction && a.time == b.time;
		}

		RT_DEVICE friend bool operator!=(const ray& a, const ray& b) {
			return !(a == b);
		}
	};

	template<class T>
	using ray2 = ray<T, 2>;

	template<class T>
	using ray3 = ray<T, 3>;

	template<class T>
	using ray4 = ray<T, 4>;

	template<std::size_t N>
	using rayf = ray<float_t, N>;

	using ray2f = ray2<float_t>;
	using ray3f = ray3<float_t>;
	using ray4f = ray4<float_t>;
}

#endif
