#include "exception.hpp"


ComponentException::ComponentException(const char* message) : message_(message) {}

const char* ComponentException::what() const throw() {
    return message_.c_str();
}