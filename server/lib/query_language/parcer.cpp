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
expr* parser::primary(){
    if (match({tt::FALSE}))
        return new literal(false);
    if (match({tt::TRUE}))
        return new literal(true);
    if (match({tt::NUMBER})){
        return new literal(std::stod(previous().literal));
    }
    if (match({tt::STRING}))
        return new literal(previous().literal);
    if (match({tt::LEFT_PAREN})){
        expr* expr = expression();
        // обработать, что нет правой скобки
        return new grouping(expr);
    }
    if (match({tt::IDENTIFIER})){
        std::vector<std::string> json_fields = read_json_elem();
        if(!json_fields.empty()){
            return new literal(json_fields);
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



expr* parser::func_in_class(){
    expr* left = primary();
    if(match({tt::IN})){
        if(match({tt::LEFT_PAREN})){
            expr* right = primary();
            if(match({tt::RIGHT_PAREN})){
                return new func_in(left, right);
            }
        }
    }
    return primary();
}


expr* parser::unar(){
    if(match({tt::BANG, tt::MINUS})){
        token oper = previous();
        expr* right = unar();
        return new unary(right, oper);
    }
    return func_in_class();
}

expr* parser::multiplication(){
    expr* expression = unar();
    while(match({tt::SLASH, tt::STAR})){
        token oper = previous();
        expr* right = unar();
        expression = new binary(expression, oper, right);
    }
    return expression;
}

expr* parser::addition(){
    expr* expression = multiplication();
    while(match({tt::MINUS, tt::PLUS})){
        std::cout<<"операция + -"<<std::endl;
        token oper = previous();
        expr* right = multiplication();
        expression = new binary(expression, oper, right);
    }
    return expression;
}

expr* parser::comparison(){
    expr* expression = addition();
    while(match({tt::LESS, tt::LESS_EQUAL, tt::GREATER, tt::GREATER_EQUAL})){
        token oper = previous();
        expr* right = addition();
        expression = new binary(expression, oper, right);
    }
    return expression;
}

expr* parser::equality(){
    expr* expression = comparison();
    while(match({tt::BANG_EQUAL,tt::EQUAL_EQUAL})){
        token oper = previous();
        expr* right = comparison();
        expression = new binary(expression, oper, right);
    }
    return expression;
}

expr* parser::_and(){
    expr* left = equality();

    while(match({tt::AND})){
        token oper = previous();
        expr* right = equality();
        left = new logical_expr(left, oper, right);
    }
    return left;
}

expr* parser::_or(){
    expr* left = _and();
    literal* l = reinterpret_cast<literal*>(left);
    while(match({tt::OR})){
        token oper = previous();
        expr* right = _and();
        left = new logical_expr(left, oper, right);
    } 
    return left;
}


expr* parser::expression(){
    return _or();
}



/*expr* parser::function(std::string kind){
    token name = consume(FUN, std::string("Expect " + kind + " name."));
    consume(tt::LEFT_PAREN, std::string("Expected '(' after" + kind + " declaration."));
    std::vector<token> parameters;

   
    consume(tt::RIGHT_PAREN, std::string("Expected ')' after " + kind + " declaration"));
    return new fun_stmt(name, parameters);
}*/



expr*  parser::parse(){

    return expression();
  }

