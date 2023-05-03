#include "server.hpp"
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/bind.hpp>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <string>

using boost::asio::ip::tcp;

TCPSession::TCPSession(tcp::socket socket) : socket_(std::move(socket)) {
}

void TCPSession::start() {
    do_read();
}

auto make_string(boost::asio::streambuf &streambuf) -> std::string {
    return {buffers_begin(streambuf.data()), buffers_end(streambuf.data())};
}

void TCPSession::do_read() {
    auto self = shared_from_this();

    boost::asio::async_read_until(
        socket_,
        request_buffer,
        ' ',  // https://stackoverflow.com/questions/3058589/boostasioasync-read-until-reads-all-data-instead-of-just-some
        [this, self](boost::system::error_code ec, std::size_t length) {
            std::cout << "reading " << length << std::endl;
            std::cout << make_string(request_buffer) << std::endl;

            request_buffer.consume(length);

            std::fflush(stdout);
            if (!ec) {
                do_read();
                return;
            }
            std::cout << ec << std::endl;
            std::fflush(stdout);
        });
}

void TCPSession::do_write(std::size_t length) {
    // auto self(shared_from_this());
    // boost::asio::async_write(
    //     socket_,
    //     boost::asio::buffer(data_, length),
    //     [this, self](boost::system::error_code ec, std::size_t /*length*/)
    //     {});
}

PluginServer::PluginServer(boost::asio::io_context &context, uint16_t port)
    : io_context_(context),
      acceptor_(io_context_, tcp::endpoint(tcp::v4(), port)) {
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
