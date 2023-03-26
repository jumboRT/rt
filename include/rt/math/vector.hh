#ifndef RT_MATH_VECTOR_HH
#define RT_MATH_VECTOR_HH

#include "rt/math/math.hh"

#include <cstddef>

namespace rt {
	template<class T, std::size_t N>
	class vec {
	private:
		T elem[N];
	public:
		vec() = default;

		RT_DEVICE vec(const T& arg) {
			for (std::size_t i = 0; i < N; i++) {
				elem[i] = arg;
			}
		}

		template<class U, std::size_t M>
		RT_DEVICE explicit vec(const vec<U, M>& arg) {
			for (std::size_t i = 0; i < min(N, M); i++) {
				elem[i] = static_cast<T>(arg[i]);
			}
		}

		RT_DEVICE T& operator[](std::size_t index) {
			return elem[index];
		}

		RT_DEVICE const T& operator[](std::size_t index) const {
			return elem[index];
		}

		RT_DEVICE friend bool operator==(const vec& a, const vec& b) {
			for (std::size_t i = 0; i < N; i++) {
				if (a[i] != b[i]) {
					return false;
				}
			}

			return true;
		}

		RT_DEVICE friend bool operator!=(const vec& a, const vec& b) {
			return !(a == b);
		}

		RT_DEVICE vec operator-() const {
			vec out;

			for (std::size_t i = 0; i < N; i++) {
				out[i] = -elem[i];
			}

			return out;
		}

		RT_DEVICE vec& operator+=(const vec& arg) {
			for (std::size_t i = 0; i < N; i++) {
				elem[i] += arg[i];
			}

			return *this;
		}

		RT_DEVICE vec& operator-=(const vec& arg) {
			for (std::size_t i = 0; i < N; i++) {
				elem[i] -= arg[i];
			}

			return *this;
		}

		RT_DEVICE vec& operator*=(const vec& arg) {
			for (std::size_t i = 0; i < N; i++) {
				elem[i] *= arg[i];
			}

			return *this;
		}

		RT_DEVICE vec& operator/=(const vec& arg) {
			for (std::size_t i = 0; i < N; i++) {
				elem[i] /= arg[i];
			}

			return *this;
		}

		RT_DEVICE friend vec operator+(vec a, const vec& b) {
			return a += b;
		}

		RT_DEVICE friend vec operator-(vec a, const vec& b) {
			return a -= b;
		}

		RT_DEVICE friend vec operator*(vec a, const vec& b) {
			return a *= b;
		}

		RT_DEVICE friend vec operator/(vec a, const vec& b) {
			return a /= b;
		}
	};

	template<class T>
	using vec2 = vec<T, 2>;

	template<class T>
	using vec3 = vec<T, 3>;

	template<class T>
	using vec4 = vec<T, 4>;

	template<std::size_t N>
	using vecf = vec<real, N>;

	template<std::size_t N>
	using vecz = vec<std::size_t, N>;

	using vec2f = vec2<real>;
	using vec3f = vec3<real>;
	using vec4f = vec4<real>;

	using vec2z = vec2<std::size_t>;
	using vec3z = vec3<std::size_t>;
	using vec4z = vec4<std::size_t>;

	template<class T, class... Args>
	RT_DEVICE vec<T, sizeof...(Args)> vector(const Args&... args) {
		T elem[] = { static_cast<T>(args)... };
		vec<T, sizeof...(Args)> out;

		for (std::size_t i = 0; i < sizeof...(Args); i++) {
			out[i] = elem[i];
		}

		return out;
	}

	template<class T, class U, std::size_t N, class... Args>
	RT_DEVICE vec<T, sizeof...(Args) + N> vector(const vec<U, N>& arg, const Args&... args) {
		T elem[] = { static_cast<T>(args)... };
		vec<T, sizeof...(Args) + N> out(arg);

		for (std::size_t i = 0; i < sizeof...(Args); i++) {
			out[N + i] = elem[i];
		}
		
		return out;
	}

	template<class T, std::size_t N>
	RT_DEVICE vec<T, N> floor(const vec<T, N>& arg) {
		vec<T, N> out;

		for (std::size_t i = 0; i < N; i++) {
			out[i] = floor(arg[i]);
		}

		return out;
	}

	template<class T, std::size_t N>
	RT_DEVICE vec<T, N> ceil(const vec<T, N>& arg) {
		vec<T, N> out;

		for (std::size_t i = 0; i < N; i++) {
			out[i] = ceil(arg[i]);
		}

		return out;
	}

	template<class T, std::size_t N>
	RT_DEVICE vec<T, N> abs(const vec<T, N>& arg) {
		vec<T, N> out;

		for (std::size_t i = 0; i < N; i++) {
			out[i] = abs(arg[i]);
		}

		return out;
	}

	template<class T, std::size_t N>
	RT_DEVICE vec<T, N> min(const vec<T, N>& a, const vec<T, N>& b) {
		vec<T, N> out;

		for (std::size_t i = 0; i < N; i++) {
			out[i] = min(a[i], b[i]);
		}

		return out;
	}

