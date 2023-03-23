#ifndef RT_MATH_VECTOR_HH
#define RT_MATH_VECTOR_HH

#include "rt/math/math.hh"

#include <cstddef>

namespace rt {
	template<class T, std::size_t N>
	class vector {
	private:
		T elem[N];
	public:
		vector() = default;

		vector(const T& arg) {
			for (std::size_t i = 0; i < N; i++) {
				elem[i] = arg;
			}
		}

		template<class U, std::size_t M>
		explicit vector(const vector<U, M>& arg) {
			for (std::size_t i = 0; i < min(N, M); i++) {
				elem[i] = static_cast<T>(arg[i]);
			}
		}

		T& operator[](std::size_t index) {
			return elem[index];
		}

		const T& operator[](std::size_t index) const {
			return elem[index];
		}

		friend bool operator==(const vector& a, const vector& b) {
			for (std::size_t i = 0; i < N; i++) {
				if (a[i] != b[i]) {
					return false;
				}
			}

			return true;
		}

		friend bool operator!=(const vector& a, const vector& b) {
			return !(a == b);
		}

		vector operator-() const {
			vector out;

			for (std::size_t i = 0; i < N; i++) {
				out[i] = -elem[i];
			}

			return out;
		}

		vector& operator+=(const vector& arg) {
			for (std::size_t i = 0; i < N; i++) {
				elem[i] += arg[i];
			}

			return *this;
		}

		vector& operator-=(const vector& arg) {
			for (std::size_t i = 0; i < N; i++) {
				elem[i] -= arg[i];
			}

			return *this;
		}

		vector& operator*=(const vector& arg) {
			for (std::size_t i = 0; i < N; i++) {
				elem[i] *= arg[i];
			}

			return *this;
		}

		vector& operator/=(const vector& arg) {
			for (std::size_t i = 0; i < N; i++) {
				elem[i] /= arg[i];
			}

			return *this;
		}

		friend vector operator+(vector a, const vector& b) {
			return a += b;
		}

		friend vector operator-(vector a, const vector& b) {
			return a -= b;
		}

		friend vector operator*(vector a, const vector& b) {
			return a *= b;
		}

		friend vector operator/(vector a, const vector& b) {
			return a /= b;
		}
	};

	template<class T, class... Args>
	vector<T, sizeof...(Args)> make_vector(const Args&... args) {
		T elem[] = { static_cast<T>(args)... };
		vector<T, sizeof...(Args)> out;

		for (std::size_t i = 0; i < sizeof...(Args); i++) {
			out[i] = elem[i];
		}

		return out;
	}

	template<class T, class U, std::size_t N, class... Args>
	vector<T, sizeof...(Args) + N> make_vector(const vector<U, N>& arg, const Args&... args) {
		T elem[] = { static_cast<T>(args)... };
		vector<T, sizeof...(Args) + N> out(arg);

		for (std::size_t i = 0; i < sizeof...(Args); i++) {
			out[N + i] = elem[i];
		}
		
		return out;
	}

	template<class T, std::size_t N>
	vector<T, N> floor(const vector<T, N>& arg) {
		vector<T, N> out;

		for (std::size_t i = 0; i < N; i++) {
			out[i] = floor(arg[i]);
		}

		return out;
	}

	template<class T, std::size_t N>
	vector<T, N> ceil(const vector<T, N>& arg) {
		vector<T, N> out;

		for (std::size_t i = 0; i < N; i++) {
			out[i] = ceil(arg[i]);
		}

		return out;
	}

	template<class T, std::size_t N>
	vector<T, N> abs(const vector<T, N>& arg) {
		vector<T, N> out;

		for (std::size_t i = 0; i < N; i++) {
			out[i] = abs(arg[i]);
		}

		return out;
	}

	template<class T, std::size_t N>
	vector<T, N> min(const vector<T, N>& a, const vector<T, N>& b) {
		vector<T, N> out;

		for (std::size_t i = 0; i < N; i++) {
			out[i] = min(a[i], b[i]);
		}

		return out;
	}

