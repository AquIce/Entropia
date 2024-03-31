#ifndef __AQUICE_UNIT_ASSERT_H__
#define __AQUICE_UNIT_ASSERT_H__

#include <iostream>
#include <string>

int passed = 0;
int failed = 0;

int indent = 0;

std::string prefix = "[AquIce>Unit>Assert]";

std::string red = "\033[0;31m";
std::string green = "\033[0;32m";
std::string reset = "\033[0m";

#define ASSERT_BLOCK(name, code) std::cout << std::string(indent, '\t') << prefix << " Running " << name << " Tests" << reset << std::endl; \
indent++; \
code \
std::cout << "\n"; \
indent--;

#define ASSERT_EQUAL(name, a, b) if(a != b) { \
	std::cerr << std::string(indent, '\t') << red << prefix << reset << " Test \"" << name << "\" failed: " << #a << "(" << a << ") != " << #b << "(" << b << ")" << reset << std::endl; \
	failed++; \
} else { \
	std::cout << std::string(indent, '\t') << green << prefix << reset << " Test \"" << name << "\" passed" << reset << std::endl; \
	passed++; \
}

#define ASSERT_NOT_EQUAL(name, a, b) if(a == b) { \
	std::cerr << std::string(indent, '\t') << red << prefix << reset << " Test \"" << name << "\" failed: " << #a << "(" << a << ") == " << #b << "(" << b << ")" << reset << std::endl; \
	failed++; \
} else { \
	std::cout << std::string(indent, '\t') << green << prefix << reset << " Test \"" << name << "\" passed" << reset << std::endl; \
	passed++; \
}

#define ASSERT_TRUE(name, a) if(!a) { \
	std::cerr << std::string(indent, '\t') << red << prefix << reset << " Test \"" << name << "\" failed: " << #a << " is false" << reset << std::endl; \
	failed++; \
} else { \
	std::cout << std::string(indent, '\t') << green << prefix << reset << " Test \"" << name << "\" passed" << reset << std::endl; \
	passed++; \
}

#define ASSERT_FALSE(name, a) if(a) { \
	std::cerr << std::string(indent, '\t') << red << prefix << reset << " Test \"" << name << "\" failed: " << #a << " is true" << reset << std::endl; \
	failed++; \
} else { \
	std::cout << std::string(indent, '\t') << green << prefix << reset << " Test \"" << name << "\" passed" << reset << std::endl; \
	passed++; \
}

#define ASSERT_NULL(name, a) if(a != nullptr) { \
	std::cerr << std::string(indent, '\t') << red << prefix << reset << " Test \"" << name << "\" failed: " << #a << " is not null" << reset << std::endl; \
	failed++; \
} else { \
	std::cout << std::string(indent, '\t') << green << prefix << reset << " Test \"" << name << "\" passed" << reset << std::endl; \
	passed++; \
}

#define ASSERT_NOT_NULL(name, a) if(a == nullptr) { \
	std::cerr << std::string(indent, '\t') << red << prefix << reset << " Test \"" << name << "\" failed: " << #a << " is null" << reset << std::endl; \
	failed++; \
} else { \
	std::cout << std::string(indent, '\t') << green << prefix << reset << " Test \"" << name << "\" passed" << reset << std::endl; \
	passed++; \
}

#define ASSERT_THROW(name, a) try { \
	a; \
	std::cerr << std::string(indent, '\t') << red << prefix << reset << " Test \"" << name << "\" failed: " << #a << " did not throw an exception" << reset << std::endl; \
	failed++; \
} catch(...) { \
	std::cout << std::string(indent, '\t') << green << prefix << reset << " Test \"" << name << "\" passed" << reset << std::endl; \
	passed++; \
}

#define ASSERT_NO_THROW(name, a) try { \
	a; \
	std::cout << std::string(indent, '\t') << green << prefix << reset << " Test \"" << name << "\" passed" << reset << std::endl; \
	passed++; \
} catch(...) { \
	std::cerr << std::string(indent, '\t') << red << prefix << reset << " Test \"" << name << "\" failed: " << #a << " threw an exception" << reset << std::endl; \
	failed++; \
}

