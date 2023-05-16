#include "../BasicPluginWrapper.h"
#include "mock_classes.h"

#include <memory>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

using namespace nlohmann;

TEST(BasicPWInitTest, Output) {
    auto               memorizer = std::make_shared<Memorizer>();
    BasicPluginWrapper wrapper(memorizer, "tests");
    wrapper.init("test_name");

    json actual   = json::parse(memorizer->received_message);
    json expected = json::parse(
        R"({ "query_type" : "init", "plugin_type" : "tests", "plugin_name" : "test_name" })");
    EXPECT_EQ(expected, actual);
}

TEST(BasicPWInitTest, Success) {
    std::string        answer       = R"({ "status" : 0, "error" : "null"})";
    auto               fixed_answer = std::make_shared<FixedAnswer>(answer);
    BasicPluginWrapper wrapper(fixed_answer, "tests");

    EXPECT_TRUE(wrapper.init("exiting_plugin").empty());
}

TEST(BasicPWInitTest, Error) {
    std::string        answer       = R"({ "status" : 1, "error" : "something" })";
    auto               fixed_answer = std::make_shared<FixedAnswer>(answer);
    BasicPluginWrapper wrapper(fixed_answer, "tests");

    std::string actual = wrapper.init("nonexiten_plugin");
    std::string expected = "something";

    EXPECT_EQ(actual, expected);
}

TEST(BasicPWInitTest, WrongResponseFormat) {
    std::string        answer       = R"({ "status" : "ok", "error" : "something" })";
    auto               fixed_answer = std::make_shared<FixedAnswer>(answer);
    BasicPluginWrapper wrapper(fixed_answer, "tests");

    std::string actual = wrapper.init("nonexiten_plugin");
    std::string expected = "Wrong response format";

    EXPECT_EQ(actual, expected);
}

TEST(BasicPWInitTest, Disconnect) {
    std::string        answer       = R"({ "status" : "0", "error" : "something" })";
    auto               fixed_answer = std::make_shared<FixedAnswer>(answer, false);
    BasicPluginWrapper wrapper(fixed_answer, "tests");

    std::string actual = wrapper.init("nonexiten_plugin");
    std::string expected = "Server disconnected";

    EXPECT_EQ(actual, expected);
}

TEST(BasicPWOutputTest, GetDefaultConfig) {
    auto               memorizer = std::make_shared<Memorizer>();
    BasicPluginWrapper wrapper(memorizer, "tests");
    EXPECT_THROW(wrapper.get_default_config(), std::runtime_error);

    json actual   = json::parse(memorizer->received_message);
    json expected = json::parse(
        R"({ "query_type" : "get_default_config", "plugin_type" : "tests" })");
    EXPECT_EQ(expected, actual);
}

//TEST(BasicPWOutputTest, GetDefaultScheme) {
//    auto               memorizer = std::make_shared<Memorizer>();
//    BasicPluginWrapper wrapper(memorizer, "tests");
//    EXPECT_THROW(wrapper.get_default_scheme(), std::runtime_error);
//
//    json actual   = json::parse(memorizer->received_message);
//    json expected = json::parse(
//        R"({ "query_type" : "get_default_scheme", "plugin_type" : "tests" })");
//
//    EXPECT_EQ(expected, actual);
//}
//
//TEST(BasicPWOutputTest, SetConfig) {
//    auto               memorizer = std::make_shared<Memorizer>();
//    BasicPluginWrapper wrapper(memorizer, "tests");
//    EXPECT_THROW(
//        wrapper.set_config(R"({ "language" : "english", "level" : "C2" })"),
//        std::runtime_error);
//
//    json actual   = json::parse(memorizer->received_message);
//    json expected = json::parse(
//        R"({ "query_type" : "set_config", "plugin_type" : "tests", "query" : { "language" : "english", "level" : "C2" } })");
//    EXPECT_EQ(expected, actual);
//}
//
//TEST(BasicPWOutputTest, ListPlugins) {
//    auto               memorizer = std::make_shared<Memorizer>();
//    BasicPluginWrapper wrapper(memorizer, "tests");
//    EXPECT_THROW(wrapper.list_plugins(), std::runtime_error);
//
//    json actual   = json::parse(memorizer->received_message);
//    json expected = json::parse(
//        R"({ "query_type" : "list_plugins", "plugin_type" : "tests" })");
//    EXPECT_EQ(expected, actual);
//}
//
//TEST(BasicPWOutputTest, LoadNewPlugins) {
//    auto               memorizer = std::make_shared<Memorizer>();
//    BasicPluginWrapper wrapper(memorizer, "tests");
//    EXPECT_THROW(wrapper.load_new_plugins(), std::runtime_error);
//
//    json actual   = json::parse(memorizer->received_message);
//    json expected = json::parse(
//        R"({ "query_type" : "load_new_plugins", "plugin_type" : "tests" })");
//    EXPECT_EQ(expected, actual);
//}

