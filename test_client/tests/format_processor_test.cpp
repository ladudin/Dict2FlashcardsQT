#include <boost/asio/io_service.hpp>
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
            R"("plugin_name": "processor", "plugin_type": "format" })"         \
            "\r\n";                                                            \
        auto expected = R"*({"status": 0, "message": ""})*"_json;              \
        auto actual   = sender.request(request);                               \
        ASSERT_EQ(expected, actual);                                           \
    } while (0)

TEST(FormatProcessor, Init) {
    SetUp();
    Init(sender);
}

TEST(FormatProcessor, ValidateConfig) {
    SetUp();
    Init(sender);

    const auto *request  = R"(
        {
            "query_type": "validate_config",
            "plugin_type": "format",
            "config": {}
        })"
                           "\r\n";

    auto        expected = R"*({"status": 0, "result": {}})*"_json;
    auto        actual   = sender.request(request);
    ASSERT_EQ(expected, actual);
}

TEST(FormatProcessor, Save) {
    SetUp();
    Init(sender);

    const auto *request  = R"(
    {
        "query_type": "save",
        "cards_path":
        "/home/blackdeer/projects/cpp/technopark/test_client/deck.json"
    })"
                           "\r\n";

    auto        expected = R"*({"message": "", "status": 0})*"_json;
    auto        actual   = sender.request(request);
    ASSERT_EQ(expected, actual);
}

TEST(FormatProcessor, ListPlugins) {
    SetUp();
    Init(sender);

    const auto *request = R"(
        {
            "query_type": "list_plugins",
            "plugin_type": "format"
        })"
                          "\r\n";

    auto        expected =
        R"*({"result": {"success": ["processor"], "failed": []}, "status": 0})*"_json;
    auto actual = sender.request(request);
    ASSERT_EQ(expected, actual);
}
