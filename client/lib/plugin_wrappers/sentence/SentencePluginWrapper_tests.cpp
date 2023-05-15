//#include "../../include/wrappers/SentencePluginWrapper.h"
//#include "mock_classes.h"
//
//#include <memory>
//#include <string>
//#include <vector>
//
//#include <gtest/gtest.h>
//
//TEST(SentencePWOutputTest, Get) {
//    auto               memorizer = std::make_shared<Memorizer>();
//    SentencePluginWrapper wrapper(memorizer);
//    wrapper.get("test_word", 5);
//
//    std::string actual = memorizer->received_message;
//    std::string expected =
//        R"({ "query_type" : "get", "plugin_type" : "sentence", "query" : { "word" : "go", "count" : 5 } })";
//    EXPECT_EQ(expected, actual);
//}
//
//TEST(SentencePWInputTest, GetSuccess) {
//    std::string answer = R"({ "status" : 0, "result" : ["link_1", "link_2"]})";
//    auto        fixed_answer = std::make_shared<FixedAnswer>(answer);
//    SentencePluginWrapper       wrapper(fixed_answer);
//
//    std::vector<std::string> actual   = wrapper.get("", 2);
//    std::vector<std::string> expected = {"link_1", "link_2"};
//
//    EXPECT_EQ(expected, actual);
//}
//
//TEST(SentencePWInputTest, GetFailure) {
//    std::string        answer       = R"({ "status" : 1, "result" : "null" })";
//    auto               fixed_answer = std::make_shared<FixedAnswer>(answer);
//    SentencePluginWrapper wrapper(fixed_answer);
//
//    EXPECT_THROW(wrapper.get("", 2), std::runtime_error);
//}