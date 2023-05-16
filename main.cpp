#include "interpreter.h"

int main(){
    /*Card card;
    card.word = "example aaaa";
    card.special = { "special1", "special2" };
    card.definition = "This is an example";
    card.examples = { "Example 1", "Example 2" };
    card.image_links = { "image1.jpg", "image2.jpg" };
    card.audio_links = { "audio1.mp3", "audio2.mp3" };
    card.tags = { { "tag1", "value1" }, { "tag2", "value2" } };
    card.other = { { "key1", "value1" }, { "key2", "value2" } };

    json jsonCard = card_to_json(card);
   
    std::string jsonString = jsonCard.dump();
    std::cout << jsonString << std::endl;*/

    /*scanner scan("(pos[$ANY][data][\"привет\"]!");
    std::vector<token> vec= scan.scan_tokens();
    for(int i = 0; i < vec.size();++i){
        std::cout<<vec[i].lexeme<<std::endl;

    }*/
    scanner scan("2");
    std::vector<token> tokens= scan.scan_tokens();
    parser p(tokens);
    expr* statements = p.parse();
    if(statements->)
    return 0;
}