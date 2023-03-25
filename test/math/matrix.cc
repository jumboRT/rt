#include "rt/test/assert.hh"
#include "rt/math/matrix.hh"

void test_math_matrix(int, char**) {
	rt::matrix<double, 2, 2> identity, mat, inv;

	identity = rt::identity<double, 2>();
	mat[0] = rt::make_vector<double>(1, 3);
	mat[1] = rt::make_vector<double>(2, 4);
	inv = inverse(mat);

	RT_ASSERT(mat(inv) == identity);
	RT_ASSERT(inv(mat) == identity);
	RT_ASSERT(mat == inverse(inv));
}
