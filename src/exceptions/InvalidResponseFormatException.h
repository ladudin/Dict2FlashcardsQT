#ifndef DICT2FLASHCARDSQT_SRC_EXCEPTIONS_INVALIDRESPONSEFORMATEXCEPTION_H
#define DICT2FLASHCARDSQT_SRC_EXCEPTIONS_INVALIDRESPONSEFORMATEXCEPTION_H

#include <stdexcept>

class InvalidResponseFormatException : public std::runtime_error {
 public:
    const char* what() const throw() {
        return "Invalid response format";
    }
};


#endif  // DICT2FLASHCARDSQT_SRC_EXCEPTIONS_INVALIDRESPONSEFORMATEXCEPTION_H
