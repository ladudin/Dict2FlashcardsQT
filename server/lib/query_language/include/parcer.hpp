#pragma once
#include "classes.hpp"

class parser {
 public:
    parser(std::vector<token> &t);
    std::unique_ptr<expr> parse();

 private:
    std::vector<token>       tokens;
    std::vector<std::string> read_json_elem();
    int                      current = 0;
    bool                     is_at_end();
    bool                     check(token_type type);
    bool                     match(std::vector<token_type> types);
    token                    peek();
    token                    previous();
    token                    advance();
    std::unique_ptr<expr>    primary();
    std::unique_ptr<expr>    func_in_class();
    std::unique_ptr<expr>    unar();
    std::unique_ptr<expr>    multiplication();
    std::unique_ptr<expr>    addition();
    std::unique_ptr<expr>    comparison();
    std::unique_ptr<expr>    equality();
    std::unique_ptr<expr>    and_expr();
    std::unique_ptr<expr>    or_expr();
    std::unique_ptr<expr>    expression();
};
