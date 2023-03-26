#include "rt/test/assert.hh"
#include "rt/math/quadratic.hh"

void test_math_quadratic(int, char**) {
	rt::real t0, t1;
	rt::real a = 0.5f;
	rt::real b = -2.5f;
	rt::real c = 2.0f;

	RT_ASSERT(rt::quadratic(a, b, c, t0, t1));
	RT_ASSERT(t0 == 1);
	RT_ASSERT(t1 == 4);
}
