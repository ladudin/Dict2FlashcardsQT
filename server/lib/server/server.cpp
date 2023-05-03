#include "server.hpp"
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/bind.hpp>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <string>

using boost::asio::ip::tcp;
using nlohmann::json;

TCPConnection::TCPConnection(
    boost::asio::ip::tcp::socket        socket,
    std::unique_ptr<IResponceGenerator> response_generator)
    : socket_(std::move(socket)) {
    response_generator_.reset(std::move(response_generator));
}

void TCPConnection::start() {
    do_read();
}

void TCPConnection::do_read() {
    auto self = shared_from_this();

    // https://stackoverflow.com/questions/3058589/boostasioasync-read-until-reads-all-data-instead-of-just-some
    boost::asio::async_read_until(
        socket_,
        request_buffer,
        "\n\r",
        [this, self](boost::system::error_code error_code, std::size_t length) {
            if (error_code) {
                std::cerr << "TCPSesssion error: " << error_code << std::endl;
                return;
            }
            request_buffer.commit(length);
            std::istream istrm(&request_buffer);
            std::string  result;
            istrm >> result;

            json parsed_request = json::parse(result);
            assert(parsed_request.is_object());
            assert(parsed_request.contains("query_type"));

            json query_type = parsed_request["query_type"];
            assert(query_type.is_string());

            parsed_request["query_type"];
        });
}

void TCPConnection::do_write(std::size_t length) {
    // auto self(shared_from_this());
    // boost::asio::async_write(
    //     socket_,
    //     boost::asio::buffer(data_, length),
    //     [this, self](boost::system::error_code ec, std::size_t /*length*/) //
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
                std::make_shared<TCPConnection>(std::move(socket))->start();
            }
            start_accept();
        });
}
