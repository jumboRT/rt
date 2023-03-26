#ifndef RT_TEST_DEBUG_HH
#define RT_TEST_DEBUG_HH

#include "rt/math/vector.hh"
#include "rt/math/matrix.hh"
#include "rt/math/quaternion.hh"
#include "rt/math/box.hh"
#include "rt/math/ray.hh"
#include "rt/math/intersection.hh"

#include <ostream>

namespace rt {
	template<class CharT, class T, std::size_t N>
	std::basic_ostream<CharT>& operator<<(std::basic_ostream<CharT>& os, const vec<T, N>& arg) {
		const char *delim = "[";

		for (std::size_t i = 0; i < N; i++) {
			os << delim << arg[i];
			delim = " ";
		}

		return os << "]";
	}
	
	template<class CharT, class T, std::size_t R, std::size_t C>
	std::basic_ostream<CharT>& operator<<(std::basic_ostream<CharT>& os, const mat<T, R, C>& arg) {
		const char *delim = "[";

		for (std::size_t i = 0; i < R; i++) {
			os << delim << arg[i];
			delim = " ";
		}

		return os << "]";
	}
	
	template<class CharT, class T>
	std::basic_ostream<CharT>& operator<<(std::basic_ostream<CharT>& os, const quat<T>& arg) {
		return os << vec<T, 4>(arg);
	}
	
	template<class CharT, class T, std::size_t N>
	std::basic_ostream<CharT>& operator<<(std::basic_ostream<CharT>& os, const box<T, N>& arg) {
		os << "[min=" << arg.min;
		os << " max=" << arg.max;
		return os << "]";
	}
	
	template<class CharT, class T, std::size_t N>
	std::basic_ostream<CharT>& operator<<(std::basic_ostream<CharT>& os, const ray<T, N>& arg) {
		os << "[origin=" << arg.origin;
		os << " direction=" << arg.direction;
		os << " time=" << arg.time;
		return os << "]";
	}
	
	template<class CharT>
	std::basic_ostream<CharT>& operator<<(std::basic_ostream<CharT>& os, const intersection& arg) {
		os << "[point=" << arg.point;
		os << " normal=" << arg.normal;
		os << " time=" << arg.time;
		return os << "]";
	}
}

#endif
