#include "word_cards.h"

WordCards::WordCards(const std::string& word)
    : word(word)
    , pos(0)
{
}

size_t WordCards::size() const
{
    return cards.size();
}

std::string WordCards::get_word() const
{
    return word;
}

const Card* WordCards::get_card() const
{
    if (pos < 0 || pos >= size())
    {
        return nullptr;
    }
    return &cards[pos];
}

void WordCards::next()
{
    if (pos == size() - 1)
    {
        return;
    }
    ++pos;
}

void WordCards::prev()
{
    if (pos == 0)
    {
        return;
    }
    --pos;
}

void WordCards::addCard(Card card)
{
    cards.push_back(card);
}
