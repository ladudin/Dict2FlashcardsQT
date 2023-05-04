#include "plugin_wrappers/basic_plugin_wrapper/BasicPluginWrapper.h"
#include "plugin_wrappers/tests/src/mock_classes.h"

#include <memory>
#include <string>
#include <vector>

#include <gtest/gtest.h>

TEST(BasicPWOutputTest, Init) {
    auto               memorizer = std::make_shared<Memorizer>();
    BasicPluginWrapper wrapper(memorizer, "test");
    wrapper.init("test_name");

    std::string actual = memorizer->received_message;
    std::string expected =
        R"({ "query_type" : "init", "plugin_type" : "test", "plugin_name" : "test_name" })";
    EXPECT_EQ(expected, actual);
}

TEST(BasicPWOutputTest, GetDefaultConfig) {
    auto               memorizer = std::make_shared<Memorizer>();
    BasicPluginWrapper wrapper(memorizer, "test");
    wrapper.get_default_config();

    std::string actual = memorizer->received_message;
    std::string expected =
        R"({ "query_type" : "get_default_config", "plugin_type" : "test" })";
    EXPECT_EQ(expected, actual);
}

TEST(BasicPWOutputTest, GetDefaultScheme) {
    auto               memorizer = std::make_shared<Memorizer>();
    BasicPluginWrapper wrapper(memorizer, "test");
    wrapper.get_default_scheme();

    std::string actual = memorizer->received_message;
    std::string expected =
        R"({ "query_type" : "get_default_scheme", "plugin_type" : "test" })";
    EXPECT_EQ(expected, actual);
}

TEST(BasicPWOutputTest, SetConfig) {
    auto               memorizer = std::make_shared<Memorizer>();
    BasicPluginWrapper wrapper(memorizer, "test");
    wrapper.set_config(R"({ "language" : "english", "level" : "C2" })");

    std::string actual = memorizer->received_message;
    std::string expected =
        R"({ "query_type" : "set_config", "plugin_type" : "test", "config" : { "language" : "english", "level" : "C2" })";
    EXPECT_EQ(expected, actual);
}

TEST(BasicPWOutputTest, ListPlugins) {
    auto               memorizer = std::make_shared<Memorizer>();
    BasicPluginWrapper wrapper(memorizer, "test");
    wrapper.get_default_scheme();

    std::string actual = memorizer->received_message;
    std::string expected =
        R"({ "query_type" : "get_default_scheme", "plugin_type" : "test" })";
    EXPECT_EQ(expected, actual);
}

TEST(BasicPWOutputTest, LoadNewPlugins) {
    auto               memorizer = std::make_shared<Memorizer>();
    BasicPluginWrapper wrapper(memorizer, "test");
    wrapper.get_default_scheme();

    std::string actual = memorizer->received_message;
    std::string expected =
        R"({ "query_type" : "load_new_plugins", "plugin_type" : "test" })";
    EXPECT_EQ(expected, actual);
}

TEST(BasicPWInputTest, InitSuccess) {
    std::string        answer       = R"({ "status" : 0, "result" : "null" })";
    auto               fixed_answer = std::make_shared<FixedAnswer>(answer);
    BasicPluginWrapper wrapper(fixed_answer, "test");

    EXPECT_NO_THROW(wrapper.init("exiting_plugin"));
}

TEST(BasicPWInputTest, InitFailure) {
    std::string        answer       = R"({ "status" : 1, "result" : "null" })";
    auto               fixed_answer = std::make_shared<FixedAnswer>(answer);
    BasicPluginWrapper wrapper(fixed_answer, "test");

    EXPECT_THROW(wrapper.init("nonexiten_plugin"), std::runtime_error);
}

TEST(BasicPWInputTest, GetDefaultConfigSuccess) {
    std::string answer =
        R"({ "status" : 0, "result" : { "language" : "english", "level" : "C2" }})";
    auto               fixed_answer = std::make_shared<FixedAnswer>(answer);
    BasicPluginWrapper wrapper(fixed_answer, "test");

    std::string        actual = wrapper.get_default_config();
    std::string expected      = R"({ "language" : "english", "level" : "C2" })";
    EXPECT_EQ(expected, actual);
}

