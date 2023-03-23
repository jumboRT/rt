#include "rt/test/tester.hh"
#include "rt/test/assert.hh"
#include "rt/math/vector.hh"
#include "rt/math/matrix.hh"
#include "rt/math/quadratic.hh"

#include <iostream>

static void test_vector() {
	// dot product of basis vectors is zero
	{
		rt::vector<double, 3> i, j, k;

		i = rt::make_vector<double>(1, 2, 3);
		tangents(i, j, k);

		RT_ASSERT(dot(i, j) == 0);
		RT_ASSERT(dot(i, k) == 0);
		RT_ASSERT(dot(j, k) == 0);
	}
}

static void test_matrix() {
	// product of matrix and inverse is identity
	// inverse of matrix inverse is itself
	{
		rt::matrix<double, 2, 2> identity, mat, inv;

		identity = rt::identity<double, 2>();
		mat[0] = rt::make_vector<double>(1, 3);
		mat[1] = rt::make_vector<double>(2, 4);
		inv = inverse(mat);

		RT_ASSERT(mat * inv == identity);
		RT_ASSERT(inv * mat == identity);
		RT_ASSERT(mat == inverse(inv));
	}
}

static void test_quadratic() {
	// roots of 0.5 * x ^ 2 - 2.5 * x + 2.0 are 1.0 and 4.0
	{
		double t0, t1;

		RT_ASSERT(rt::quadratic(0.5, -2.5, 2.0, t0, t1));
		RT_ASSERT(t0 == 1);
		RT_ASSERT(t1 == 4);
	}
}

int main(int argc, char **argv) {
	rt::tester t;

	t.insert("vector", test_vector);
	t.insert("matrix", test_matrix);
	t.insert("quadratic", test_quadratic);

	if (argc > 1) {
		for (int i = 1; i < argc; i++) {
			t.run(argv[i]);
		}
	} else {
		t.run();
	}

	return EXIT_SUCCESS;
}
