#ifndef RT_MATH_MATRIX_HH
#define RT_MATH_MATRIX_HH

#include "rt/math/vector.hh"

#include <cstddef>

namespace rt {
	template<class T, std::size_t R, std::size_t C>
	class matrix {
	private:
		vector<vector<T, C>, R> rows;
	public:
		matrix() = default;

		matrix(const T& arg) {
			for (std::size_t i = 0; i < R; i++) {
				rows[i] = vector<T, C>(arg);
			}
		}

		template<class U, std::size_t S, std::size_t D>
		explicit matrix(const matrix<U, S, D>& arg) {
			for (std::size_t i = 0; i < min(R, S); i++) {
				rows[i] = static_cast<vector<T, C>>(arg[i]);
			}
		}

		vector<T, C>& operator[](std::size_t index) {
			return rows[index];
		}

		const vector<T, C>& operator[](std::size_t index) const {
			return rows[index];
		}

		friend bool operator==(const matrix& a, const matrix& b) {
			return a.rows == b.rows;
		}

		friend bool operator!=(const matrix& a, const matrix& b) {
			return !(a == b);
		}

		matrix operator-() const {
			return matrix { -rows };
		}

		matrix& operator+=(const matrix& arg) {
			return rows += arg.rows, *this;
		}

		matrix& operator-=(const matrix& arg) {
			return rows -= arg.rows, *this;
		}

		matrix& operator*=(const matrix& arg) {
			return rows *= arg.rows, *this;
		}

		matrix& operator/=(const matrix& arg) {
			return rows /= arg.rows, *this;
		}

		friend matrix operator+(matrix a, const matrix& b) {
			return a += b;
		}

		friend matrix operator-(matrix a, const matrix& b) {
			return a -= b;
		}

		friend matrix operator*(matrix a, const matrix& b) {
			return a *= b;
		}

		friend matrix operator/(matrix a, const matrix& b) {
			return a /= b;
		}

		vector<T, R> column(std::size_t index) const {
			vector<T, R> out;
			
			for (std::size_t i = 0; i < R; i++) {
				out[i] = rows[i][index];
			}

			return out;
		}

		matrix<T, C, R> transpose() const {
			matrix<T, C, R> out;

			for (std::size_t i = 0; i < C; i++) {
				out[i] = column(i);
			}
			
			return out;
		}
	
		vector<T, R> operator()(const vector<T, C>& arg) const {
			vector<T, R> out;

			for (std::size_t i = 0; i < R; i++) {
				out[i] = dot(rows[i], arg);
			}

			return out;
		}

		template<std::size_t N>
		matrix<T, R, N> operator()(const matrix<T, C, N>& arg) const {
			matrix<T, R, N> out;
			
			for (std::size_t i = 0; i < R; i++) {
				for (std::size_t j = 0; j < N; j++) {
					out[i][j] = dot(rows[i], arg.column(j));
				}
			}

			return out;
		}
	};

	template<class T, std::size_t N>
	matrix<T, N, N> identity() {
		matrix<T, N, N> out;

		for (std::size_t i = 0; i < N; i++) {
			out[i] = 0;
			out[i][i] = 1;
		}

		return out;
	}

	template<class T, std::size_t N, std::size_t M>
	matrix<T, N, N> scale(const vector<T, M>& arg) {
		matrix<T, N, N> out = identity<T, N>();

		static_assert(N >= M, "matrix too small");

		for (std::size_t i = 0; i < M; i++) {
			out[i][i] = arg[i];
		}

		return out;
	}

	template<class T, std::size_t N>
	matrix<T, N, N> rotate(std::size_t x, std::size_t y, const T& theta) {
		matrix<T, N, N> out = identity<T, N>();

		out[x][x] = cos(theta);
		out[x][y] = -sin(theta);
		out[y][x] = sin(theta);
		out[y][y] = cos(theta);

		return out;
	}

	template<class T, std::size_t N, std::size_t M>
	matrix<T, N, N> translate(const vector<T, M>& arg) {
		matrix<T, N, N> out = identity<T, N>();

		static_assert(N >= M, "matrix too small");

		for (std::size_t i = 0; i < M; i++) {
			out[N - 1][i] = arg[i];
		}

		return out;
	}

	// https://en.wikipedia.org/wiki/Gaussian_elimination
	template<class T, std::size_t N>
	matrix<T, N, N> inverse(matrix<T, N, N> arg) {
		matrix<T, N, N> out = identity<T, N>();

		for (std::size_t i = 0; i < N; i++) {
			std::size_t index = i;
			T value = abs(arg[i][i]);

			for (std::size_t j = i + 1; j < N; j++) {
				T tmp = abs(arg[j][i]);

				if (tmp > value) {
					index = j;
					value = tmp;
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
