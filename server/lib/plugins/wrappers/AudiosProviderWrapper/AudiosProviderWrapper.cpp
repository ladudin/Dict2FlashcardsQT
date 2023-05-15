#include "AudiosProviderWrapper.hpp"
#include "Container.hpp"
#include "PyExceptionInfo.hpp"
#include <boost/python/extract.hpp>
#include <boost/python/import.hpp>
#include <cstdint>
#include <nlohmann/json_fwd.hpp>
#include <optional>
#include <utility>
#include <variant>

AudiosProviderWrapper::AudiosProviderWrapper(std::string &&name,
                                             Container   &&container)
    : name_(name), container_(container) {
}

auto AudiosProviderWrapper::build(std::string name, Container containter)
    -> std::variant<AudiosProviderWrapper, PyExceptionInfo> {
    auto wrapper =
        AudiosProviderWrapper(std::move(name), std::move(containter));
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

auto AudiosProviderWrapper::name() const -> const std::string & {
    return name_;
}

auto AudiosProviderWrapper::get(const std::string &word, uint64_t batch_size)
    -> std::variant<AudiosProviderWrapper::type, PyExceptionInfo> {
}

auto AudiosProviderWrapper::load() -> std::optional<PyExceptionInfo> {
}

auto AudiosProviderWrapper::unload() -> std::optional<PyExceptionInfo> {
}

auto AudiosProviderWrapper::get_config_description()
    -> std::variant<PyExceptionInfo, nlohmann::json> {
}

auto AudiosProviderWrapper::get_default_config()
    -> std::variant<PyExceptionInfo, nlohmann::json> {
}

auto AudiosProviderWrapper::set_config(nlohmann::json &&new_config)
    -> std::variant<PyExceptionInfo, nlohmann::json> {
}
