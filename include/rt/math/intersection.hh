#ifndef RT_MATH_INTERSECTION_HH
#define RT_MATH_INTERSECTION_HH

#include "rt/math/vector.hh"

namespace rt {
	class intersection {
	public:
		vec3f point;
		vec3f normal;
		real time;
	};
}

#endif
