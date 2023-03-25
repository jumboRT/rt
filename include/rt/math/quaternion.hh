#ifndef RT_MATH_QUATERNION_HH
#define RT_MATH_QUATERNION_HH

#include "rt/math/vector.hh"

namespace rt {
	template<class T>
	class quaternion {
	private:
		vector<T, 4> elem;
	public:
		quaternion() = default;

		quaternion(const T& arg) {
			elem = arg;
		}

		template<class U>
		explicit quaternion(const vector<U, 4>& arg) {
			elem = static_cast<vector<T, 4>>(arg);
		}

		template<class U>
		explicit quaternion(const quaternion<U>& arg) {
			elem = static_cast<vector<T, 4>>(arg);
		}

		template<class U>
		explicit operator vector<U, 4>() const {
			return static_cast<vector<U, 4>>(elem);
		}

		T& operator[](std::size_t index) {
			return elem[index];
		}

		const T& operator[](std::size_t index) const {
			return elem[index];
		}

		friend bool operator==(const quaternion& a, const quaternion& b) {
			return a.elem == b.elem;
		}

		friend bool operator!=(const quaternion& a, const quaternion& b) {
			return !(a == b);
		}

		quaternion operator-() const {
			quaternion out;

			out.elem = -elem;

			return out;
		}

		quaternion& operator+=(const quaternion& arg) {
			return elem += arg.elem, *this;
		}

		quaternion& operator-=(const quaternion& arg) {
			return elem -= arg.elem, *this;
		}

		quaternion& operator*=(const quaternion& arg) {
			return elem *= arg.elem, *this;
		}

		quaternion& operator/=(const quaternion& arg) {
			return elem /= arg.elem, *this;
		}

		friend quaternion operator+(quaternion a, const quaternion& b) {
			return a += b;
		}

		friend quaternion operator-(quaternion a, const quaternion& b) {
			return a -= b;
		}

		friend quaternion operator*(quaternion a, const quaternion& b) {
			return a *= b;
		}

		friend quaternion operator/(quaternion a, const quaternion& b) {
			return a /= b;
		}
	};

	template<class T>
	T dot(const quaternion<T>& a, const quaternion<T>& b) {
		return dot(vector<T, 4>(a), vector<T, 4>(b));
	}
}

#endif
