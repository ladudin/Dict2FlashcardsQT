// https://github.com/gabime/spdlog/issues/1515
#include "spdlog/common.h"
#include <boost/bind/bind.hpp>
#define SPDLOG_ACTIVE_LEVEL                                                    \
    SPDLOG_LEVEL_TRACE  // Must: define SPDLOG_ACTIVE_LEVEL before `#include
                        // "spdlog/spdlog.h"`
#include "spdlog/sinks/stdout_sinks.h"
#include "spdlog/spdlog.h"

#include "DefinitionsProviderWrapper.hpp"
#include "FormatProcessorWrapper.hpp"
#include "PluginsProvider.hpp"
#include "Server.hpp"
#include <boost/asio.hpp>
#include <cstdint>
#include <iostream>
#include <memory>

auto main(int argc, char *argv[]) -> int {
    // https://github.com/gabime/spdlog/wiki/3.-Custom-formatting
    spdlog::set_pattern("[%H:%M:%S] [%s] line %# %v");

    Py_Initialize();
    auto plugins_dirs = PluginTypesLocationsConfig{
        .definitions_providers_dir =
            "/home/blackdeer/projects/cpp/technopark/plugins/definitions/",
        .sentences_providers_dir =
            "/home/blackdeer/projects/cpp/technopark/plugins/sentences/",
        .images_providers_dir =
            "/home/blackdeer/projects/cpp/technopark/plugins/images/",
        .audios_providers_dir =
            "/home/blackdeer/projects/cpp/technopark/plugins/audios/",
        .format_processors_dir = "/home/blackdeer/projects/cpp/technopark/"
                                 "plugins/format_processors/"};

    boost::asio::io_context io_context;
    boost::asio::signal_set signals(io_context, SIGINT, SIGTERM);
    signals.async_wait(
        boost::bind(&boost::asio::io_service::stop, &io_context));

    auto plugins_provider =
        std::make_shared<PluginsProvider>(std::move(plugins_dirs));
    constexpr uint16_t port = 8888;
    auto server = PluginServer(std::move(plugins_provider), io_context, port);
    io_context.run();
}
