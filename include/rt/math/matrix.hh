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

	template<class T, std::size_t R, std::size_t C>
	vector<T, R> column(const matrix<T, R, C>& arg, std::size_t index) {
		vector<T, R> out;
		
		for (std::size_t i = 0; i < R; i++) {
			out[i] = arg[i][index];
		}

		return out;
	}

	template<class T, std::size_t R, std::size_t C>
	matrix<T, R, C> transpose(const matrix<T, C, R>& arg) {
		matrix<T, R, C> out;

		for (std::size_t i = 0; i < R; i++) {
			out[i] = column(arg, i);
		}
		
		return out;
	}
	
	template<class T, std::size_t R, std::size_t C>
	vector<T, R> operator*(const matrix<T, R, C>& a, const vector<T, C>& b) {
		vector<T, R> out;

		for (std::size_t i = 0; i < R; i++) {
			out[i] = dot(a[i], b);
		}

		return out;
	}

	template<class T, std::size_t R, std::size_t C, std::size_t N>
	matrix<T, R, C> operator*(const matrix<T, R, N>& a, const matrix<T, N, C>& b) {
		matrix<T, R, C> out;
		
		for (std::size_t i = 0; i < R; i++) {
			for (std::size_t j = 0; j < N; j++) {
				out[i][j] = dot(a[i], column(b, j));
			}
		}

		return out;
	}

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
