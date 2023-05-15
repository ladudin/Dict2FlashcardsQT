#include "DefinitionsProviderWrapper.hpp"
#include "FormatProcessorWrapper.hpp"
#include "PluginTypesLocationsConfig.hpp"
#include "PluginsProvider.hpp"
#include "Server.hpp"
#include <boost/asio.hpp>
#include <cstdint>
#include <iostream>
#include <memory>

auto main(int argc, char *argv[]) -> int {
    Py_Initialize();
    auto plugins_dirs = PluginTypesLocationsConfig(
        "/home/blackdeer/projects/cpp/technopark/plugins/definitions/",
        "/home/blackdeer/projects/cpp/technopark/plugins/sentences/",
        "/home/blackdeer/projects/cpp/technopark/plugins/images/",
        "/home/blackdeer/projects/cpp/technopark/plugins/audios/",
        "/home/blackdeer/projects/cpp/technopark/plugins/format_processors/");

    boost::asio::io_context io_context;
    // auto                    plugins_provider =
    // std::make_shared<PluginsProvider>(std::move(plugins_dirs));
    auto plugins_provider = PluginsProvider(std::move(plugins_dirs));
    auto format_processor_or_error =
        plugins_provider.get_format_processor("processor").value();

    auto format_processor =
        std::get<FormatProcessorWrapper>(format_processor_or_error);
    // constexpr uint64_t batch_size = 5;
    auto res_or_error = format_processor.get({"query", "123", "9595"});
    auto res          = std::get<FormatProcessorWrapper::type>(res_or_error);

    std::cout << res << std::endl;
    // auto server = PluginServer(std::move(plugins_provider), io_context,
    // 8888); io_context.run();
}
