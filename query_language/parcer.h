#pragma once
#include "classes.h"

class parser {
    public:
    parser(std::vector<token>& t);
    expr* parse();
    
    private:
    std::vector<token> tokens;
    std::vector<std::string> read_json_elem();
    int current = 0;
    bool is_at_end();
    token peek();
    token previous();
    token advance();
    bool check(token_type type);
    bool match(std::vector<token_type> types);
    token consume(token_type type, std::string message);
    expr* primary();
    expr* finish_call(expr* callee);
    expr* call();
    expr* unar();
    expr* multiplication();
    expr* addition();
    expr* comparison();
    expr* equality();
    expr* _and();
    expr*_or();
    expr* assignment();
    expr* expression();
    expr* function(std::string kind);
};

