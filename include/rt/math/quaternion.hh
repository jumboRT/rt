#ifndef RT_MATH_QUATERNION_HH
#define RT_MATH_QUATERNION_HH

#include "rt/math/vector.hh"

// TODO: meer quaternion operations

namespace rt {
	template<class T>
	class quat {
	private:
		vec4<T> elem;
	public:
		quat() = default;

		RT_DEVICE quat(const T& arg) {
			elem = arg;
		}

		template<class U>
		RT_DEVICE explicit quat(const vec4<U>& arg) {
			elem = static_cast<vec4<T>>(arg);
		}

		template<class U>
		RT_DEVICE explicit quat(const quat<U>& arg) {
			elem = static_cast<vec4<T>>(arg);
		}

		template<class U>
		RT_DEVICE explicit operator vec4<U>() const {
			return static_cast<vec4<U>>(elem);
		}

		RT_DEVICE T& operator[](std::size_t index) {
			return elem[index];
		}

		RT_DEVICE const T& operator[](std::size_t index) const {
			return elem[index];
		}

		RT_DEVICE friend bool operator==(const quat& a, const quat& b) {
			return a.elem == b.elem;
		}

		RT_DEVICE friend bool operator!=(const quat& a, const quat& b) {
			return !(a == b);
		}

		RT_DEVICE quat operator-() const {
			quat out;

			out.elem = -elem;

			return out;
		}

		RT_DEVICE quat& operator+=(const quat& arg) {
			return elem += arg.elem, *this;
		}

		RT_DEVICE quat& operator-=(const quat& arg) {
			return elem -= arg.elem, *this;
		}

		RT_DEVICE quat& operator*=(const quat& arg) {
			return elem *= arg.elem, *this;
		}

		RT_DEVICE quat& operator/=(const quat& arg) {
			return elem /= arg.elem, *this;
		}

		RT_DEVICE friend quat operator+(quat a, const quat& b) {
			return a += b;
		}

		RT_DEVICE friend quat operator-(quat a, const quat& b) {
			return a -= b;
		}

		RT_DEVICE friend quat operator*(quat a, const quat& b) {
			return a *= b;
		}

		RT_DEVICE friend quat operator/(quat a, const quat& b) {
			return a /= b;
		}
	};

	using quatf = quat<real>;

	template<class T>
	RT_DEVICE T dot(const quat<T>& a, const quat<T>& b) {
		return dot(vec4<T>(a), vec4<T>(b));
	}
}

#endif
