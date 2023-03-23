#ifndef RT_TEST_DEBUG_HH
#define RT_TEST_DEBUG_HH

#include "rt/math/vector.hh"
#include "rt/math/matrix.hh"

#include <ostream>

namespace rt {
	template<class CharT, class T, std::size_t N>
	std::basic_ostream<CharT>& operator<<(std::basic_ostream<CharT>& os, const vector<T, N>& arg) {
		const char *delim = "[";

		for (std::size_t i = 0; i < N; i++) {
			os << delim << arg[i];
			delim = " ";
		}

		return os << "]";
	}
	
	template<class CharT, class T, std::size_t R, std::size_t C>
	std::basic_ostream<CharT>& operator<<(std::basic_ostream<CharT>& os, const matrix<T, R, C>& arg) {
		const char *delim = "[";

		for (std::size_t i = 0; i < R; i++) {
			os << delim << arg[i];
			delim = " ";
		}

		return os << "]";
	}
}

#endif
