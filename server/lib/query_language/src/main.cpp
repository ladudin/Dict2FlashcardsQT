#include "interpreter.hpp"

using nlohmann::json;

struct Card {
    std::string              word;
    std::vector<std::string> special;
    std::string              definition;
    std::vector<std::string> examples;
    std::vector<std::string> image_links;
    std::vector<std::string> audio_links;
    json                     tags;
    json                     other;
};

json card_to_json(Card card) {
    json jsonCard;
    jsonCard["word"]        = card.word;
    jsonCard["special"]     = card.special;
    jsonCard["definition"]  = card.definition;
    jsonCard["examples"]    = card.examples;
    jsonCard["image_links"] = card.image_links;
    jsonCard["audio_links"] = card.audio_links;
    jsonCard["tags"]        = card.tags;
    jsonCard["other"]       = card.other;
    return jsonCard;
}

int main() {
    Card card;
    card.word        = "example";
    card.special     = {"special1", "special2"};
    card.definition  = "This is an example";
    card.examples    = {"Example 1", "Example 2"};
    card.image_links = {"image1.jpg", "image2.jpg"};
    card.audio_links = {"audio1.mp3", "audio2.mp3"};
    card.tags        = {
        {"tag1", {"value1", "moscow"}},
        {"level", {"A1"}}
    };
    card.other = {
        {"key1", "value1 слово pnfvinv 345"},
        {"key2", "value2"                       },
        {"key3", "value3"                       }
    };

    json               jsonCard = card_to_json(card);

    try {
    scanner scan("\"A1\" in tags[level]");
    //scanner scan("\"A1ee\"");
    std::vector<token> tokens = scan.scan_tokens();
    for (int i = 0; i < tokens.size(); ++i){
        std::cout<< tokens[i].lexeme <<std::endl;
    }
    parser p(tokens);
    std::unique_ptr<Expr> exp = p.parse();
    interpreter inter;
    Value val = inter.interpret(exp.get(), jsonCard);

    if (std::holds_alternative<double>(val)) {
        std::cout << "Значение: " << std::get<double>(val) << std::endl;
    } else if (std::holds_alternative<nlohmann::json>(val)) {
        std::cout << "Это JSON" << std::endl;
        std::cout << "Значение: " << std::get<nlohmann::json>(val).dump() << std::endl;
    } else if (std::holds_alternative<bool>(val)) {
        std::cout << "Это логическое значение" << std::endl;
        std::cout << "Значение: " << std::get<bool>(val) << std::endl;
    } else if (std::holds_alternative<std::string>(val)) {
        std::cout << "Это строка" << std::endl;
        std::cout << "Значение: " << std::get<std::string>(val) << std::endl;
    } else if (std::holds_alternative<std::monostate>(val)){
        std::cout << "Пусто" << std::endl;
    } else {
         std::cout << ":(" << std::endl;
    }
} catch (const ComponentException& e) {
    std::cerr << "Ошибка: " << e.what() << std::endl;
} 
    return 0;
}
