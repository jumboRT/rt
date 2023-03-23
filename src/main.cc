#include "rt/math/vector.hh"
#include "rt/math/matrix.hh"
#include "rt/test/debug.hh"
#include "rt/test/assert.hh"

#include <iostream>

// TODO: __device__ voor cuda
// TODO: quaternions (lijken heel erg op 4d vectors)

int main() {
	std::cout << normalize(rt::make_vector<float>(1, 2, 3)) << std::endl;
}
