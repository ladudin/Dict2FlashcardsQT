#include "ImagesProviderWrapper.hpp"

ImagesProviderWrapper::ImagesProviderWrapper(std::string &&name,
                                             Container   &&container)
    : name_(name), container_(container) {
}

auto ImagesProviderWrapper::build(std::string name, Container containter)
    -> std::variant<ImagesProviderWrapper, PyExceptionInfo> {
    // auto wrapper = ImagesProviderWrapper(std::move(containter));
    // try {
    //
    // } catch (const boost::python::error_already_set &) {
    //     auto info = PyExceptionInfo::build();
    //     return info;
    // }
    //
    // return wrapper;
}

auto ImagesProviderWrapper::name() const -> const std::string & {
    return name_;
}

auto ImagesProviderWrapper::get(const std::string &word, uint64_t batch_size)
    -> std::variant<ImagesProviderWrapper::type, PyExceptionInfo> {
}

auto ImagesProviderWrapper::load() -> std::optional<PyExceptionInfo> {
}

auto ImagesProviderWrapper::unload() -> std::optional<PyExceptionInfo> {
}

auto ImagesProviderWrapper::get_config_description()
    -> std::variant<PyExceptionInfo, nlohmann::json> {
}

auto ImagesProviderWrapper::get_default_config()
    -> std::variant<PyExceptionInfo, nlohmann::json> {
}

auto ImagesProviderWrapper::set_config(nlohmann::json &&new_config)
    -> std::variant<PyExceptionInfo, nlohmann::json> {
}
