#include "ImagePluginWrapper.h"
#include "mock_classes.h"

#include <memory>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

using namespace nlohmann;

TEST(ImagePWGet, Output) {
    auto               memorizer = std::make_shared<Memorizer>();
    ImagePluginWrapper wrapper(memorizer);
    wrapper.get("test_word", 5, true);

    json actual   = json::parse(memorizer->received_message);
    json expected = {
        {"query_type",  "get"      },
        {"plugin_type", "images"   },
        {"word",        "test_word"},
        {"batch_size",  5          },
        {"restart",     true       }
    };
    EXPECT_EQ(expected, actual);
}

TEST(ImagePWGet, FullSuccess) {
    json answer = {
        {"status",  0                                          },
        {"result",  json::array({"link_1", "link_2", "link_3"})},
        {"message", ""                                         }
    };
    auto fixed_answer = std::make_shared<FixedAnswer>(answer.dump());
    ImagePluginWrapper                               wrapper(fixed_answer);

    std::pair<std::vector<std::string>, std::string> actual =
        wrapper.get("test_word", 3, true);
    std::pair<std::vector<std::string>, std::string> expected = {
        std::vector<std::string>{"link_1", "link_2", "link_3"},
        ""
    };
    EXPECT_EQ(expected, actual);
}

TEST(ImagePWGet, PartialSuccess) {
    json answer = {
        {"status",  0                                          },
        {"result",  json::array({"link_1", "link_2", "link_3"})},
        {"message", "something"                                }
    };
    auto fixed_answer = std::make_shared<FixedAnswer>(answer.dump());
    ImagePluginWrapper                               wrapper(fixed_answer);

    std::pair<std::vector<std::string>, std::string> actual =
        wrapper.get("test_word", 3, true);
    std::pair<std::vector<std::string>, std::string> expected = {
        std::vector<std::string>{"link_1", "link_2", "link_3"},
        "something"
    };
    EXPECT_EQ(expected, actual);
}

TEST(ImagePWGet, Error) {
    json answer = {
        {"status",  1          },
        {"result",  "null"     },
        {"message", "something"}
    };
    auto fixed_answer = std::make_shared<FixedAnswer>(answer.dump());
    ImagePluginWrapper                               wrapper(fixed_answer);

    std::pair<std::vector<std::string>, std::string> actual =
        wrapper.get("test_word", 3, true);
    std::pair<std::vector<std::string>, std::string> expected = {
        std::vector<std::string>(), "something"};
    EXPECT_EQ(expected, actual);
}

// TEST(ImagePWGet, WrongResponseFormat) {
// }
//
// TEST(ImagePWGet, Disconnect) {
// }