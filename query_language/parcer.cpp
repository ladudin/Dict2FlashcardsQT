#include "parcer.h"

parser::parser(std::vector<token>& t) : tokens(t) {};

bool parser::is_at_end(){
    return tokens[current].type == token_type::EOTF;
}

token parser::peek(){
    return tokens[current];
}

token parser::previous(){
    return tokens[current - 1];
}

token parser::advance(){
    if (!is_at_end())
        current++;
    return previous();
}

bool parser::check(token_type type){
    return !is_at_end() && peek().type == type;
}

bool parser::match(std::vector<token_type> types){
    for (auto& type : types){
        if (check(type)){
            advance();
            return true;
        }
    }
    return false;
}

// потом заманить ifы
std::unique_ptr<expr> parser::primary(){
    if (match({tt::FALSE}))
        return std::make_unique<literal>(false);
    if (match({tt::TRUE}))
        return std::make_unique<literal>(true);
    if (match({tt::NUMBER})){
        return std::make_unique<literal>(std::stod(previous().literal));
    }
    if (match({tt::STRING}))
        return std::make_unique<literal>(previous().literal);
    if (match({tt::LEFT_PAREN})){
        std::unique_ptr<expr> expr = expression();
        // обработать, что нет правой скобки
        return std::make_unique<grouping>(std::move(expr));
    }
    if (match({tt::IDENTIFIER})){
        std::vector<std::string> json_fields = read_json_elem();
        if(!json_fields.empty()){
            return std::make_unique<literal>(json_fields);
        } // обработать ошибку
    }
    return nullptr;
}

std::vector<std::string> parser::read_json_elem(){
    std::vector<std::string> json_fields;
    json_fields.push_back(previous().lexeme);
    while(match({{tt::LEFT_BRACKET}})){
        if (match({tt::IDENTIFIER})){
            json_fields.push_back(previous().lexeme);
        }else{
            return std::vector<std::string>();
        }

        if (!match({tt::RIGHT_BRACKET})){
            return std::vector<std::string>();
        }
    }
    return json_fields;
}



std::unique_ptr<expr> parser::func_in_class(){
    std::unique_ptr<expr>  left = primary();
    if(match({tt::IN})){
        if(match({tt::LEFT_PAREN})){
            std::unique_ptr<expr>  right = primary();
            if(match({tt::RIGHT_PAREN})){
                return std::make_unique<func_in>(std::move(left), std::move(right));
            }
        }
    }
    return left;
}


std::unique_ptr<expr> parser::unar(){
    if(match({tt::BANG, tt::MINUS})){
        token oper = previous();
        std::unique_ptr<expr> right = unar();
        return std::make_unique<unary>(std::move(right),oper);
    }
    return func_in_class();
}

std::unique_ptr<expr> parser::multiplication(){
    std::unique_ptr<expr> expression = unar();
    while(match({tt::SLASH, tt::STAR})){
        token oper = previous();
        std::unique_ptr<expr> right = unar();
        expression = std::make_unique<binary>(std::move(expression), oper, std::move(right));
    }
    return expression;
}

std::unique_ptr<expr> parser::addition(){
    std::unique_ptr<expr> expression = multiplication();
    while(match({tt::MINUS, tt::PLUS})){
        std::cout<<"операция + -"<<std::endl;
        token oper = previous();
        std::unique_ptr<expr> right = multiplication();
        expression = std::make_unique<binary>(std::move(expression), oper, std::move(right));
    }
    return expression;
}

std::unique_ptr<expr> parser::comparison(){
     std::unique_ptr<expr> expression = addition();
    while(match({tt::LESS, tt::LESS_EQUAL, tt::GREATER, tt::GREATER_EQUAL})){
        token oper = previous();
         std::unique_ptr<expr> right = addition();
        expression = std::make_unique<binary>(std::move(expression), oper, std::move(right));
    }
    return expression;
}

std::unique_ptr<expr> parser::equality(){
    std::unique_ptr<expr> expression = comparison();
    while(match({tt::BANG_EQUAL,tt::EQUAL_EQUAL})){
        token oper = previous();
        std::unique_ptr<expr> right = comparison();
        expression = std::make_unique<binary>(std::move(expression), oper, std::move(right));
    }
    return expression;
}

std::unique_ptr<expr>  parser::_and(){
    std::unique_ptr<expr>  left = equality();

    while(match({tt::AND})){
        token oper = previous();
        std::unique_ptr<expr>  right = equality();
         left = std::make_unique<logical_expr>(std::move(left), oper, std::move(right));
    }
    return left;
}

std::unique_ptr<expr> parser::_or(){
    std::unique_ptr<expr> left = _and();
//    literal* l = reinterpret_cast<literal*>(left);
    while(match({tt::OR})){
        token oper = previous();
        std::unique_ptr<expr> right = _and();
        left = std::make_unique<logical_expr>(std::move(left), oper, std::move(right));
    } 
    return left;
}


std::unique_ptr<expr> parser::expression(){
    return _or();
}

std::unique_ptr<expr>  parser::parse(){

    return expression();
  }





