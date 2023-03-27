#include "rt/test/assert.hh"
#include "rt/math/matrix.hh"

void test_math_matrix(int, char**) {
	rt::mat2f identity, mat, inv;

	identity = rt::mat2f::identity();
	mat[0] = rt::vec2f(1, 3);
	mat[1] = rt::vec2f(2, 4);
	inv = inverse(mat);

	RT_ASSERT(mat(inv) == identity);
	RT_ASSERT(inv(mat) == identity);
	RT_ASSERT(mat == inverse(inv));
}
