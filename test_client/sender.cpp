//
// client.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <cstring>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string.h>

using boost::asio::ip::tcp;

void request(tcp::socket &socket, const std::string &json_request) {
    boost::array<char, 4069> buf = {};
    strncpy(buf.data(), json_request.c_str(), json_request.size());

    boost::system::error_code error;

    size_t                    len =
        socket.write_some(boost::asio::buffer(buf, strlen(buf.data())), error);
    size_t len2          = socket.read_some(boost::asio::buffer(buf), error);

    auto parsed_response = nlohmann::json::parse(buf.data(), buf.data() + len2);

    std::cout << "=======================================" << std::endl;
    std::cout << parsed_response.dump(2) << std::endl;

    if (error == boost::asio::error::eof) {
        return;
    }
    if (error) {
        throw boost::system::system_error(error);  // Some other error.
    }
}

int main(int argc, char *argv[]) {
    try {
        // if (argc != 2) {
        //     std::cerr << "Usage: client <host>" << std::endl;
        //     return 1;
        // }

        boost::asio::io_service        ios;

        boost::asio::ip::tcp::endpoint endpoint(
            boost::asio::ip::address::from_string("127.0.0.1"), 8888);

        boost::asio::ip::tcp::socket socket(ios);

        socket.connect(endpoint);

        // DEFINITIONS
        request(socket,
                R"(
                {
                    "query_type": "init",
                    "plugin_name": "definitions",
                    "plugin_type": "word"
                })"
                "\r\n");
        request(socket,
                R"(
{
    "query_type": "get", 
    "plugin_type": "word", 
    "filter": "",
    "word": "go",
    "batch_size": 5,
    "restart": false
})"
                "\r\n");
        // SENTENCES
        request(socket,
                R"(
                        {
                            "query_type": "init",
                            "plugin_name": "sentences",
                            "plugin_type": "sentences"
                        })"
                "\r\n");
        request(socket,
                R"(
        {
            "query_type": "get",
            "plugin_type": "sentences",
            "word": "go",
            "batch_size": 5,
            "restart": false
        })"
                "\r\n");
        // AUDIOS
        request(socket,
                R"(
                        {
                            "query_type": "init",
                            "plugin_name": "audios",
                            "plugin_type": "audios"
                        })"
                "\r\n");
        request(socket,
                R"(
        {
            "query_type": "get",
            "plugin_type": "audios",
            "word": "go",
            "batch_size": 5,
            "restart": false
        })"
                "\r\n");
        // IMAGES
        request(socket,
                R"(
                        {
                            "query_type": "init",
                            "plugin_name": "images",
                            "plugin_type": "images"
                        })"
                "\r\n");
        request(socket,
                R"(
        {
            "query_type": "get",
            "plugin_type": "images",
            "word": "go",
            "batch_size": 5,
            "restart": false
        })"
                "\r\n");

        // DEFINITIONS
        request(socket,
                R"(
{
    "query_type": "get", 
    "plugin_type": "word", 
    "filter": "",
    "word": "go",
    "batch_size": 5,
    "restart": false
})"
                "\r\n");

    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
