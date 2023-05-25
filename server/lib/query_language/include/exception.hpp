#pragma once
#include "include_libs.hpp"

// Базовый класс исключений для компонентов (сканер, парсер, интерпретатор)
class ComponentException : public std::exception {
public:
    explicit ComponentException(const char* message);

    const char* what() const throw();

private:
   std::string message_;
};