	template<class T, std::size_t N>
	vector<T, N> max(const vector<T, N>& a, const vector<T, N>& b) {
		vector<T, N> out;

		for (std::size_t i = 0; i < N; i++) {
			out[i] = max(a[i], b[i]);
		}

		return out;
	}

	template<class T, std::size_t N>
	std::size_t min_index(const vector<T, N>& arg) {
		std::size_t out = 0;

		for (std::size_t i = 1; i < N; i++) {
			if (arg[i] < arg[out]) {
				out = i;
			}
		}

		return out;
	}

	template<class T, std::size_t N>
	std::size_t max_index(const vector<T, N>& arg) {
		std::size_t out = 0;

		for (std::size_t i = 1; i < N; i++) {
			if (arg[i] > arg[out]) {
				out = i;
			}
		}

		return out;
	}

	template<class T, std::size_t N>
	T& min(vector<T, N>& arg) {
		return arg[min_index(arg)];
	}

	template<class T, std::size_t N>
	const T& min(const vector<T, N>& arg) {
		return arg[min_index(arg)];
	}

	template<class T, std::size_t N>
	T& max(vector<T, N>& arg) {
		return arg[max_index(arg)];
	}

	template<class T, std::size_t N>
	const T& max(const vector<T, N>& arg) {
		return arg[max_index(arg)];
	}
	
	template<class T, std::size_t N>
	T sum(const vector<T, N>& arg) {
		T out = arg[0];

		for (std::size_t i = 1; i < N; i++) {
			out += arg[i];
		}

		return out;
	}
	
	template<class T, std::size_t N>
	T product(const vector<T, N>& arg) {
		T out = arg[0];

		for (std::size_t i = 1; i < N; i++) {
			out *= arg[i];
		}

		return out;
	}

	template<class T, std::size_t N>
	T dot(const vector<T, N>& a, const vector<T, N>& b) {
		return sum(a * b);
	}

	template<class T, std::size_t N>
	T abs_dot(const vector<T, N>& a, const vector<T, N>& b) {
		return abs(dot(a, b));
	}

	template<class T, std::size_t N>
	T length_squared(const vector<T, N>& arg) {
		return dot(arg, arg);
	}

	template<class T, std::size_t N>
	T length(const vector<T, N>& arg) {
		return sqrt(length_squared(arg));
	}

	template<class T, std::size_t N>
	T distance_squared(const vector<T, N>& a, const vector<T, N>& b) {
		return length_squared(a - b);
	}

	template<class T, std::size_t N>
	T distance(const vector<T, N>& a, const vector<T, N>& b) {
		return length(a - b);
	}

	template<class T, std::size_t N>
	vector<T, N> normalize(const vector<T, N>& arg) {
		return arg / length(arg);
	}

	template<class T>
	vector<T, 3> cross(const vector<T, 3>& a, const vector<T, 3>& b) {
		T x = a[1] * b[2] - a[2] * b[1];
		T y = a[2] * b[0] - a[0] * b[2];
		T z = a[0] * b[1] - a[1] * b[0];
		return make_vector<T>(x, y, z);
	}

	template<class T>
	void tangents(const vector<T, 3>& i, vector<T, 3>& j, vector<T, 3>& k) {
		if (abs(i[0]) > abs(i[1])) {
			j = normalize(make_vector<T>(-i[2], 0, i[0]));
		} else {
			j = normalize(make_vector<T>(0, i[2], -i[1]));
		}

		k = cross(i, j);
	}

	template<class T, std::size_t N, std::size_t M>
	vector<T, N> permute(const vector<T, M>& arg, const vector<std::size_t, N>& index) {
		vector<T, N> out;

		for (std::size_t i = 0; i < N; i++) {
			out[i] = arg[index[i]];
		}

		return out;
	}

	template<class T, std::size_t N>
	vector<T, N> lerp(const vector<T, N>& a, const vector<T, N>& b, const T& t) {
		return a + t * (b - a);
	}

	template<class T, std::size_t N>
	vector<T, N> align(const vector<T, N>& arg, const vector<T, N>& to) {
		return dot(arg, to) < 0 ? -arg : arg;
	}
}

#endif
