#include "rt/test/assert.hh"
#include "rt/math/vector.hh"

void test_math_vector(int, char**) {
	rt::vec3f i, j, k;

	i = rt::vec3f(1, 2, 3);
	tangents(i, j, k);

	RT_ASSERT(dot(i, j) == 0);
	RT_ASSERT(dot(i, k) == 0);
	RT_ASSERT(dot(j, k) == 0);
}
