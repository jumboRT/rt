#ifndef RT_MATH_QUATERNION_HH
#define RT_MATH_QUATERNION_HH

#include "rt/math/vector.hh"

namespace rt {
	template<class T>
	class quat {
	private:
		vec4<T> elem;
	public:
		quat() = default;

		RT_DEVICE quat(const T& val) {
			elem = val;
		}

		RT_DEVICE quat(T x, T y, T z, T w) {
			elem = vec4<T>(std::move(x), std::move(y), std::move(z), std::move(w));
		}

		RT_DEVICE quat(const vec3<T>& axis, const T& theta) {
			*this = quat(cos(theta / 2), axis * sin(theta / 2));
		}

		template<class U>
		RT_DEVICE explicit quat(const U& x, const vec3<U>& arg) {
			elem = vec4<T>(static_cast<T>(x), static_cast<T>(arg[0]), static_cast<T>(arg[1]), static_cast<T>(arg[2]));
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
		RT_DEVICE explicit operator vec3<U>() const {
			return vec3<U>(static_cast<U>(elem[1]), static_cast<U>(elem[2]), static_cast<U>(elem[3]));
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
			return quat(-elem);
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

		RT_DEVICE vec3<T> operator()(vec3<T> arg) const {
			return vec3<T>((*this)(quat(0, arg))(quat(elem[0], -elem[1], -elem[2], -elem[3])));
		}

		RT_DEVICE quat operator()(const quat& arg) const {
			T x = elem[0] * arg[0] - elem[1] * arg[1] - elem[2] * arg[2] - elem[3] * arg[3];
			T y = elem[0] * arg[1] + elem[1] * arg[0] + elem[2] * arg[3] - elem[3] * arg[2];
			T z = elem[0] * arg[2] - elem[1] * arg[3] + elem[2] * arg[0] + elem[3] * arg[1];
			T w = elem[0] * arg[3] + elem[1] * arg[2] - elem[2] * arg[1] + elem[3] * arg[0];

			return quat(std::move(x), std::move(y), std::move(z), std::move(w));
		}
	};

	using quatf = quat<float_t>;

	template<class T>
	RT_DEVICE T dot(const quat<T>& a, const quat<T>& b) {
		return dot(vec4<T>(a), vec4<T>(b));
	}

	template<class T>
	RT_DEVICE T length(const quat<T>& arg) {
		return length(vec4<T>(arg));
	}

	template<class T>
	RT_DEVICE quat<T> normalize(const quat<T>& arg) {
		return quat<T>(normalize(vec4<T>(arg)));
	}

	template<class T>
	RT_DEVICE quat<T> lerp(const quat<T>& a, const quat<T>& b, const T& t) {
		return quat<T>(lerp(vec4<T>(a), vec4<T>(b), t));
	}

	template<class T>
	RT_DEVICE quat<T> slerp(const quat<T>& a, const quat<T>& b, const T& t) {
		T cos_theta = dot(a, b);

		if (cos_theta > 0.999f) {
			return normalize(lerp(a, b, t));
		} else {
			T theta = acos(clamp(cos_theta, -1, 1)) * t;

			return a * cos(theta) + normalize(b - a * cos_theta) * sin(theta);
		}
	}
}

#endif
