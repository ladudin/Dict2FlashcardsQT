#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H

#include <string>

#include <boost/asio.hpp>

#include "IRequestable.h"

using boost::asio::ip::tcp;

class ServerConnection : public IRequestable {
 public:
    ServerConnection(unsigned short     port,
                     const std::string &host = "127.0.0.1");
    ~ServerConnection() override;
    std::pair<std::string, std::string>
    request(const std::string &request) override;

 private:
    boost::asio::io_context io_context_;
    tcp::socket             socket_;
    boost::asio::streambuf  buffer_;
};

#endif  // SERVERCONNECTION_H
