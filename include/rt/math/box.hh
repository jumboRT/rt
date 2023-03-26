#ifndef RT_MATH_BOX_HH
#define RT_MATH_BOX_HH

#include "rt/math/vector.hh"

namespace rt {
	template<class T, std::size_t N>
	class box {
	public:
		vec<T, N> min;
		vec<T, N> max;

		box() = default;

		RT_DEVICE box(const vec<T, N>& min, const vec<T, N>& max) {
			this->min = min;
			this->max = max;
		}

		template<class U, std::size_t M>
		RT_DEVICE explicit box(const box<U, M>& arg) {
			min = static_cast<vec<T, N>>(arg.min);
			max = static_cast<vec<T, N>>(arg.max);
		}

		RT_DEVICE friend bool operator==(const box& a, const box& b) {
			return a.min == b.min && a.max == b.max;
		}

		RT_DEVICE friend bool operator!=(const box& a, const box& b) {
			return !(a == b);
		}

		RT_DEVICE box& operator|=(const box& arg) {
			min = ::rt::min(min, arg.min);
			max = ::rt::max(max, arg.max);

			return *this;
		}

		RT_DEVICE box& operator&=(const box& arg) {
			min = ::rt::max(min, arg.min);
			max = ::rt::min(max, arg.max);

			return *this;
		}

		RT_DEVICE friend box operator|(box a, const box& b) {
			return a |= b;
		}

		RT_DEVICE friend box operator&(box a, const box& b) {
			return a &= b;
		}
	};

	template<class T>
	using box2 = box<T, 2>;

	template<class T>
	using box3 = box<T, 3>;

	template<class T>
	using box4 = box<T, 4>;

	template<std::size_t N>
	using boxf = box<real, N>;

	template<std::size_t N>
	using boxz = box<std::size_t, N>;

	using box2f = box2<real>;
	using box3f = box3<real>;
	using box4f = box4<real>;

	using box2z = box2<std::size_t>;
	using box3z = box3<std::size_t>;
	using box4z = box4<std::size_t>;
}

#endif
