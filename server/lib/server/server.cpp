#include "server.hpp"
#include "response_generators.hpp"
#include "session.hpp"
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/bind.hpp>
#include <boost/python.hpp>
#include <boost/python/extract.hpp>
#include <boost/python/import.hpp>
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

#error "Переставить путь к плагинам"

PluginServer::PluginServer(boost::asio::io_context &context, uint16_t port)
    : io_context_(context),
      acceptor_(io_context_, tcp::endpoint(tcp::v4(), port)) {
    Py_Initialize();
    try {
        // Так мы указываем пайтону откуда можно импортировать модули
        const auto           *plug_dir = "/home/blackdeer/projects/cpp/"
                                         "technopark_project/python_tests/plugins/";
        boost::python::object sys      = boost::python::import("sys");
        sys.attr("path").attr("append")(plug_dir);

        start_accept();
    } catch (...) {
        PyErr_Print();
        PyErr_Clear();
    }
}

void PluginServer::start_accept() {
    acceptor_.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket) {
            if (!ec) {
                std::make_shared<Session<ResponceGenerator>>(std::move(socket))
                    ->start();
            }
            start_accept();
        });
}
