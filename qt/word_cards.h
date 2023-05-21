#ifndef WORD_CARDS_H
#define WORD_CARDS_H

#include <string>
#include <vector>
#include "Card.h"

class WordCards {
public:
    explicit WordCards(const std::string& name);
    size_t size() const;
    std::string get_word() const;
    const Card* get_card() const;
    void next();
    void prev();
    void addCard(Card card);

private:
    std::string word;
    std::vector<Card> cards;
    size_t pos;
};

#endif // WORD_CARDS_H
