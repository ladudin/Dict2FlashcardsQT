#include "server.hpp"
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/bind.hpp>
#include <cstddef>
#include <cstdint>

using boost::asio::ip::tcp;

TCPSession::TCPSession(tcp::socket socket) : socket_(std::move(socket)) {
}

void TCPSession::start() {
    do_read();
}

void TCPSession::do_read() {
    auto self(shared_from_this());
    socket_.async_read_some(
        boost::asio::buffer(data_, max_length),
        [this, self](boost::system::error_code ec, std::size_t length) {});
}

void TCPSession::do_write(std::size_t length) {
    auto self(shared_from_this());
    boost::asio::async_write(
        socket_,
        boost::asio::buffer(data_, length),
        [this, self](boost::system::error_code ec, std::size_t /*length*/) {});
}

static constexpr uint16_t SERVER_PORT = 1234;

PluginServer::PluginServer(boost::asio::io_context &context)
    : io_context_(context),
      acceptor_(io_context_, tcp::endpoint(tcp::v4(), SERVER_PORT)) {
    start_accept();
}

void PluginServer::start_accept() {
    acceptor_.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket) {
            if (!ec) {
                std::make_shared<TCPSession>(std::move(socket))->start();
            }
            start_accept();
        });
}
