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

PluginServer::PluginServer(boost::asio::io_context &context, uint16_t port)
    : io_context_(context),
      acceptor_(io_context_, tcp::endpoint(tcp::v4(), port)) {
    Py_Initialize();
    try {
        const auto           *plug_dir = "/home/blackdeer/projects/cpp/"
                                         "technopark_project/python_tests/plugins/";
        // Так мы указываем пайтону откуда можно импортировать модули
        boost::python::object sys      = boost::python::import("sys");
        sys.attr("path").attr("append")(plug_dir);

        boost::python::object cambridge_plug =
            boost::python::import("cambridge");
        boost::python::object wordset_plug = boost::python::import("wordset");

        // boost::python::object response =
        //     http.attr("urlopen")("http://www.google.com");
        // boost::python::object read = response.attr("read")();
        // std::string strResponse    =
        // boost::python::extract<std::string>(read); std::cout << strResponse
        // << std::endl;
    } catch (...) {
        PyErr_Print();
        PyErr_Clear();
    }

    start_accept();
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
