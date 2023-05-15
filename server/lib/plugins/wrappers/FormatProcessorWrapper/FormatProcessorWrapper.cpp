#include "FormatProcessorWrapper.hpp"
#include "Container.hpp"
#include "IPluginWrapper.hpp"

FormatProcessorWrapper::FormatProcessorWrapper(std::string &&name,
                                               Container   &&container)
    : name_(name), container_(container) {
}

auto FormatProcessorWrapper::build(std::string name, Container containter)
    -> std::variant<FormatProcessorWrapper, PyExceptionInfo> {
}

auto FormatProcessorWrapper::name() const -> const std::string & {
    return name_;
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
