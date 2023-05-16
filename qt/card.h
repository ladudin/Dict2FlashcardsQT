#ifndef CARD_H
#define CARD_H

#include <string>
#include <vector>

struct Card {
    std::string word;
    std::string definition;
    std::vector<std::string> exaples;
    std::vector<std::string> image_links;
    std::vector<std::string> audio_links;
};

#endif // CARD_H
