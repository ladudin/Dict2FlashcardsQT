#include <memory>
#include <string>
#include <vector>
#include <iostream>

#include "Card.h"
#include "WordPluginWrapper.h"
#include "mock_classes.h"

#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

//using namespace nlohmann;
//
//TEST(WordPWOutputTest, GetDictScheme) {
//    auto              memorizer = std::make_shared<Memorizer>();
//    WordPluginWrapper wrapper(memorizer);
//    EXPECT_THROW(wrapper.get_dict_scheme(), std::runtime_error);
//
//    json actual   = json::parse(memorizer->received_message);
//    json expected = json::parse(
//        R"({ "query_type" : "get_dict_scheme" , "plugin_type" : "word" })");
//    EXPECT_EQ(expected, actual);
//}
//
//TEST(WordPWOutputTest, Get) {
//    auto              memorizer = std::make_shared<Memorizer>();
//    WordPluginWrapper wrapper(memorizer);
//    EXPECT_THROW(wrapper.get("go"), std::runtime_error);
//
//    json actual   = json::parse(memorizer->received_message);
//    json expected = json::parse(
//        R"({ "query_type" : "get", "plugin_type" : "word", "query" : "go" })");
//    EXPECT_EQ(expected, actual);
//}
//
//TEST(WordPWInputTest, GetDefaultConfigSuccess) {
//    std::string answer =
//        R"({ "status" : 0, "result" : { "field_1" : "value_1", "field_2" : "value_2" }})";
//    auto              fixed_answer = std::make_shared<FixedAnswer>(answer);
//    WordPluginWrapper wrapper(fixed_answer);
//
//    json              actual = json::parse(wrapper.get_dict_scheme());
//    json              expected =
//        json::parse(R"({ "field_1" : "value_1", "field_2" : "value_2" })");
//    EXPECT_EQ(expected, actual);
//}
//
//TEST(WordPWInputTest, GetDefaultConfigFailure) {
//    std::string       answer       = R"({ "status" : 1, "result" : "null" })";
//    auto              fixed_answer = std::make_shared<FixedAnswer>(answer);
//    WordPluginWrapper wrapper(fixed_answer);
//
//    EXPECT_THROW(wrapper.get_dict_scheme(), std::runtime_error);
//}
//
//TEST(WordPWInputTest, GetSuccess) {
//    std::string answer =
//        R"({"status":0,"result":[{"word":"go","special":["something special"],"definition":"move","examples":["go somewhere"],"image_links":[],"audio_links":[],"tags":{"tag":"tag"},"other":{"other":"other"}}]})";
//    auto              fixed_answer = std::make_shared<FixedAnswer>(answer);
//    WordPluginWrapper wrapper(fixed_answer);
//
//    std::vector<Card> actual   = wrapper.get("go");
//    std::vector<Card> expected = {
//        Card{
//             "go", {"something special"},
//             "move", {"go somewhere"},
//             std::vector<std::string>(),
//             std::vector<std::string>(),
//             json({{"tag", "tag"}}),
//             json({{"other", "other"}}),
//             }
//    };
//    EXPECT_EQ(expected, actual);
//}
//
//TEST(WordPWInputTest, GetFailure) {
//    std::string       answer       = R"({ "status" : 1, "result" : "null" })";
//    auto              fixed_answer = std::make_shared<FixedAnswer>(answer);
//    WordPluginWrapper wrapper(fixed_answer);
//
//    EXPECT_THROW(wrapper.get("go"), std::runtime_error);
//}