#include "FormatProcessorWrapper.hpp"
#include "IPluginWrapper.hpp"

FormatProcessorWrapper::FormatProcessorWrapper(Container container) {
}

auto FormatProcessorWrapper::load() -> void {
}

auto FormatProcessorWrapper::get(ResultFilesPaths &&paths)
    -> FormatProcessorWrapper::type {
    return {};
}

auto FormatProcessorWrapper::get_config_description() -> nlohmann::json {
    return {};
}

auto FormatProcessorWrapper::get_default_config() -> nlohmann::json {
    return {};
}

auto FormatProcessorWrapper::set_config(nlohmann::json &&new_config)
    -> nlohmann::json {
    return {};
}

auto FormatProcessorWrapper::unload() -> void {
}
