#include "interpreter.h"



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



int main(){
    Card card;
    card.word = "example";
    card.special = { "special1", "special2" };
    card.definition = "This is an example";
    card.examples = { "Example 1", "Example 2" };
    card.image_links = { "image1.jpg", "image2.jpg" };
    card.audio_links = { "audio1.mp3", "audio2.mp3" };
    card.tags = { { "tag1", {"value1","moscow"} }, { "tag2", {"value2","stp"} }};
    card.other = { { "key1", "value1" }, { "key2", "value2" } };

    json jsonCard = card_to_json(card);
   
    /*std::string jsonString = jsonCard.dump();
    std::cout << jsonString << std::endl;*/

    /*scanner scan("(pos[$SELF][data][256]!");
    std::vector<token> vec= scan.scan_tokens();
    for(int i = 0; i < vec.size();++i){
        std::cout<<vec[i].lexeme<<std::endl;
        if (vec[i].type == tt::ANY){
            std::cout<<"ANYYYYYY"<<std::endl;
        }else if(vec[i].type == tt::IDENTIFIER){
            std::cout<<"indent"<<std::endl;
        }else if(vec[i].type == tt::NUMBER){
            std::cout<<"num"<<std::endl;
        }
    }*/
    scanner scan("\"example\" in(word) ");
    std::vector<token> tokens= scan.scan_tokens();
    /*for(int i = 0; i < tokens.size();++i){
        std::cout<<tokens[i].lexeme<<" "<<i<<std::endl;
    }*/

    parser p(tokens);
    expr* exp = p.parse();
    interpreter inter;
    value val = inter.interpret(exp, jsonCard);
    if (val.val_type == DOUBLE){
        std::cout<<"значение: "<<val.doub_val<< std::endl;
    } else if (val.val_type == JSON){
        std::cout<<"это json "<< std::endl;
        std::cout<<"значение: "<<val.json_val.dump()<< std::endl;
    } else if (val.val_type == BOOL){
        std::cout<<"это bool "<< std::endl;
        std::cout<<"значение: "<<val.bool_val<< std::endl;
    } else if (val.val_type == STRING){
        std::cout<<"это string "<< std::endl;
        std::cout<<"значение: "<<val.str_val<< std::endl;
    } else if (val.val_type == EMPTY){
        std::cout<<"пусто"<< std::endl;
    } 
    delete exp;
    
    return 0;
}