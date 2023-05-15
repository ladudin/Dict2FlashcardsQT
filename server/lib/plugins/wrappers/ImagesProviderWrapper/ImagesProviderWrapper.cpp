#include "ImagesProviderWrapper.hpp"

ImagesProviderWrapper::ImagesProviderWrapper(std::string &&name,
                                             Container   &&container)
    : name_(name), container_(container) {
}

auto ImagesProviderWrapper::build(std::string name, Container containter)
    -> std::variant<ImagesProviderWrapper, PyExceptionInfo> {
    auto wrapper =
        ImagesProviderWrapper(std::move(name), std::move(containter));
    try {
        boost::python::object py_json       = boost::python::import("json");
        boost::python::object py_json_dumps = py_json.attr("dumps");

        boost::python::object py_plugin_conf =
            containter.get_default_config()();
        boost::python::object py_str_json_conf = py_json_dumps(py_plugin_conf);

        std::string           cpp_plugin_conf =
            boost::python::extract<std::string>(py_str_json_conf);
        wrapper.config_ = nlohmann::json::parse(cpp_plugin_conf);
    } catch (const boost::python::error_already_set &) {
        return PyExceptionInfo::build().value();
    }
    return wrapper;
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
