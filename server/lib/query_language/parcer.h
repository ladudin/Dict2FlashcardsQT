#pragma once
#include "classes.h"

class parser {
 public:
    parser(std::vector<token> &t);
    std::unique_ptr<expr> parse();

 private:
    std::vector<token>       tokens;
    std::vector<std::string> read_json_elem();
    int                      current = 0;
    bool                     is_at_end();
    token                    peek();
    token                    previous();
    token                    advance();
    bool                     check(token_type type);
    bool                     match(std::vector<token_type> types);
    token                    consume(token_type type, std::string message);
    std::unique_ptr<expr>    primary();
    std::unique_ptr<expr>    finish_call(expr *callee);
    std::unique_ptr<expr>    func_in_class();
    std::unique_ptr<expr>    unar();
    std::unique_ptr<expr>    multiplication();
    std::unique_ptr<expr>    addition();
    std::unique_ptr<expr>    comparison();
    std::unique_ptr<expr>    equality();
    std::unique_ptr<expr>    _and();
    std::unique_ptr<expr>    _or();
    std::unique_ptr<expr>    assignment();
    std::unique_ptr<expr>    expression();
    std::unique_ptr<expr>    function(std::string kind);
};
