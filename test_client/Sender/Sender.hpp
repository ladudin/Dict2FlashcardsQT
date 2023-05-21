#ifndef TEST_SENDER_H
#define TEST_SENDER_H

#include <array>
#include <boost/asio/ip/tcp.hpp>
#include <nlohmann/json.hpp>

class Sender {
 public:
    explicit Sender(boost::asio::ip::tcp::socket &&socket);

    auto request(const std::string &str_request) -> nlohmann::json;

 private:
    std::array<char, 4096>       bufffer_;
    boost::asio::ip::tcp::socket socket_;
};

#endif
