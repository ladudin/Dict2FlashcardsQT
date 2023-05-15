#include "ServerConnection.h"

#include <iostream>
#include <string>

#include <boost/asio.hpp>

ServerConnection::ServerConnection(unsigned short port, const std::string &host)
    : io_context_(), socket_(io_context_), is_connected_(true) {
    boost::asio::ip::tcp::endpoint endpoint(
        boost::asio::ip::address::from_string(host), port);
    boost::system::error_code error;
    socket_.connect(endpoint);
    is_connected_ = !error;
}

ServerConnection::~ServerConnection() {
    socket_.close();
}

bool ServerConnection::is_connected() {
    return is_connected_;
}

std::pair<bool, std::string>
ServerConnection::request(const std::string &request) {
    boost::system::error_code error;

    boost::asio::write(socket_, boost::asio::buffer(request), error);
    if (error) {
        return std::make_pair(false, error.message());
        is_connected_ = false;
    }

    size_t bytes = boost::asio::read_until(socket_, buffer_, '\n', error);
    if (error) {
        return std::make_pair(false, error.message());
        is_connected_ = false;
    }

    std::string  response;
    std::istream is(&buffer_);
    std::getline(is, response);
    return std::make_pair(true, response);
}