#define ASSERT_NEAR(name, a, b, epsilon) if(a < b - epsilon || a > b + epsilon) { \
	std::cerr << std::string(indent, '\t') << red << prefix << reset << " Test \"" << name << "\" failed: " << #a << "(" << a << ") is not near " << #b << "(" << b << ") with epsilon " << epsilon << reset << std::endl; \
	failed++; \
} else { \
	std::cout << std::string(indent, '\t') << green << prefix << reset << " Test \"" << name << "\" passed" << reset << std::endl; \
	passed++; \
}

#define ASSERT_NOT_NEAR(name, a, b, epsilon) if(a >= b - epsilon && a <= b + epsilon) { \
	std::cerr << std::string(indent, '\t') << red << prefix << reset << " Test \"" << name << "\" failed: " << #a << "(" << a << ") is near " << #b << "(" << b << ") with epsilon " << epsilon << reset << std::endl; \
	failed++; \
} else { \
	std::cout << std::string(indent, '\t') << green << prefix << reset << " Test \"" << name << "\" passed" << reset << std::endl; \
	passed++; \
}

#define ASSERT_LESS(name, a, b) if(a >= b) { \
	std::cerr << std::string(indent, '\t') << red << prefix << reset << " Test \"" << name << "\" failed: " << #a << "(" << a << ") is not less than " << #b << "(" << b << ")" << reset << std::endl; \
	failed++; \
} else { \
	std::cout << std::string(indent, '\t') << green << prefix << reset << " Test \"" << name << "\" passed" << reset << std::endl; \
	passed++; \
}

#define ASSERT_LESS_EQUAL(name, a, b) if(a > b) { \
	std::cerr << std::string(indent, '\t') << red << prefix << reset << " Test \"" << name << "\" failed: " << #a << "(" << a << ") is not less than or equal to " << #b << "(" << b << ")" << reset << std::endl; \
	failed++; \
} else { \
	std::cout << std::string(indent, '\t') << green << prefix << reset << " Test \"" << name << "\" passed" << reset << std::endl; \
	passed++; \
}

#define ASSERT_GREATER(name, a, b) if(a <= b) { \
	std::cerr << std::string(indent, '\t') << red << prefix << reset << " Test \"" << name << "\" failed: " << #a << "(" << a << ") is not greater than " << #b << "(" << b << ")" << reset << std::endl; \
	failed++; \
} else { \
	std::cout << std::string(indent, '\t') << green << prefix << reset << " Test \"" << name << "\" passed" << reset << std::endl; \
	passed++; \
}

#define ASSERT_GREATER_EQUAL(name, a, b) if(a < b) { \
	std::cerr << std::string(indent, '\t') << red << prefix << reset << " Test \"" << name << "\" failed: " << #a << "(" << a << ") is not greater than or equal to " << #b << "(" << b << ")" << reset << std::endl; \
	failed++; \
} else { \
	std::cout << std::string(indent, '\t') << green << prefix << reset << " Test \"" << name << "\" passed" << reset << std::endl; \
	passed++; \
}

#define ASSERT_TYPE(name, a, b) if(typeid(a) != typeid(b)) { \
	std::cerr << std::string(indent, '\t') << red << prefix << reset << " Test \"" << name << "\" failed: " << #a << " is not of type " << #b << reset << std::endl; \
	failed++; \
} else { \
	std::cout << std::string(indent, '\t') << green << prefix << reset << " Test \"" << name << "\" passed" << reset << std::endl; \
	passed++; \
}

void print_results() {
	std::cout << prefix << " " << green << passed << " (" << (float)passed / (float)(passed + failed) * 100 << "%) PASSED" << reset << ", " << red << failed << " (" << (float)failed / (float)(passed + failed) << "%) FAILED" << reset << ", " << reset << (passed + failed) << " TOTAL" << reset << std::endl;
}

#endif