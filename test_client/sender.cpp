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
#include <iostream>

using boost::asio::ip::tcp;

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
        for (;;) {
            boost::array<char, 256> buf = {
                "{\"query_type\": \"init\", \"plugin_type\": \"word\", "
                "\"plugin_name\": \"definitions\"}\r\n"};
            boost::system::error_code error;

            // std::cout.write(buf.data(), 4);

            size_t len  = socket.write_some(boost::asio::buffer(buf), error);
            size_t len2 = socket.read_some(boost::asio::buffer(buf), error);
            if (error == boost::asio::error::eof)
                break;  // Connection closed cleanly by peer.
            else if (error)
                throw boost::system::system_error(error);  // Some other error.
        }
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
