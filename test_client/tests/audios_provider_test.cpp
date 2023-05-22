#include <boost/asio/io_service.hpp>
#include <gtest/gtest.h>
#include <iostream>
#include <math.h>
#include <nlohmann/json.hpp>
#include <string>

#include "Media.hpp"
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
            R"("plugin_name": "audios", "plugin_type": "audios" })"            \
            "\r\n";                                                            \
        auto expected = R"*({"status": 0, "message": ""})*"_json;              \
        auto actual   = sender.request(request);                               \
        ASSERT_EQ(expected, actual);                                           \
    } while (0)

TEST(AudiosProvider, Init) {
    SetUp();
    Init(sender);
}

TEST(AudiosProvider, ValidateConfig) {
    SetUp();
    Init(sender);

    const auto *request  = R"(
        {
            "query_type": "validate_config",
            "plugin_type": "audios",
            "config": {"audio region": "uk", "timeout": 1}
        })"
                           "\r\n";

    auto        expected = R"*({"status": 0, "result": {}})*"_json;
    auto        actual   = sender.request(request);
    ASSERT_EQ(expected, actual);
}

TEST(AudiosProvider, blankGet) {
    SetUp();
    Init(sender);

    const auto *request = R"*(
        {
            "query_type": "get",
            "plugin_type": "audios",
            "word": "sunshade",
            "filter": "",
            "batch_size": 0,
            "restart": false
        })*"
                          "\r\n";

    auto        expected =
        R"*({"result": [{"local": [], "web": []}, ""], "status": 0})*"_json;
    auto actual = sender.request(request);
    ASSERT_EQ(expected, actual);
}

TEST(AudiosProvider, Get) {
    SetUp();
    Init(sender);

    const auto *request = R"*(
        {
            "query_type": "get",
            "plugin_type": "audios",
            "word": "sunshade",
            "filter": "",
            "batch_size": 5,
            "restart": false
        })*"
                          "\r\n";

    auto        actual  = sender.request(request);
    ASSERT_EQ(actual["status"], 0);
    ASSERT_FALSE(actual["result"][1].empty());
    Media links = actual["result"][0];
    ASSERT_LE(links.web.size(), 5);
}

TEST(AudiosProvider, ListPlugins) {
    SetUp();
    Init(sender);

    const auto *request = R"(
        {
            "query_type": "list_plugins",
            "plugin_type": "audios"
        })"
                          "\r\n";

    auto        expected =
        R"*({"result": {"success": ["audios"], "failed": []}, "status": 0})*"_json;
    auto actual = sender.request(request);
    ASSERT_EQ(expected, actual);
}
