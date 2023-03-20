#ifndef RT_TEST_DEBUG_HH
#define RT_TEST_DEBUG_HH

#include "rt/math/vector.hh"

#include <ostream>

namespace rt {
	template<class CharT, class T, std::size_t N>
	constexpr std::basic_ostream<CharT>& operator<<(std::basic_ostream<CharT>& os, const vector<T, N>& vec) {
		const char *delim = "[";

		for (std::size_t i = 0; i < N; i++) {
			os << delim << vec[i];
			delim = " ";
		}

		return os << "]";
	}

	// TODO: matrix printen
}

#endif
