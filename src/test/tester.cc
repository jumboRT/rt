#include "rt/test/tester.hh"
#include "rt/test/assert.hh"

namespace rt {
	void tester::insert(std::string name, std::function<void()> test) {
		tests.emplace(std::move(name), std::move(test));
	}

	void tester::run(const std::string& name) const {
		auto range = tests.equal_range(name);

		RT_ASSERT(range.first != range.second);

		for (auto it = range.first; it != range.second; it++) {
			it->second();
		}
	}

	void tester::run() const {
		for (const auto& test : tests) {
			test.second();
		}
	}
}
