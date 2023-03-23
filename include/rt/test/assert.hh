#ifndef RT_TEST_ASSERT_HH
#define RT_TEST_ASSERT_HH

#include <stdexcept>
#include <memory>

#define RT_ASSERT(expr) ((expr) ? 0 : throw ::rt::assert_error(#expr, __FILE__, __LINE__))

namespace rt {
	class assert_error : public std::logic_error {
	private:
		std::shared_ptr<std::string> expr;
		std::shared_ptr<std::string> file;
		long line;
	public:
		assert_error(std::string expr, std::string file, long line);
		assert_error(const assert_error& arg) noexcept;
	};
}

#endif
