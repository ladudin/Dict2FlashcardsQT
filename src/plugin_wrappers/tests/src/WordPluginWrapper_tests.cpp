#include "plugin_wrappers/tests/src/mock_classes.h"
#include "plugin_wrappers/word_plugin_wrapper/WordPluginWrapper.h"

#include <memory>
#include <string>
#include <vector>

#include <gtest/gtest.h>

TEST(WordPWOutputTest, GetDictScheme) {
    auto              memorizer = std::make_shared<Memorizer>();
    WordPluginWrapper wrapper(memorizer);
    wrapper.get_dict_scheme();

    std::string actual   = memorizer->received_message;
    std::string expected = R"({ "query_type" : "get_dict_scheme" })";
    EXPECT_EQ(expected, actual);
}

TEST(WordPWOutputTest, Get) {
    auto              memorizer = std::make_shared<Memorizer>();
    WordPluginWrapper wrapper(memorizer);
    wrapper.get();

    std::string actual   = memorizer->received_message;
    std::string expected = R"({ "query_type" : "get", "plugin_type" : "word", "query" : { "word" : "go" } })";
    EXPECT_EQ(expected, actual);
}

TEST(WordPWInputTest, GetDefaultConfigSuccess) {
    std::string answer =
        R"({ "status" : 0, "result" : { "field_1" : "value_1", "field_2" : "value_2" }})";
    auto              fixed_answer = std::make_shared<FixedAnswer>(answer);
    WordPluginWrapper wrapper(fixed_answer);

    std::string       actual = wrapper.get_dict_scheme();
    std::string       expected =
        R"({ "field_1" : "value_1", "field_2" : "value_2" })";
    EXPECT_EQ(expected, actual);
}

TEST(WordPWInputTest, GetDefaultConfigFailure) {
    std::string       answer       = R"({ "status" : 1, "result" : "null" })";
    auto              fixed_answer = std::make_shared<FixedAnswer>(answer);
    WordPluginWrapper wrapper(fixed_answer);

    EXPECT_THROW(wrapper.get_dict_scheme(), std::runtime_error);
}

TEST(WordPWInputTest, GetSuccess) {
    std::string answer =
        R"({ "status" : 0, "result" : [ { card_fields }, { card_2_fields } ]})";
    auto              fixed_answer = std::make_shared<FixedAnswer>(answer);
    WordPluginWrapper wrapper(fixed_answer);

    std::vector<Card>       actual = wrapper.get();
    std::vector<Card>       expected = { Card(card_fields), Card(card_2_fileds)};
    EXPECT_EQ(expected, actual);
}

TEST(WordPWInputTest, GetFailure) {
    std::string       answer       = R"({ "status" : 1, "result" : "null" })";
    auto              fixed_answer = std::make_shared<FixedAnswer>(answer);
    WordPluginWrapper wrapper(fixed_answer);

    EXPECT_THROW(wrapper.get(), std::runtime_error);
}