#ifndef RT_TEST_TESTER_HH
#define RT_TEST_TESTER_HH

#include <unordered_map>
#include <functional>
#include <string>

namespace rt {
	class tester {
	private:
		std::unordered_multimap<std::string, std::function<void()>> tests;
	public:
		void insert(std::string name, std::function<void()> test);
		void run(const std::string& name) const;
		void run() const;
	};
}

#endif
