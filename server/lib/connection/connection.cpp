#include "connection.hpp"
#include <iostream>
#include <nlohmann/json.hpp>
#include <stdexcept>

using nlohmann::json;

TCPConnection::TCPConnection(
    boost::asio::ip::tcp::socket        socket,
    std::unique_ptr<IResponceGenerator> response_generator)
    : socket_(std::move(socket)),
      response_generator_(std::move(response_generator)) {
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
                // Заменим на логер
                std::cerr << "Couldn't read from user" << std::endl;
                return;
            }
            request_buffer.commit(length);
            std::istream istrm(&request_buffer);
            std::string  result;
            istrm >> result;

            json response = response_generator_->handle(result);
            do_write(response);

            // json parsed_request = json::parse(result);
            // assert(parsed_request.is_object());
            // assert(parsed_request.contains("query_type"));
            //
            // json query_type = parsed_request["query_type"];
            // assert(query_type.is_string());
            //
            // parsed_request["query_type"];
        });
}

void TCPConnection::do_write(std::string response) {
    auto self(shared_from_this());
    boost::asio::async_write(
        socket_,
        boost::asio::buffer(response, response.length()),
        [this, self](boost::system::error_code ec, std::size_t length) {
            if (ec) {
                std::cerr << "Couldn't respond to user" << std::endl;
            }
            do_read();
        });
}
