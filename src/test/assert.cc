#include "rt/test/assert.hh"

#include <sstream>

namespace rt {
	static std::string make_reason(const std::string& expr, const std::string& file, long line) {
		return (std::stringstream() << file << ":" << line << ": " << expr).str();
	}

	assert_error::assert_error(std::string expr, std::string file, long line) : logic_error(make_reason(expr, file, line)) {
		this->expr = std::make_shared<std::string>(std::move(expr));
		this->file = std::make_shared<std::string>(std::move(file));
		this->line = line;
	}

	assert_error::assert_error(const assert_error& arg) noexcept : logic_error(arg) {
		expr = arg.expr;
		file = arg.file;
		line = arg.line;
	}
}
