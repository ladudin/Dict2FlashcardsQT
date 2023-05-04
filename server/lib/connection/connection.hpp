#ifndef CONNECTION_H
#define CONNECTION_H

#include "response_generators.hpp"
#include <boost/asio.hpp>
#include <string>

class TCPConnection : public std::enable_shared_from_this<TCPConnection> {
 public:
    explicit TCPConnection(
        boost::asio::ip::tcp::socket        socket,
        std::unique_ptr<IResponceGenerator> response_generator);

    void start();

 private:
    boost::asio::ip::tcp::socket        socket_;
    boost::asio::streambuf              request_buffer;
    std::unique_ptr<IResponceGenerator> response_generator_;

    void                                do_read();
    void                                do_write(std::string response);
};

#endif  // !CONNECTION_H
