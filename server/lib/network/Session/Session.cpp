#include "Session.hpp"
#include "spdlog/common.h"
#include "spdlog/spdlog.h"
#include <iostream>
#include <nlohmann/json.hpp>

using nlohmann::json;

Session::Session(boost::asio::ip::tcp::socket        socket,
                 std::unique_ptr<IResponceGenerator> response_generator)
    : socket_(std::move(socket)),
      response_generator_(std::move(response_generator)) {
}

void Session::start() {
    spdlog::info("Started new session");
    do_read();
}

void Session::do_read() {
    // https://stackoverflow.com/questions/3058589/boostasioasync-read-until-reads-all-data-instead-of-just-some
    auto self = shared_from_this();
    boost::asio::async_read_until(
        socket_,
        request_buffer,
        "\r\n",
        [this, self](boost::system::error_code error_code, std::size_t length) {
            if (error_code) {
                spdlog::error("Couldn't read from user");
                return;
            }
            request_buffer.commit(length);
            std::istream istrm(&request_buffer);
            std::string  result;
            istrm >> result;

            json response = response_generator_->handle(result);
            auto str_response = response.dump() + "\r\n";
            do_write(str_response);
        });
}

void Session::do_write(std::string response) {
    auto self(shared_from_this());
    boost::asio::async_write(
        socket_,
        boost::asio::buffer(response, response.length()),
        [this, self](boost::system::error_code ec, std::size_t length) {
            if (ec) {
                spdlog::error("Couldn't respond to user");
            }
            do_read();
        });
}
