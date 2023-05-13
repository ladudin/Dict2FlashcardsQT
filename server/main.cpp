#include "PluginTypesLocationsConfig.hpp"
#include "PluginsProvider.hpp"
#include "Server.hpp"
#include <boost/asio.hpp>
#include <memory>

auto main(int argc, char *argv[]) -> int {
    auto plugins_dirs = PluginTypesLocationsConfig("", "", "", "", "");

    boost::asio::io_context io_context;
    auto                    plugins_provider =
        std::make_shared<PluginsProvider>(std::move(plugins_dirs));
    auto server = PluginServer(std::move(plugins_provider), io_context, 8888);
    io_context.run();
}
