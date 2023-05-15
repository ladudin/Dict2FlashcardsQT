#include "../../include/wrappers/FormatProcessorPluginWrapper.h"
#include "mock_classes.h"

#include <memory>
#include <string>
#include <vector>

#include <gtest/gtest.h>

TEST(FormatProcessorPWOutputTest, Save) {
    auto                         memorizer = std::make_shared<Memorizer>();
    FormatProcessorPluginWrapper wrapper(memorizer);
    wrapper.save("/cards", "/links", "/media");

    std::string actual = memorizer->received_message;
    std::string expected =
        R"({ "query_type" : "get", "plugin_type" : "format_processor", "query" : { "cards" : "/cards", "links" : "/links", "media" : "/media"} })";
    EXPECT_EQ(expected, actual);
}

TEST(FormatProcessorPWInputTest, SaveSuccess) {
    std::string answer       = R"({ "status" : 0, "result" : "null"})";
    auto        fixed_answer = std::make_shared<FixedAnswer>(answer);
    FormatProcessorPluginWrapper wrapper(fixed_answer);

    EXPECT_NO_THROW(wrapper.save("/cards", "/links", "/media"));
}

TEST(FormatProcessorPWInputTest, SaveFailure) {
    std::string answer       = R"({ "status" : 1, "result" : "null" })";
    auto        fixed_answer = std::make_shared<FixedAnswer>(answer);
    FormatProcessorPluginWrapper wrapper(fixed_answer);

    EXPECT_THROW(wrapper.save("/cards", "/links", "/media"),
                 std::runtime_error);
}