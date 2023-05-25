#include "parcer.hpp"

parser::parser(std::vector<token> &t) : tokens(t){};

bool parser::is_at_end() {
    return tokens[current].type == token_type::EOTF;
}

token parser::peek() {
    return tokens[current];
}

token parser::previous() {
    return tokens[current - 1];
}

token parser::advance() {
    if (!is_at_end())
        current++;
    return previous();
}

bool parser::check(token_type type) {
    return !is_at_end() && peek().type == type;
}

bool parser::match(std::vector<token_type> types) {
    for (auto &type : types) {
        if (check(type)) {
            advance();
            return true;
        }
    }
    return false;
}


std::unique_ptr<expr> parser::primary() {
   token_type type = peek().type;
    advance();

    switch (type) {
        case tt::FALSE:
            return std::make_unique<literal>(false);
        case tt::TRUE:
            return std::make_unique<literal>(true);
        case tt::NUMBER:
            return std::make_unique<literal>(std::stod(previous().literal));
        case tt::STRING:
            return std::make_unique<literal>(previous().literal);
        case tt::LEFT_PAREN: {
            std::unique_ptr<expr> expr = expression();
            if (match({tt::RIGHT_PAREN})) {
                return std::make_unique<grouping>(std::move(expr));
            } else {
                throw ComponentException("Missing closing parenthesis for grouping.");
            }
        }
        case tt::IDENTIFIER: {
            std::vector<std::string> json_fields = read_json_elem();
            if (!json_fields.empty()) {
                return std::make_unique<literal>(json_fields);
            } else {
                 throw ComponentException("Invalid JSON element.");
            }
        }
        default:
            throw ComponentException("Unexpected token encountered.");
    }
}

std::vector<std::string> parser::read_json_elem() {
    std::vector<std::string> json_fields;
    json_fields.push_back(previous().lexeme);
    while (match({{tt::LEFT_BRACKET}})) {
        if (match({tt::IDENTIFIER})) {
            json_fields.push_back(previous().lexeme);
        } else {
            return std::vector<std::string>();
        }

        if (!match({tt::RIGHT_BRACKET})) {
            throw ComponentException("Missing closing parenthesis for JSON.");
        }
    }
    return json_fields;
}

std::unique_ptr<expr> parser::func_in_class() {
    std::unique_ptr<expr> left = primary();
    if (match({tt::IN})){
        /*if(!match({tt::LEFT_PAREN})){
            throw ComponentException("Missing open parenthesis for function call.");
        }*/

        std::unique_ptr<expr> right = primary();
        
        /*if (!match({tt::RIGHT_PAREN})) {
            throw ComponentException("Missing closing parenthesis for function call.");
        }*/

        return std::make_unique<func_in>(std::move(left),
                                        std::move(right));
    }
    return left;
}

std::unique_ptr<expr> parser::unar() {
    if (match({tt::NOT,
               tt::MINUS,
               tt::LEN,
               tt::SPLIT,
               tt::UPPER,
               tt::LOWER,
               tt::REDUCE})) {
        token                 oper  = previous();
        std::unique_ptr<expr> right = unar();
        return std::make_unique<unary>(std::move(right), oper);
    }
    return func_in_class();
}

std::unique_ptr<expr> parser::multiplication() {
    std::unique_ptr<expr> left = unar();
    while (match({tt::SLASH, tt::STAR})) {
        token                 oper  = previous();
        std::unique_ptr<expr> right = unar();
        left                  = std::make_unique<binary>(
            std::move(left), oper, std::move(right));
    }
    return left;
}

std::unique_ptr<expr> parser::addition() {
    std::unique_ptr<expr> left = multiplication();
    while (match({tt::MINUS, tt::PLUS})) {
        token                 oper  = previous();
        std::unique_ptr<expr> right = multiplication();
        left                  = std::make_unique<binary>(
            std::move(left), oper, std::move(right));
    }
    return left;
}

std::unique_ptr<expr> parser::comparison() {
    std::unique_ptr<expr> left = addition();
    while (match({tt::LESS, tt::LESS_EQUAL, tt::GREATER, tt::GREATER_EQUAL})) {
        token                 oper  = previous();
        std::unique_ptr<expr> right = addition();
        left                  = std::make_unique<binary>(
            std::move(left), oper, std::move(right));
    }
    return left;
}

std::unique_ptr<expr> parser::equality() {
    std::unique_ptr<expr> left = comparison();
    while (match({tt::BANG_EQUAL, tt::EQUAL_EQUAL})) {
        token                 oper  = previous();
        std::unique_ptr<expr> right = comparison();
        left                  = std::make_unique<binary>(
            std::move(left), oper, std::move(right));
    }
    return left;
}

std::unique_ptr<expr> parser::and_expr() {
    std::unique_ptr<expr> left = equality();

    while (match({tt::AND})) {
        token                 oper  = previous();
        std::unique_ptr<expr> right = equality();
        left                        = std::make_unique<logical_expr>(
            std::move(left), oper, std::move(right));
    }
    return left;
}

std::unique_ptr<expr> parser::or_expr() {
    std::unique_ptr<expr> left = and_expr();
    
    while (match({tt::OR})) {
        token                 oper  = previous();
        std::unique_ptr<expr> right = and_expr();
        left                        = std::make_unique<logical_expr>(
            std::move(left), oper, std::move(right));
    }
    return left;
}

std::unique_ptr<expr> parser::expression() {
    return or_expr();
}

std::unique_ptr<expr> parser::parse() {

    return expression();
}
