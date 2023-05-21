#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <gtest/gtest.h>
#include <iostream>
#include <math.h>
#include <nlohmann/json.hpp>

#include "Sender.hpp"

#define SetUp()                                                                \
    boost::asio::io_service        ios;                                        \
    boost::asio::ip::tcp::socket   socket(ios);                                \
    boost::asio::ip::tcp::endpoint endpoint(                                   \
        boost::asio::ip::address::from_string("127.0.0.1"), 8888);             \
    socket.connect(endpoint);                                                  \
    auto sender = Sender(std::move(socket));

#define Init(sender)                                                           \
    do {                                                                       \
        const auto *request =                                                  \
            R"({"query_type": "init",)"                                        \
            R"("plugin_name": "definitions", "plugin_type": "word" })"         \
            "\r\n";                                                            \
        auto expected = R"*({"status": 0, "message": ""})*"_json;              \
        auto actual   = sender.request(request);                               \
        ASSERT_EQ(expected, actual);                                           \
    } while (0)

TEST(DefinitionsProvider, Init) {
    SetUp();
    Init(sender);
}

TEST(DefinitionsProvider, ValidateConfig) {
    SetUp();
    Init(sender);

    const auto *request  = R"(
        {
            "query_type": "validate_config",
            "plugin_type": "word",
            "config": {"audio region": "uk", "timeout": 1}
        })"
                           "\r\n";

    auto        expected = R"*({"status": 0, "result": {}})*"_json;
    auto        actual   = sender.request(request);
    ASSERT_EQ(expected, actual);
}

TEST(DefinitionsProvider, get) {
    SetUp();
    Init(sender);

    const auto *request  = R"*(
        {
            "query_type": "get",
            "plugin_type": "word",
            "word": "sunshade",
            "filter": "",
            "batch_size": 2,
            "restart": false
        })*"
                           "\r\n";

    auto        expected = R"*({
  "result": [
    [
      {
        "audios": {
          "local": [],
          "web": [
            [
              "https://dictionary.cambridge.org//media/english/uk_pron/u/uks/uksun/uksunbu025.mp3",
              ""
            ]
          ]
        },
        "definition": "an object similar to an umbrella that you carry to protect yourself from light from the sun",
        "examples": [],
        "images": {
          "local": [],
          "web": [
            [
              "https://dictionary.cambridge.org/images/thumb/paraso_noun_002_26494_2.jpg?version=5.0.318",
              ""
            ]
          ]
        },
        "other": [],
        "special": [],
        "tags": {
          "domain": [],
          "pos": [
            "noun"
          ],
          "region": [],
          "usage": []
        },
        "word": "sunshade"
      },
      {
        "audios": {
          "local": [],
          "web": [
            [
              "https://dictionary.cambridge.org//media/english/uk_pron/u/uks/uksun/uksunbu025.mp3",
              ""
            ]
          ]
        },
        "definition": "a larger folding frame of this type that you put into the ground to form an area that is sheltered from the light of the sun",
        "examples": [],
        "images": {
          "local": [],
          "web": [
            [
              "https://dictionary.cambridge.org/images/thumb/sunsha_noun_002_36661.jpg?version=5.0.318",
              ""
            ]
          ]
        },
        "other": [],
        "special": [
          "(US also umbrella)"
        ],
        "tags": {
          "domain": [],
          "pos": [
            "noun"
          ],
          "region": [],
          "usage": []
        },
        "word": "sunshade"
      }
    ],
    ""
  ],
  "status": 0
})*"_json;

    auto        actual   = sender.request(request);
    ASSERT_EQ(expected, actual);
}

TEST(DefinitionsProvider, blankGet) {
    SetUp();
    Init(sender);

    const auto *request  = R"*(
        {
            "query_type": "get",
            "plugin_type": "word",
            "word": "sunshade",
            "filter": "",
            "batch_size": 0,
            "restart": false
        })*"
                           "\r\n";

    auto        expected = R"*({"result": [[], ""], "status": 0})*"_json;
    auto        actual   = sender.request(request);
    ASSERT_EQ(expected, actual);
}

TEST(DefinitionsProvider, ListPlugins) {
    SetUp();
    Init(sender);

    const auto *request = R"(
        {
            "query_type": "list_plugins",
            "plugin_type": "word"
        })"
                          "\r\n";

    auto        expected =
        R"*({"result": {"success": ["definitions"], "failed": []}, "status": 0})*"_json;
    auto actual = sender.request(request);
    ASSERT_EQ(expected, actual);
}
