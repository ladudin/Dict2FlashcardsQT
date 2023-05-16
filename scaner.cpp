#include "scaner.h"

void scanner::init_keywords(){
    keywords["in"] = tt::IN;
    keywords["len"] = tt::LEN;
    keywords["split"] = tt::SPLIT;
    keywords["lower"] = tt::LOWER;
    keywords["upper"] = tt::UPPER;
    keywords["all"] = tt::ALL;
    keywords["any"] = tt::ANY;
    keywords["and"] = tt::AND;
    keywords["or"] = tt::OR;
    keywords["not"] = tt::NOT;

}

bool scanner::has_next(size_t i){
    return current + i < source.size();
}

bool scanner::is_digit(const std::string& c){
    return std::isdigit(c[0]);
}

void scanner::add_token(token_type type){
    add_token(type, "");
}

void scanner::add_token(token_type type, const std::string& literal){
    std::string text = source.substr(start, current - start);
    tokens.emplace_back(type, text, literal);
}

char scanner::advance(){
    current++;
    return source[current - 1];
}

bool scanner::match(const std::string& expected){
    if (!has_next(expected.size())) return false;
    if (source.substr(current, current + expected.size())  != expected) return false;
    current += expected.size();
    return true;
}

std::string scanner::peek(){
    if (!has_next()) return "";
    return source.substr(current, 1);
}

std::string scanner::peek_next(){
    if (current + 1 >= source.size()) return std::string("\0");
    return source.substr(current+1, 1);
}

void scanner::number(){

    while (is_digit(peek())){
        advance();
    } 

    if (peek()[0] == '.' && is_digit(peek_next())){
        advance();
        while (is_digit(peek())){
            advance();
        } 
    }

    add_token(tt::NUMBER, source.substr(start, current - start));
}

void scanner::identifier(){
    while(isalnum(peek()[0])){
        advance();
    } 
    std::string text = source.substr(start, current - start);
    auto type = keywords.find(text);
    type == keywords.end() ? add_token(tt::IDENTIFIER) : add_token(type->second);
}

void scanner::string(){

    while (peek()[0] != '"' && has_next()){
        advance();
    }

    //Unterminated string
    if (!has_next()){
        // тут вставить логгер
        return;
    }

    advance();

    std::string value = source.substr(start + 1, current - start - 2);
    add_token(tt::STRING, value);
}

void scanner::scan_token(){
    char c = advance();
    switch(c){
        case '(': add_token(tt::LEFT_PAREN); break;
        case ')': add_token(tt::RIGHT_PAREN); break;
        case '[': add_token(tt::LEFT_BRACKET); break;
        case ']': add_token(tt::RIGHT_BRACKET); break;
        case ',': add_token(tt::COMMA); break;
        case '.': add_token(tt::DOT); break;
        case '-': add_token(tt::MINUS); break;
        case '+': add_token(tt::PLUS); break;
        case ';': add_token(tt::SEMICOLON); break;
        case '*': add_token(tt::STAR); break;
        case '?': add_token(tt::QMARK); break;
        case ':': add_token(tt::COLON); break;
        case '!': add_token(match(std::string(1, '=')) ? tt::BANG_EQUAL : tt::BANG); break;
        case '=': add_token(match(std::string("=")) ? tt::EQUAL_EQUAL : tt::EQUAL); break;
        case '<': add_token(match(std::string("=")) ? tt::LESS_EQUAL : tt::LESS); break;
        case '>': add_token(match(std::string("=")) ? tt::GREATER_EQUAL : tt::GREATER); break;
//        case '$': if(match(std::string("ANY"))) add_token(tt::ANY); break;
        case '$': 
        case ' ':
        case '\r':
        case '\t': break;
        case '"': string(); break;

        default:
            if (is_digit(std::string(1, c)))
                number();
            else if (isalpha(c))
                identifier();
            else
                std::cout << "Unexpected character "; break;

    }
}

scanner::scanner (const std::string& source_) : source(source_){
    init_keywords();
}

std::vector<token> scanner::scan_tokens(){
    while(has_next()){
        start = current;
        scan_token();
    }
    tokens.emplace_back(EOTF, "","");
    return tokens;
}




struct Card {
    std::string word;
    std::vector<std::string> special;
    std::string definition;
    std::vector<std::string> examples;
    std::vector<std::string> image_links;
    std::vector<std::string> audio_links;
    json tags; 
    json other; 
};

json card_to_json(Card card){
    json jsonCard;
    jsonCard["word"] = card.word;
    jsonCard["special"] = card.special;
    jsonCard["definition"] = card.definition;
    jsonCard["examples"] = card.examples;
    jsonCard["image_links"] = card.image_links;
    jsonCard["audio_links"] = card.audio_links;
    jsonCard["tags"] = card.tags;
    jsonCard["other"] = card.other;
    return jsonCard;
}

