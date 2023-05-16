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


expr* parser::primary(){
    if (match({tt::FALSE}))
        return new literal("false");
    if (match({tt::TRUE}))
        return new literal("true");
    if (match({tt::NUMBER}))
        return new literal(std::stod(previous().literal));
    if (match({tt::STRING}))
        return new literal(previous().literal);
    if (match({tt::LEFT_PAREN})){
        expr* expr = expression();
        // обработать, что нет правой скобки
        return new grouping(expr);
    }
    /*if (match({tt::IDENTIFIER}))
        return new var_expr(previous());*/
    return nullptr;
}


/*expr* parser::finish_call(expr* callee){
    std::vector<expr*> arguments;
    if (!check(tt::RIGHT_PAREN)){
        do{
            arguments.emplace_back(expression());
        } while(match({tt::COMMA}));
    }
    token r_paren = consume(tt::RIGHT_PAREN, "Expect ')' after arguments.");
    return new call_expr(callee, r_paren, arguments);
}*/

/*expr* parser::call(){
    expr* call = primary();
    while (true){
        if (match({tt::LEFT_PAREN}))
            call = finish_call(call);
        else
            break;
    };
    return call;
}*/

expr* parser::unar(){
    if(match({tt::BANG, tt::MINUS})){
        token oper = previous();
        expr* right = unar();
        return new unary(right, oper);
    }
    return primary();
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
    return equality();
}



/*expr* parser::function(std::string kind){
    token name = consume(FUN, std::string("Expect " + kind + " name."));
    consume(tt::LEFT_PAREN, std::string("Expected '(' after" + kind + " declaration."));
    std::vector<token> parameters;

   
    consume(tt::RIGHT_PAREN, std::string("Expected ')' after " + kind + " declaration"));
    return new fun_stmt(name, parameters);
}*/



expr*  parser::parse(){

    return equality();
  }

