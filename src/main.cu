#include "rt/test/debug.hh"
#include "rt/shape/sphere.hh"

#include <iostream>

// TODO: clean up CMakeLists.txt
// TODO: move rt::swap to a different header
// TODO: rt::span const "begin" en "end"

__managed__ rt::intersection i;

__global__ void kernel(rt::sphere sphere, rt::ray3f ray) {
	sphere.intersect(ray, i);
}

int main() {
	rt::vec3f origin = rt::vector<rt::real>(1, 1, 1);
	rt::vec3f direction = rt::normalize(-origin);
	rt::ray3f ray(origin, direction, 0);
	rt::sphere sphere(1);
	kernel<<<1, 1>>>(sphere, ray);
	cudaDeviceSynchronize();
	std::cout << i << std::endl;
}
