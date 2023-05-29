#include "exception.hpp"
#include <cctype>

ComponentException::ComponentException(const char* message) : message_(message) {}

const char* ComponentException::what() const throw() {
    return message_.c_str();
}