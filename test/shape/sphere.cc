#include "rt/test/assert.hh"
#include "rt/shape/sphere.hh"
#include "rt/math/intersection.hh"

#define RT_EPSILON 0.000001f

void test_shape_sphere(int, char**) {
	rt::intersection i;
	rt::vec3f origin = rt::vec3f(1, 1, 1);
	rt::vec3f normal = normalize(origin);
	rt::ray3f ray(origin, -normal, 0);
	rt::sphere sphere(1);

	intersect(sphere, ray, i);

	RT_ASSERT(rt::abs(i.time - rt::sqrt(3.0f) + 1) <= RT_EPSILON);
	RT_ASSERT(rt::distance(i.point, normal) <= RT_EPSILON);
	RT_ASSERT(rt::distance(i.normal, normal) <= RT_EPSILON);
}
