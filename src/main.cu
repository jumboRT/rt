#include "rt/test/debug.hh"
#include "rt/shape/sphere.hh"

#include <iostream>

// TODO: clean up CMakeLists.txt
// TODO: meer tests
// TODO: static constructors?
// TODO: fma for vectors?

__managed__ rt::intersection i;

__global__ void kernel(rt::sphere sphere, rt::ray3f ray) {
	intersect(sphere, ray, i);
}

int main() {
	rt::vec3f origin = rt::vector<rt::float_t>(1, 1, 1);
	rt::vec3f direction = normalize(-origin);
	rt::ray3f ray(origin, direction, 0);
	rt::sphere sphere(1);
	kernel<<<1, 1>>>(sphere, ray);
	cudaDeviceSynchronize();
	std::cout << i << std::endl;
}
