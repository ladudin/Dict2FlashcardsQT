#ifndef DICT2FLASHCARDSQT_SRC_DATAPROVIDER_SERVERCONNECTION_SERVERCONNECTION_H
#define DICT2FLASHCARDSQT_SRC_DATAPROVIDER_SERVERCONNECTION_SERVERCONNECTION_H

#include <string>
#include <variant>

#include <boost/asio.hpp>

#include "containers/ExceptionInfo.h"
#include "data_providers/irequestable/IRequestable.h"

using boost::asio::ip::tcp;

class ServerConnection : public IRequestable {
 public:
    ServerConnection(unsigned short     port,
                     const std::string &host = "127.0.0.1");
    ~ServerConnection();
    std::variant<std::string, ExceptionInfo>
    request(const std::string &request) override;

 private:
    boost::asio::io_context io_context_;
    tcp::socket             socket_;
    boost::asio::streambuf  buffer_;
};

#endif  // DICT2FLASHCARDSQT_SRC_DATAPROVIDER_SERVERCONNECTION_SERVERCONNECTION_H
