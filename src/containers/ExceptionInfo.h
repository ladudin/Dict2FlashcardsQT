#ifndef DICT2FLASHCARDSQT_SRC_CONTAINERS_EXCEPTIONINFO_H
#define DICT2FLASHCARDSQT_SRC_CONTAINERS_EXCEPTIONINFO_H

#include <string>
#include <variant>

struct ExceptionInfo {
    std::string info;
};

template <typename T>
using Result = std::variant<T, ExceptionInfo>;

#endif  // DICT2FLASHCARDSQT_SRC_CONTAINERS_EXCEPTIONINFO_H
