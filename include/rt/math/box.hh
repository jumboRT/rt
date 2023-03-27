#ifndef RT_MATH_BOX_HH
#define RT_MATH_BOX_HH

#include "rt/math/vector.hh"

#include <limits>

namespace rt {
	template<class T, std::size_t N>
	class box {
	public:
		vec<T, N> min;
		vec<T, N> max;

		box() = default;

		RT_DEVICE box(vec<T, N> arg) {
			min = arg;
			max = std::move(arg);
		}

		RT_DEVICE box(vec<T, N> min, vec<T, N> max) {
			this->min = std::move(min);
			this->max = std::move(max);
		}

		template<class U, std::size_t M>
		RT_DEVICE explicit box(const box<U, M>& arg) {
			min = static_cast<vec<T, N>>(arg.min);
			max = static_cast<vec<T, N>>(arg.max);
		}

		RT_DEVICE operator bool() const {
			for (std::size_t i = 0; i < N; i++) {
				if (max[i] <= min[i]) {
					return false;
				}
			}

			return true;
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

		RT_DEVICE static box empty() {
			return box(std::numeric_limits<T>::lowest(), std::numeric_limits<T>::max());
		}
	};

	template<class T>
	using box2 = box<T, 2>;

	template<class T>
	using box3 = box<T, 3>;

	template<class T>
	using box4 = box<T, 4>;

	template<std::size_t N>
	using boxf = box<float_t, N>;

	template<std::size_t N>
	using boxz = box<std::size_t, N>;

	using box2f = box2<float_t>;
	using box3f = box3<float_t>;
	using box4f = box4<float_t>;

	using box2z = box2<std::size_t>;
	using box3z = box3<std::size_t>;
	using box4z = box4<std::size_t>;

	template<class T, std::size_t N>
	RT_DEVICE bool contains(const box<T, N>& a, const vec<T, N>& b) {
		for (std::size_t i = 0; i < N; i++) {
			if (a.min[i] < b[i] || a.max[i] > b[i]) {
				return false;
			}
		}

		return true;
	}

	template<class T, std::size_t N>
	RT_DEVICE bool contains_exclusive(const box<T, N>& a, const vec<T, N>& b) {
		for (std::size_t i = 0; i < N; i++) {
			if (a.min[i] < b[i] || a.max[i] >= b[i]) {
				return false;
			}
		}

		return true;
	}

	template<class T, std::size_t N>
	RT_DEVICE vec<T, N> size(const box<T, N>& arg) {
		return arg.max - arg.min;
	}

	template<class T, std::size_t N>
	RT_DEVICE T interior(const box<T, N>& arg) {
		return product(size(arg));
	}

	template<class T, std::size_t N>
	RT_DEVICE T exterior(const box<T, N>& arg) {
		vec<T, N> out = 1;

		for (std::size_t i = 0; i < N; i++) {
			for (std::size_t j = 0; j < N; j++) {
				if (i != j) {
					out[i] *= arg[j];
				}
			}
		}

		return 2 * sum(out);
	}

	template<class T, std::size_t N>
	RT_DEVICE std::size_t min_index(const box<T, N>& arg) {
		return min_index(size(arg));
	}

	template<class T, std::size_t N>
	RT_DEVICE std::size_t max_index(const box<T, N>& arg) {
		return max_index(size(arg));
	}

	template<class T, std::size_t N>
	RT_DEVICE vec<T, N> lerp(const box<T, N>& arg, const vec<T, N>& t) {
		return lerp(arg.min, arg.max, t);
	}
}

#endif
