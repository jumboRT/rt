#include "rt/test/assert.hh"
#include "rt/math/vector.hh"

void test_math_vector(int, char**) {
	rt::vector<double, 3> i, j, k;

	i = rt::make_vector<double>(1, 2, 3);
	tangents(i, j, k);

	RT_ASSERT(dot(i, j) == 0);
	RT_ASSERT(dot(i, k) == 0);
	RT_ASSERT(dot(j, k) == 0);
}
