//#include "../../include/wrappers/AudioPluginWrapper.h"
//#include "mock_classes.h"
//
//#include <memory>
//#include <string>
//#include <vector>
//
//#include <gtest/gtest.h>
//
//TEST(AudioPWOutputTest, Get) {
//    auto               memorizer = std::make_shared<Memorizer>();
//    AudioPluginWrapper wrapper(memorizer);
//    wrapper.get("test_word", 5);
//
//    std::string actual = memorizer->received_message;
//    std::string expected =
//        R"({ "query_type" : "get", "plugin_type" : "audio", "query" : { "word" : "go", "count" : 5 } })";
//    EXPECT_EQ(expected, actual);
//}
//
//TEST(AudioPWInputTest, GetSuccess) {
//    std::string answer = R"({ "status" : 0, "result" : ["link_1", "link_2"]})";
//    auto        fixed_answer = std::make_shared<FixedAnswer>(answer);
//    AudioPluginWrapper       wrapper(fixed_answer);
//
//    std::vector<std::string> actual   = wrapper.get("", 2);
//    std::vector<std::string> expected = {"link_1", "link_2"};
//
//    EXPECT_EQ(expected, actual);
//}
//
//TEST(AudioPWInputTest, GetFailure) {
//    std::string        answer       = R"({ "status" : 1, "result" : "null" })";
//    auto               fixed_answer = std::make_shared<FixedAnswer>(answer);
//    AudioPluginWrapper wrapper(fixed_answer);
//
//    EXPECT_THROW(wrapper.get("", 2), std::runtime_error);
//}