#include "deckmock.h"
#include <QDebug>
#include <QString>
#include <iostream>

DeckMock::DeckMock()
{
    WordCards* go_cards = new WordCards("go");

    Card* card1 = new Card;
    card1->word = "go";
    card1->definition = "ходить";
    go_cards->addCard(card1);

    Card* card2 = new Card;
    card2->word = "go";
    card2->definition = "идти";
    go_cards->addCard(card2);

    Card* card3 = new Card;
    card3->word = "go";
    card3->definition = "уйти";
    go_cards->addCard(card3);

    Card* card4 = new Card;
    card4->word = "go";
    card4->definition = "пойти";
    go_cards->addCard(card4);

    WordCards* play_cards = new WordCards("play");

    Card* card5 = new Card;
    card5->word = "play";
    card5->definition = "играть";
    play_cards->addCard(card5);

    Card* card6 = new Card;
    card6->word = "play";
    card6->definition = "игрулькать";
    play_cards->addCard(card6);

    Card* card7 = new Card;
    card7->word = "play";
    card7->definition = "гамать";
    play_cards->addCard(card7);

    Card* card8 = new Card;
    card8->word = "play";
    card8->definition = "катать";
    play_cards->addCard(card8);

    Card* card9 = new Card;
    card9->word = "play";
    card9->definition = "задротить";
    play_cards->addCard(card9);

    deck.push_back(go_cards);
    deck.push_back(play_cards);
}

size_t DeckMock::size() const
{
    return deck.size();
}

std::string DeckMock::getWord(size_t index) const
{
    if (index >= size())
    {
        return std::string();
    }
    return deck[index]->get_word();
}

Card *DeckMock::getCard(size_t index) const
{
    return deck[index]->get_card();
}

void DeckMock::next(size_t index)
{
    deck[index]->next();
}

void DeckMock::prev(size_t index)
{
    deck[index]->prev();
}

int DeckMock::indexOfWord(const std::string &word) const
{
    for (int i = 0; i < size(); ++i) {
        if (getWord(i) == word) {
            return i;
        }
    }
    return -1;
}

void DeckMock::load(std::string word)
{
    Card* card1 = new Card;
    card1->word = word;
    card1->definition = "ходить";

    Card* card2 = new Card;
    card2->word = word;
    card2->definition = "идти";

    Card* card3 = new Card;
    card3->word = word;
    card3->definition = "уйти";

    Card* card4 = new Card;
    card4->word = word;
    card4->definition = "пойти";

    for (size_t i = 0; i < size(); ++i)
    {
        if (getWord(i) == word)
        {
            deck[i]->addCard(card1);
            deck[i]->addCard(card2);
            deck[i]->addCard(card3);
            deck[i]->addCard(card4);
            return;
        }
    }
    WordCards* go_cards = new WordCards(word);
    go_cards->addCard(card1);
    go_cards->addCard(card2);
    go_cards->addCard(card3);
    go_cards->addCard(card4);
    deck.push_back(go_cards);
}


