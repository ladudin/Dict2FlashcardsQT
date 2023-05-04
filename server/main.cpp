#include "server.hpp"
#include <boost/asio.hpp>

auto main(int argc, char *argv[]) -> int {
    boost::asio::io_context io_context;
    auto                    server = PluginServer(io_context, 8888);
    io_context.run();
}
