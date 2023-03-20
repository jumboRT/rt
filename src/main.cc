#include "rt/math/vector.hh"
#include "rt/test/debug.hh"

#include <iostream>

int main() {
	// TODO: testing framework

	rt::vector<float, 3> i = normalize(rt::vector<float, 3>(1));
	rt::vector<float, 3> j, k;

	coordinate_system(i, j, k);

	std::cout << i << std::endl;
	std::cout << j << std::endl;
	std::cout << k << std::endl;
}