//TEST(BasicPWInputTest, GetDefaultConfigSuccess) {
//    std::string answer =
//        R"({ "status" : 0, "result" : { "language" : "english", "level" : "C2" }})";
//    auto               fixed_answer = std::make_shared<FixedAnswer>(answer);
//    BasicPluginWrapper wrapper(fixed_answer, "tests");
//
//    json               actual = json::parse(wrapper.get_default_config());
//    json               expected =
//        json::parse(R"({ "language" : "english", "level" : "C2" })");
//    EXPECT_EQ(expected, actual);
//}
//
//TEST(BasicPWInputTest, GetDefaultConfigFailure) {
//    std::string        answer       = R"({"status" : 1, "result" : "null"})";
//    auto               fixed_answer = std::make_shared<FixedAnswer>(answer);
//    BasicPluginWrapper wrapper(fixed_answer, "tests");
//
//    EXPECT_THROW(wrapper.get_default_config(), std::runtime_error);
//}
//
//TEST(BasicPWInputTest, GetDefaultSchemeSuccess) {
//    std::string answer =
//        R"({ "status" : 0, "result" : { "language" : ["english", "russian"],
//        "level" : ["C2", "C1"] }})";
//    auto               fixed_answer = std::make_shared<FixedAnswer>(answer);
//    BasicPluginWrapper wrapper(fixed_answer, "tests");
//
//    json               actual   = json::parse(wrapper.get_default_scheme());
//    json               expected = json::parse(
//        R"({ "language" : ["english", "russian"], "level" : ["C2", "C1"] })");
//    EXPECT_EQ(expected, actual);
//}
//
//TEST(BasicPWInputTest, GetDefaultSchemeFailure) {
//    std::string        answer       = R"({"status" : 1, "result" : "null"})";
//    auto               fixed_answer = std::make_shared<FixedAnswer>(answer);
//    BasicPluginWrapper wrapper(fixed_answer, "tests");
//
//    EXPECT_THROW(wrapper.get_default_scheme(), std::runtime_error);
//}
//
//TEST(BasicPWInputTest, SetConfigSuccess) {
//    std::string        answer       = R"({ "status" : 0, "result" : "null"})";
//    auto               fixed_answer = std::make_shared<FixedAnswer>(answer);
//    BasicPluginWrapper wrapper(fixed_answer, "tests");
//
//    std::map<std::string, std::string> actual = wrapper.set_config("{}");
//    EXPECT_TRUE(actual.empty());
//}
//
//TEST(BasicPWInputTest, SetConfigFailure) {
//    std::string answer =
//        R"({ "status" : 1, "result" : { "field_name" : "error_type",
//        "field_name2" : "error_type2" } })";
//    auto               fixed_answer = std::make_shared<FixedAnswer>(answer);
//    BasicPluginWrapper wrapper(fixed_answer, "tests");
//
//    std::map<std::string, std::string> actual   = wrapper.set_config("{}");
//    std::map<std::string, std::string> expected = {
//        {"field_name",  "error_type" },
//        {"field_name2", "error_type2"}
//    };
//    EXPECT_EQ(expected, actual);
//}
//
//TEST(BasicPWInputTest, ListPluginsSuccess) {
//    std::string answer =
//        R"({ "status" : 0, "result" : { "success": ["plugin_1"], "failed":
//        ["plugin_2"]} })";
//    auto               fixed_answer = std::make_shared<FixedAnswer>(answer);
//    BasicPluginWrapper wrapper(fixed_answer, "tests");
//
//    LoadResult         actual   = wrapper.list_plugins();
//    LoadResult         expected = {{"plugin_1"}, {"plugin_2"}};
//    EXPECT_EQ(expected, actual);
//}
//
//TEST(BasicPWInputTest, ListPluginsFailure) {
//    std::string        answer       = R"({"status" : 1, "result" : "null"})";
//    auto               fixed_answer = std::make_shared<FixedAnswer>(answer);
//    BasicPluginWrapper wrapper(fixed_answer, "tests");
//
//    EXPECT_THROW(wrapper.list_plugins(), std::runtime_error);
//}
//
//TEST(BasicPWInputTest, LoadNewPluginsSuccess) {
//    std::string answer =
//        R"({ "status" : 0, "result" : {"success": ["plugin_1", "plugin_2"],
//        "failed":["plugin_3"]} })";
//    auto               fixed_answer = std::make_shared<FixedAnswer>(answer);
//    BasicPluginWrapper wrapper(fixed_answer, "tests");
//
//    LoadResult         actual   = wrapper.list_plugins();
//    LoadResult         expected = {
//        {"plugin_1", "plugin_2"},
//        {"plugin_3"}
//    };
//    EXPECT_EQ(expected, actual);
//}
//
//TEST(BasicPWInputTest, LoadNewPluginsFailure) {
//    std::string        answer       = R"({ "status" : 1, "result" : "null"
//    })";
//    auto               fixed_answer = std::make_shared<FixedAnswer>(answer);
//    BasicPluginWrapper wrapper(fixed_answer, "tests");
//
//    EXPECT_THROW(wrapper.load_new_plugins(), std::runtime_error);
//}