TEST(BasicPWInputTest, GetDefaultConfigFailure) {
    std::string        answer       = R"({ "status" : 1, "result" : "null" })";
    auto               fixed_answer = std::make_shared<FixedAnswer>(answer);
    BasicPluginWrapper wrapper(fixed_answer, "test");

    EXPECT_THROW(wrapper.get_default_config(), std::runtime_error);
}

TEST(BasicPWInputTest, GetDefaultSchemeSuccess) {
    std::string answer =
        R"({ "status" : 0, "result" : { "language" : ["english", "russian"], "level" : ["C2", "C1"] }})";
    auto               fixed_answer = std::make_shared<FixedAnswer>(answer);
    BasicPluginWrapper wrapper(fixed_answer, "test");

    std::string        actual = wrapper.get_default_scheme();
    std::string        expected =
        R"({ "language" : ["english", "russian"], "level" : ["C2", "C1"] })";
    EXPECT_EQ(expected, actual);
}

TEST(BasicPWInputTest, GetDefaultSchemeFailure) {
    std::string        answer       = R"({ "status" : 1, "result" : "null" })";
    auto               fixed_answer = std::make_shared<FixedAnswer>(answer);
    BasicPluginWrapper wrapper(fixed_answer, "test");

    EXPECT_THROW(wrapper.get_default_scheme(), std::runtime_error);
}

TEST(BasicPWInputTest, SetConfigSuccess) {
    std::string        answer       = R"({ "status" : 0, "result" : "null"})";
    auto               fixed_answer = std::make_shared<FixedAnswer>(answer);
    BasicPluginWrapper wrapper(fixed_answer, "test");

    std::map<std::string, std::string> actual = wrapper.set_config("");
    EXPECT_TRUE(actual.empty());
    //     EXPECT_NO_THROW(wrapper.set_config(R"({ "language" : "english",
    //     "level" : "C2" })"));
}

TEST(BasicPWInputTest, SetConfigFailure) {
    std::string answer =
        R"({ "status" : 1, "result" : { "field_name" : "error_type", "field_name2" : "error_type2" } })";
    auto               fixed_answer = std::make_shared<FixedAnswer>(answer);
    BasicPluginWrapper wrapper(fixed_answer, "test");

    std::map<std::string, std::string> actual   = wrapper.set_config("");
    std::map<std::string, std::string> expected = {
        {"field_name",  "error_type" },
        {"field_name2", "error_type2"}
    };
    EXPECT_EQ(expected, actual);
}

TEST(BasicPWInputTest, ListPluginsSuccess) {
    std::string answer =
        R"({ "status" : 0, "result" : ["plugin_1", "plugin_2"] })";
    auto               fixed_answer = std::make_shared<FixedAnswer>(answer);
    BasicPluginWrapper wrapper(fixed_answer, "test");

    std::vector<std::string> actual   = wrapper.list_plugins();
    std::vector<std::string> expected = {"plugin_1", "plugin_2"};
    EXPECT_EQ(expected, actual);
}

TEST(BasicPWInputTest, ListPluginsFailure) {
    std::string        answer       = R"({ "status" : 1, "result" : "null" })";
    auto               fixed_answer = std::make_shared<FixedAnswer>(answer);
    BasicPluginWrapper wrapper(fixed_answer, "test");

    EXPECT_THROW(wrapper.list_plugins(), std::runtime_error);
}

TEST(BasicPWInputTest, LoadNewPluginsSuccess) {
    std::string answer =
        R"({ "status" : 0, "result" : ["plugin_1", "plugin_2", "plugin_3"] })";
    auto               fixed_answer = std::make_shared<FixedAnswer>(answer);
    BasicPluginWrapper wrapper(fixed_answer, "test");

    std::vector<std::string> actual   = wrapper.list_plugins();
    std::vector<std::string> expected = {"plugin_1", "plugin_2", "plugin_3"};
    EXPECT_EQ(expected, actual);
}

TEST(BasicPWInputTest, LoadNewPluginsFailure) {
    std::string        answer       = R"({ "status" : 1, "result" : "null" })";
    auto               fixed_answer = std::make_shared<FixedAnswer>(answer);
    BasicPluginWrapper wrapper(fixed_answer, "test");

    EXPECT_THROW(wrapper.load_new_plugins(), std::runtime_error);
}