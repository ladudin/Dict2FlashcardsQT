#ifndef DICT2FLASHCARDSQT_SRC_EXCEPTIONS_SERVERERROREXCEPTION_H
#define DICT2FLASHCARDSQT_SRC_EXCEPTIONS_SERVERERROREXCEPTION_H

#include <stdexcept>

class ServerErrorException : public std::exception {
 private:
    std::string m_errorMessage;
 public:
    ServerErrorException(const std::string& errorMessage)
        : m_errorMessage(errorMessage) {}

    const char* what() const throw() {
        return m_errorMessage.c_str();
    }
};


#endif  // DICT2FLASHCARDSQT_SRC_EXCEPTIONS_SERVERERROREXCEPTION_H
