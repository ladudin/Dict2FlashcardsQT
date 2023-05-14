#include "FormatProcessorWrapper.hpp"
#include "Container.hpp"
#include "IPluginWrapper.hpp"

FormatProcessorWrapper::FormatProcessorWrapper(Container &&container)
    : container_(container) {
}

auto FormatProcessorWrapper::build(Container containter)
    -> std::variant<FormatProcessorWrapper, PyExceptionInfo> {
}

auto FormatProcessorWrapper::get(ResultFilesPaths &&paths)
    -> std::variant<FormatProcessorWrapper::type, PyExceptionInfo> {
}

auto FormatProcessorWrapper::load() -> std::optional<PyExceptionInfo> {
}

auto FormatProcessorWrapper::unload() -> std::optional<PyExceptionInfo> {
}

auto FormatProcessorWrapper::get_config_description()
    -> std::variant<PyExceptionInfo, nlohmann::json> {
}

auto FormatProcessorWrapper::get_default_config()
    -> std::variant<PyExceptionInfo, nlohmann::json> {
}

auto FormatProcessorWrapper::set_config(nlohmann::json &&new_config)
    -> std::variant<PyExceptionInfo, nlohmann::json> {
}
