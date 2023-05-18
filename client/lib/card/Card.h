#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

struct Card {
    std::string              word;
    std::vector<std::string> special;
    std::string              definition;
    std::vector<std::string> examples;
    std::vector<std::string> image_links;
    std::vector<std::string> audio_links;
    std::string              tags;
};

bool          operator==(const Card &lhs, const Card &rhs);
std::ostream &operator<<(std::ostream &os, const Card &card);

void          traverse_tags(const nlohmann::json &tags,
                            const std::string    &prefix,
                            std::string          &result);
std::string   parse_tags(const nlohmann::json &tags);

void          from_json(const nlohmann::json &j, Card &card);
void          to_json(nlohmann::json &j, const Card &card);

std::pair<std::vector<Card>, std::string> load_cards(const std::string &path);
std::string save_cards(const std::vector<Card> &cards, const std::string &path);

#endif  // CARD_H
