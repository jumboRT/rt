#include "rt/test/assert.hh"
#include "rt/math/quadratic.hh"

void test_math_quadratic(int, char**) {
	double t0, t1;

	RT_ASSERT(rt::quadratic(0.5, -2.5, 2.0, t0, t1));
	RT_ASSERT(t0 == 1);
	RT_ASSERT(t1 == 4);
}
