#ifndef DIAGNOSTICS_HPP
#define DIAGNOSTICS_HPP

#include <stdexcept>
#include <sstream>

#ifdef __GNUG__
#define FUNCTION_NAME __PRETTY_FUNCTION__
#else
#define FUNCTION_NAME __FUNCTION__
#endif

#define ASSERT(condition) { \
	if (!(condition)) { \
		std::ostringstream os; \
		os << "Assertion failed: " << #condition << ", in function "; \
		os << "\'" << FUNCTION_NAME << "\' at "; \
		os << __FILE__ << ':' << __LINE__ ; \
		throw std::logic_error(os.str()); \
	} \
}

#define ASSERT2(condition, message) { \
	if (!(condition)) { \
		std::ostringstream os; \
		os << "Assertion failed: " << #condition << ", in function "; \
		os << "\'" << FUNCTION_NAME << "\' at "; \
		os << __FILE__ << ':' << __LINE__ ; \
		os << "\n" << message ; \
		throw std::logic_error(os.str()); \
	} \
}

#define RT_CHECK(condition, message) { \
	if (!(condition)) { \
		std::ostringstream os; \
		os << message; \
		throw std::runtime_error(os.str()); \
	} \
}

#endif
