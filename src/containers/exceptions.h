#ifndef DICT2FLASHCARDSQT_SRC_CONTAINERS_EXCEPTIONS_H
#define DICT2FLASHCARDSQT_SRC_CONTAINERS_EXCEPTIONS_H

#include <stdexcept>

class InvalidResponseFormatException : public std::runtime_error {
 public:
    InvalidResponseFormatException(const char* message) : std::runtime_error(message) {}
};

class ServerErrorResponseException : public std::runtime_error {
 public:
    ServerErrorResponseException(const char* message) : std::runtime_error(message) {}
};

#endif  // DICT2FLASHCARDSQT_SRC_CONTAINERS_EXCEPTIONS_H
