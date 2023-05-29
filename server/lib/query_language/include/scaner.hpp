#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "exception.hpp"


enum token_type {
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACKET,
    RIGHT_BRACKET,
    COMMA,
    DOT,
    MINUS,
    PLUS,
    SEMICOLON,
    SLASH,
    STAR,
    QMARK,
    COLON,

    BANG,
    BANG_EQUAL,
    EQUAL,
    EQUAL_EQUAL,
    GREATER,
    GREATER_EQUAL,
    LESS,
    LESS_EQUAL,

    // Literals
    IDENTIFIER,
    STRING,
    NUMBER,
    JSON,
    BOOL,
    EMPTY,
    DOUBLE,

    // logic
    NOT,
    AND,
    OR,
    ANY,
    ALL,
    FALSE,
    TRUE,

    // func
    IN,
    LEN,
    SPLIT,
    LOWER,
    UPPER,
    REDUCE,
    EOTF,
    NUL
};

using tt = token_type;

struct token {
    token_type  type;
    std::string lexeme;
    std::string literal;

    token() : type(tt::NUL), lexeme(""){};
    token(const token_type   type_,
          const std::string &lexeme_  = "",
          const std::string &literal_ = "")
        : type(type_), lexeme(lexeme_), literal(literal_){};
};

class scanner {
public:

    scanner(const std::string &s);
    std::vector<token> scan_tokens();

private:
    std::string                       source;
    std::vector<token>                tokens;
    std::map<std::string, token_type> keywords;
    int                               start   = 0;
    int                               current = 0;

    void                              init_keywords();
    bool                              has_next(size_t i = 0);
    bool                              is_digit(const std::string &c);
    void                              add_token(token_type type);
    void        add_token(token_type type, const std::string &literal);
    char        advance();
    bool        match(const std::string &expected);
    std::string peek();
    std::string peek_next();
    void        number();
    void        read_json_level();
    void        read_json_keyword();
    void        string();
    void        scan_token();
};
