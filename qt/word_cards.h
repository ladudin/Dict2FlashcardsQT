#ifndef WORD_CARDS_H
#define WORD_CARDS_H

#include <string>
#include <vector>
#include "card.h"

class WordCards {
public:
    explicit WordCards(const std::string& name);
    size_t size();
    std::string get_word() const;
    Card* get_card();
    void next();
    void prev();
    void addCard(Card* card);

private:
    std::string word;
    std::vector<Card*> cards;
    size_t pos;
};

#endif // WORD_CARDS_H
