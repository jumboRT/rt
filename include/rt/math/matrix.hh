#ifndef RT_MATH_MATRIX_HH
#define RT_MATH_MATRIX_HH

#include "rt/math/vector.hh"

#include <cstddef>

// TODO: meer transforms (look-at, rodrigues', etc.)

namespace rt {
	template<class T, std::size_t R, std::size_t C = R>
	class mat {
	private:
		vec<vec<T, C>, R> rows;
	public:
		mat() = default;

		template<class U, std::size_t S, std::size_t D>
		RT_DEVICE explicit mat(const mat<U, S, D>& arg) {
			for (std::size_t i = 0; i < min(R, S); i++) {
				rows[i] = static_cast<vec<T, C>>(arg[i]);
			}
		}

		RT_DEVICE mat(const T& val) {
			for (std::size_t i = 0; i < R; i++) {
				rows[i] = val;
			}
		}

		template<class U, std::size_t S, std::size_t D>
		RT_DEVICE explicit mat(const mat<U, S, D>& arg, const T& val) {
			for (std::size_t i = 0; i < min(R, S); i++) {
				rows[i] = vec<T, C>(arg[i], val);
			}
			
			for (std::size_t i = S; i < R; i++) {
				rows[i] = val;
			}
		}

		RT_DEVICE vec<T, C>& operator[](std::size_t index) {
			return rows[index];
		}

		RT_DEVICE const vec<T, C>& operator[](std::size_t index) const {
			return rows[index];
		}

		RT_DEVICE friend bool operator==(const mat& a, const mat& b) {
			return a.rows == b.rows;
		}

		RT_DEVICE friend bool operator!=(const mat& a, const mat& b) {
			return !(a == b);
		}

		RT_DEVICE mat operator-() const {
			mat out;

			out.rows = -rows;

			return out;
		}

		RT_DEVICE mat& operator+=(const mat& arg) {
			return rows += arg.rows, *this;
		}

		RT_DEVICE mat& operator-=(const mat& arg) {
			return rows -= arg.rows, *this;
		}

		RT_DEVICE mat& operator*=(const T& arg) {
			return rows *= arg.rows, *this;
		}

		RT_DEVICE mat& operator/=(const T& arg) {
			return rows /= arg.rows, *this;
		}

		RT_DEVICE friend mat operator+(mat a, const mat& b) {
			return a += b;
		}

		RT_DEVICE friend mat operator-(mat a, const mat& b) {
			return a -= b;
		}

		RT_DEVICE friend mat operator*(mat a, const T& b) {
			return a *= b;
		}

		RT_DEVICE friend mat operator/(mat a, const T& b) {
			return a /= b;
		}

		RT_DEVICE vec<T, R> column(std::size_t index) const {
			vec<T, R> out;
			
			for (std::size_t i = 0; i < R; i++) {
				out[i] = rows[i][index];
			}

			return out;
		}

		RT_DEVICE mat<T, C, R> transpose() const {
			mat<T, C, R> out;

			for (std::size_t i = 0; i < C; i++) {
				out[i] = column(i);
			}
			
			return out;
		}
	
		RT_DEVICE vec<T, R> operator()(const vec<T, C>& arg) const {
			vec<T, R> out;

			for (std::size_t i = 0; i < R; i++) {
				out[i] = dot(rows[i], arg);
			}

			return out;
		}

		template<std::size_t N>
		RT_DEVICE mat<T, R, N> operator()(const mat<T, C, N>& arg) const {
			mat<T, R, N> out;
			
			for (std::size_t i = 0; i < R; i++) {
				for (std::size_t j = 0; j < N; j++) {
					out[i][j] = dot(rows[i], arg.column(j));
				}
			}

			return out;
		}

		RT_DEVICE static mat identity() {
			mat out = 0;

			for (std::size_t i = 0; i < min(R, C); i++) {
				out[i][i] = 1;
			}

			return out;
		}

		template<std::size_t N>
		RT_DEVICE static mat scale(const vec<T, N>& arg) {
			mat out = identity();

			for (std::size_t i = 0; i < min(N, min(R, C)); i++) {
				out[i][i] = arg[i];
			}

			return out;
		}

		RT_DEVICE static mat rotate(std::size_t x, std::size_t y, const T& theta) {
			mat out = identity();

			out[x][x] = cos(theta);
			out[x][y] = -sin(theta);
			out[y][x] = sin(theta);
			out[y][y] = cos(theta);

			return out;
		}

		template<std::size_t N>
		RT_DEVICE static mat translate(const vec<T, N>& arg) {
			mat<T, N, N> out = identity();

			for (std::size_t i = 0; i < min(N, C); i++) {
				out[N - 1][i] = arg[i];
			}

			return out;
		}
	};
	
	template<class T>
	using mat2 = mat<T, 2>;

	template<class T>
	using mat3 = mat<T, 3>;

	template<class T>
	using mat4 = mat<T, 4>;

	template<std::size_t N, std::size_t M = N>
	using matf = mat<float_t, N, M>;

	using mat2f = mat2<float_t>;
	using mat3f = mat3<float_t>;
	using mat4f = mat4<float_t>;

	// https://en.wikipedia.org/wiki/Gaussian_elimination
	template<class T, std::size_t N>
	RT_DEVICE mat<T, N> inverse(mat<T, N> arg) {
		mat<T, N> out = mat<T, N>::identity();

		for (std::size_t i = 0; i < N; i++) {
			std::size_t index = i;
			T value = abs(arg[i][i]);

			for (std::size_t j = i + 1; j < N; j++) {
				T tmp = abs(arg[j][i]);

				if (tmp > value) {
					index = j;
					value = std::move(tmp);
				}
			}

			swap(out[i], out[index]);
			swap(arg[i], arg[index]);
			out[i] /= arg[i][i];
			arg[i] /= arg[i][i];

			for (std::size_t j = 0; j < i; j++) {
				out[j] -= out[i] * arg[j][i];
			}

			for (std::size_t j = i + 1; j < N; j++) {
				out[j] -= out[i] * arg[j][i];
				arg[j] -= arg[i] * arg[j][i];
			}
		}

		return out;
	}
}

#endif
