#ifndef DECKMOCK_H
#define DECKMOCK_H

#include <vector>
#include <string>
#include "IDeck.h"
#include "word_cards.h"

class DeckMock: public IDeck
{
public:
    DeckMock();

    size_t size() const override;
    void load(std::string word) override;
    std::string getWord(size_t index) const override;
    Card *getCard(size_t index) const override;
    void next(size_t index) override;
    void prev(size_t index) override;
    int indexOfWord(const std::string &word) const override;

private:
    std::vector<WordCards*> deck;
};

#endif // DECKMOCK_H
