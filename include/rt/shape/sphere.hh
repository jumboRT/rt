#ifndef RT_SHAPE_SPHERE_HH
#define RT_SHAPE_SPHERE_HH

#include "rt/math/ray.hh"

namespace rt {
	class intersection;

	class sphere {
	private:
		float_t radius;
	public:
		RT_DEVICE sphere(const float_t& radius);
		
		RT_DEVICE friend bool intersect(const sphere& s, const ray3f& r, intersection& i);
	};
}

#endif
