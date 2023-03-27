#include "rt/test/debug.hh"
#include "rt/shape/sphere.hh"

#include <iostream>
#include <random>
#include <tuple>

// TODO: clean up CMakeLists.txt
// TODO: meer tests

__managed__ rt::intersection i;

__global__ void kernel(rt::sphere sphere, rt::ray3f ray) {
	intersect(sphere, ray, i);
}

int main() {
	rt::vec3f origin = rt::vec3f(1, 1, 1);
	rt::vec3f direction = normalize(-origin);
	rt::ray3f ray(origin, direction, 0);
	rt::sphere sphere(1);
	kernel<<<1, 1>>>(sphere, ray);
	cudaDeviceSynchronize();
	std::cout << i << std::endl;
}
