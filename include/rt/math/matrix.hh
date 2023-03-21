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
		constexpr matrix() = default;

		constexpr matrix(const T& arg) {
			for (std::size_t i = 0; i < R; i++) {
				for (std::size_t j = 0; j < C; j++) {
					rows[i][j] = i == j ? arg : 0;
				}
			}
		}

		template<class U>
		constexpr explicit matrix(const matrix<U, R, C>& arg) {
			rows = static_cast<vector<vector<U, C>, R>>(arg.rows);
		}

		constexpr vector<T, C>& operator[](std::size_t index) {
			return rows[index];
		}

		constexpr const vector<T, C>& operator[](std::size_t index) const {
			return rows[index];
		}

		constexpr friend bool operator==(const matrix& a, const matrix& b) {
			return a.rows == b.rows;
		}

		constexpr friend bool operator!=(const matrix& a, const matrix& b) {
			return !(a == b);
		}
	};

	template<class T, std::size_t N>
	constexpr matrix<T, N, N> inverse(const matrix<T, N, N>& arg) {
		// TODO
		return arg;
	}

	template<class T, std::size_t R, std::size_t C>
	constexpr matrix<T, R, C> transpose(const matrix<T, C, R>& arg) {
		matrix<T, R, C> out;

		for (std::size_t i = 0; i < R; i++) {
			for (std::size_t j = 0; j < C; j++) {
				out[i][j] = arg[j][i];
			}
		}
		
		return out;
	}

	/*
	 * A B C	F
	 * C D E	G
	 *			H
	 */

	template<class T, class U, std::size_t M, std::size_t N, std::size_t P>
	constexpr auto operator*(const matrix<T, M, N> &lhs, const matrix<U, N, P> &rhs) -> matrix<decltype(lhs[0][0] * rhs[0][0]), M, P> {
		//NOT DONE
		matrix<decltype(lhs[0][0] * rhs[0][0]), M, P> result;
		for (std::size_t i = 0; i < P; ++i)
			for (std::size_t j = 0; i < N; ++j)
				for (std::size_t c = 0; i < N; ++j)
					result[j][i] += lhs[j][c] * rhs[c][i];
		return result;
	}
}

#endif
