#include "rt/math/vector.hh"
#include "rt/math/matrix.hh"
#include "rt/math/quaternion.hh"
#include "rt/test/debug.hh"
#include "rt/test/assert.hh"

#include <iostream>

// TODO: __device__ voor cuda
// TODO: meer transforms (look-at, rodrigues', etc.)
// TODO: meer quaternion operations
// TODO: quaternions als (vector<T, 3>, T) ipv (vector<T, 4>)?

int main() {
	rt::matrix<float, 4, 4> q0 = 1;
	-q0;
}
