#include "Card.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

using namespace nlohmann;

void traverse_tags(const json        &tags,
                   const std::string &prefix,
                   std::string       &result) {
    if (tags.is_object()) {
        for (auto &tag : tags.items()) {
            std::string new_prefix =
                prefix.empty() ? tag.key() + "::" : prefix + tag.key() + "::";
            traverse_tags(tag.value(), new_prefix, result);
        }
        return;
    }
    if (tags.is_array()) {
        for (auto &value : tags) {
            result += prefix + value.get<std::string>() + ' ';
        }
        return;
    }
    result += prefix + tags.get<std::string>() + ' ';
}

std::string parse_tags(const json &tags) {
    std::string result;
    traverse_tags(tags, "", result);
    if (result.back() == ' ')
        result.pop_back();
    return result;
}

void from_json(const json &j, Card &card) {
    j.at("word").get_to(card.word);
    j.at("special").get_to(card.special);
    j.at("definition").get_to(card.definition);
    j.at("examples").get_to(card.examples);
    j.at("image_links").get_to(card.image_links);
    j.at("audio_links").get_to(card.audio_links);
    //    j.at("tags").get_to(card.tags);
    card.tags = parse_tags(j.at("tags"));
}

void to_json(json &j, const Card &card) {
    j = json{
        {"word",        card.word       },
        {"special",     card.special    },
        {"definition",  card.definition },
        {"examples",    card.examples   },
        {"image_links", card.image_links},
        {"audio_links", card.audio_links},
        {"tags",        card.tags       },
    };
}

bool operator==(const Card &lhs, const Card &rhs) {
    return lhs.word == rhs.word && lhs.special == rhs.special &&
           lhs.definition == rhs.definition && lhs.examples == rhs.examples &&
           lhs.image_links == rhs.image_links &&
           lhs.audio_links == rhs.audio_links && lhs.tags == rhs.tags;
}

std::ostream &operator<<(std::ostream &os, const Card &card) {
    os << "Card {" << '\n';
    os << '\t' << "Word: " << card.word << '\n';
    os << '\t' << "Definition: " << card.definition << '\n';
    os << '\t' << "Special: [";
    for (const auto &special : card.special) {
        os << special << " ";
    }
    os << "]\n";
    os << '\t' << "Examples: [";
    for (const auto &example : card.examples) {
        os << example << " ";
    }
    os << "]\n";
    os << '\t' << "Image Links: [";
    for (const auto &image_link : card.image_links) {
        os << image_link << " ";
    }
    os << "]\n";
    os << '\t' << "Audio Links: [";
    for (const auto &audio_link : card.audio_links) {
        os << audio_link << " ";
    }
    os << "]\n";
    os << '\t' << "Tags: " << card.tags << '\n';
    os << "}\n";

    return os;
}

std::pair<std::vector<Card>, std::string> load_cards(const std::string &path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return {{}, "Can't open the file"};
    }
    std::stringstream buffer;
    if (buffer << file.rdbuf()) {
        try {
            return {json::parse(buffer.str()).get<std::vector<Card>>(), ""};
        } catch (...) {
            return {{}, "Wrong data format"};
        }
    }
    return {{}, "Can't read from file"};
}

std::string save_cards(const std::vector<Card> &cards,
                       const std::string       &path) {
    std::ofstream file(path);
    if (!file.is_open()) {
        return "Can't open the file";
    }
    std::string cards_dump = json(cards).dump();
    if (file << cards_dump) {
        return "";
    }
    return "Can't write into file";
}