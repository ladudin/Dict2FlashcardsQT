#include "DefinitionsProviderWrapper.hpp"

DefinitionsProviderWrapper::DefinitionsProviderWrapper(std::string &&name,
                                                       Container   &&container)
    : name_(name), container_(container) {
}

auto DefinitionsProviderWrapper::build(std::string name, Container containter)
    -> std::variant<DefinitionsProviderWrapper, PyExceptionInfo> {
    auto wrapper =
        DefinitionsProviderWrapper(std::move(name), std::move(containter));
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

auto DefinitionsProviderWrapper::name() const -> const std::string & {
    return name_;
}

auto DefinitionsProviderWrapper::get(const std::string &word,
                                     uint64_t           batch_size)
    -> std::variant<DefinitionsProviderWrapper::type, PyExceptionInfo> {
}

auto DefinitionsProviderWrapper::load() -> std::optional<PyExceptionInfo> {
}

auto DefinitionsProviderWrapper::unload() -> std::optional<PyExceptionInfo> {
}

auto DefinitionsProviderWrapper::get_config_description()
    -> std::variant<PyExceptionInfo, nlohmann::json> {
}

auto DefinitionsProviderWrapper::get_default_config()
    -> std::variant<PyExceptionInfo, nlohmann::json> {
}

auto DefinitionsProviderWrapper::set_config(nlohmann::json &&new_config)
    -> std::variant<PyExceptionInfo, nlohmann::json> {
}