	template<class T, std::size_t N>
	RT_DEVICE vec<T, N> max(const vec<T, N>& a, const vec<T, N>& b) {
		vec<T, N> out;

		for (std::size_t i = 0; i < N; i++) {
			out[i] = max(a[i], b[i]);
		}

		return out;
	}

	template<class T, std::size_t N>
	RT_DEVICE std::size_t min_index(const vec<T, N>& arg) {
		std::size_t out = 0;

		for (std::size_t i = 1; i < N; i++) {
			if (arg[i] < arg[out]) {
				out = i;
			}
		}

		return out;
	}

	template<class T, std::size_t N>
	RT_DEVICE std::size_t max_index(const vec<T, N>& arg) {
		std::size_t out = 0;

		for (std::size_t i = 1; i < N; i++) {
			if (arg[i] > arg[out]) {
				out = i;
			}
		}

		return out;
	}

	template<class T, std::size_t N>
	RT_DEVICE T& min(vec<T, N>& arg) {
		return arg[min_index(arg)];
	}

	template<class T, std::size_t N>
	RT_DEVICE const T& min(const vec<T, N>& arg) {
		return arg[min_index(arg)];
	}

	template<class T, std::size_t N>
	RT_DEVICE T& max(vec<T, N>& arg) {
		return arg[max_index(arg)];
	}

	template<class T, std::size_t N>
	RT_DEVICE const T& max(const vec<T, N>& arg) {
		return arg[max_index(arg)];
	}
	
	template<class T, std::size_t N>
	RT_DEVICE T sum(const vec<T, N>& arg) {
		T out = arg[0];

		for (std::size_t i = 1; i < N; i++) {
			out += arg[i];
		}

		return out;
	}
	
	template<class T, std::size_t N>
	RT_DEVICE T product(const vec<T, N>& arg) {
		T out = arg[0];

		for (std::size_t i = 1; i < N; i++) {
			out *= arg[i];
		}

		return out;
	}

	template<class T, std::size_t N>
	RT_DEVICE T dot(const vec<T, N>& a, const vec<T, N>& b) {
		return sum(a * b);
	}

	template<class T, std::size_t N>
	RT_DEVICE T abs_dot(const vec<T, N>& a, const vec<T, N>& b) {
		return abs(dot(a, b));
	}

	template<class T, std::size_t N>
	RT_DEVICE T length_squared(const vec<T, N>& arg) {
		return dot(arg, arg);
	}

	template<class T, std::size_t N>
	RT_DEVICE T length(const vec<T, N>& arg) {
		return sqrt(length_squared(arg));
	}

	template<class T, std::size_t N>
	RT_DEVICE T distance_squared(const vec<T, N>& a, const vec<T, N>& b) {
		return length_squared(a - b);
	}

	template<class T, std::size_t N>
	RT_DEVICE T distance(const vec<T, N>& a, const vec<T, N>& b) {
		return length(a - b);
	}

	template<class T, std::size_t N>
	RT_DEVICE vec<T, N> normalize(const vec<T, N>& arg) {
		return arg / length(arg);
	}

	template<class T>
	RT_DEVICE vec3<T> cross(const vec3<T>& a, const vec3<T>& b) {
		T x = a[1] * b[2] - a[2] * b[1];
		T y = a[2] * b[0] - a[0] * b[2];
		T z = a[0] * b[1] - a[1] * b[0];

		return vector<T>(x, y, z);
	}

	// https://en.wikipedia.org/wiki/Rodrigues%27_rotation_formula
	template<class T>
	RT_DEVICE vec3<T> rotate(const vec3<T>& vec, const vec3<T>& axis, const T& theta) {
		return vec * cos(theta) + cross(vec, axis) * sin(theta) + axis * dot(axis, vec) * (1 - cos(theta));
	}

	template<class T>
	RT_DEVICE void tangents(const vec3<T>& i, vec3<T>& j, vec3<T>& k) {
		if (abs(i[0]) > abs(i[1])) {
			j = normalize(vector<T>(-i[2], 0, i[0]));
		} else {
			j = normalize(vector<T>(0, i[2], -i[1]));
		}

		k = cross(i, j);
	}

	template<class T, std::size_t N, std::size_t M>
	RT_DEVICE vec<T, N> permute(const vec<T, M>& arg, const vecz<N>& index) {
		vec<T, N> out;

		for (std::size_t i = 0; i < N; i++) {
			out[i] = arg[index[i]];
		}

		return out;
	}

	template<class T, std::size_t N>
	RT_DEVICE vec<T, N> lerp(const vec<T, N>& a, const vec<T, N>& b, const T& t) {
		return a + t * (b - a);
	}

	template<class T, std::size_t N>
	RT_DEVICE vec<T, N> align(const vec<T, N>& arg, const vec<T, N>& to) {
		return dot(arg, to) < 0 ? -arg : arg;
	}
}

#endif
