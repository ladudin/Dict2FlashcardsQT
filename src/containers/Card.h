#ifndef DICT2FLASHCARDSQT_SRC_CONTAINERS_CARD_H
#define DICT2FLASHCARDSQT_SRC_CONTAINERS_CARD_H

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
    nlohmann::json           tags;
    nlohmann::json           other;
};

inline void from_json(const nlohmann::json& j, Card& card) {
    j.at("word").get_to(card.word);
    j.at("special").get_to(card.special);
    j.at("definition").get_to(card.definition);
    j.at("examples").get_to(card.examples);
    j.at("image_links").get_to(card.image_links);
    j.at("audio_links").get_to(card.audio_links);
    j.at("tags").get_to(card.tags);
    j.at("other").get_to(card.other);
}

inline bool operator==(const Card& lhs, const Card& rhs) {
    // Compare each member of the Card struct using the == operator
    return lhs.word == rhs.word &&
           lhs.special == rhs.special &&
           lhs.definition == rhs.definition &&
           lhs.examples == rhs.examples &&
           lhs.image_links == rhs.image_links &&
           lhs.audio_links == rhs.audio_links &&
           lhs.tags == rhs.tags &&
           lhs.other == rhs.other;
}

// Print a Card object to an output stream
inline std::ostream& operator<<(std::ostream& os, const Card& card) {
    // Print each member of the Card struct using the << operator
    os << "Word: " << card.word << "\n";
    os << "Special: ";
    for (const auto& s : card.special) {
        os << s << " ";
    }
    os << "\n";
    os << "Definition: " << card.definition << "\n";
    os << "Examples: ";
    for (const auto& e : card.examples) {
        os << e << " ";
    }
    os << "\n";
    os << "Image links: ";
    for (const auto& i : card.image_links) {
        os << i << " ";
    }
    os << "\n";
    os << "Audio links: ";
    for (const auto& a : card.audio_links) {
        os << a << " ";
    }
    os << "\n";
    os << "Tags: " << card.tags.dump() << "\n";
    os << "Other: " << card.other.dump() << "\n";
    return os;
}


#endif  // DICT2FLASHCARDSQT_SRC_CONTAINERS_CARD_H
