#include "ServerConnection.h"

#include <iostream>
#include <string>

#include <boost/asio.hpp>

ServerConnection::ServerConnection(unsigned short port, const std::string &host)
    : io_context_(), socket_(io_context_) {
    boost::asio::ip::tcp::endpoint endpoint(
        boost::asio::ip::address::from_string(host), port);
    socket_.connect(endpoint);
}

ServerConnection::~ServerConnection() {
    socket_.close();
}

std::string ServerConnection::request(const std::string &request) {
    boost::asio::write(socket_, boost::asio::buffer(request));
    size_t       bytes = boost::asio::read_until(socket_, buffer_, '\n');
    std::string  response;
    std::istream is(&buffer_);
    std::getline(is, response);
    return response;
}
