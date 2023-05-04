#ifndef DICT2FLASHCARDSQT_SRC_DATAPROVIDER_SERVERCONNECTION_SERVERCONNECTION_H
#define DICT2FLASHCARDSQT_SRC_DATAPROVIDER_SERVERCONNECTION_SERVERCONNECTION_H

#include <boost/asio.hpp>

#include "data_providers/irequestable/IRequestable.h"

using boost::asio::ip::tcp;

class ServerConnection : public IRequestable {
 public:
    ServerConnection(const std::string &port,
                     const std::string &host = "localhost");
    ~ServerConnection();
    std::string request(const std::string &request) override;

 private:
    boost::asio::io_context io_context_;
    tcp::socket             socket_;
};

#endif  // DICT2FLASHCARDSQT_SRC_DATAPROVIDER_SERVERCONNECTION_SERVERCONNECTION_H
