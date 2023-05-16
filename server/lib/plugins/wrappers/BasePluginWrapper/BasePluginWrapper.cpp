#include "BasePluginWrapper.hpp"

BasePluginWrapper::BasePluginWrapper(std::string &&name, Container &&container)
    : name_(name), container_(container) {
}

auto BasePluginWrapper::build(std::string name, Container container)
    -> std::variant<BasePluginWrapper, PyExceptionInfo> {
    auto wrapper = BasePluginWrapper(std::move(name), std::move(container));
    auto config_or_error = wrapper.get_default_config();
    if (std::holds_alternative<PyExceptionInfo>(config_or_error)) {
        auto error = std::get<PyExceptionInfo>(config_or_error);
        return error;
    }
    wrapper.config_ = std::get<nlohmann::json>(config_or_error);
    return wrapper;
}

[[nodiscard]] auto BasePluginWrapper::name() const -> const std::string & {
    return name_;
}

auto BasePluginWrapper::load() -> std::optional<PyExceptionInfo> {
    try {
        boost::python::object plugin_load = container_.load();
        plugin_load();
    } catch (const boost::python::error_already_set &) {
        return PyExceptionInfo::build().value();
    }
    return std::nullopt;
}

auto BasePluginWrapper::unload() -> std::optional<PyExceptionInfo> {
    try {
        boost::python::object plugin_unload = container_.load();
        plugin_unload();
    } catch (const boost::python::error_already_set &) {
        return PyExceptionInfo::build().value();
    }
    return std::nullopt;
}

auto BasePluginWrapper::get_config_description()
    -> std::variant<PyExceptionInfo, nlohmann::json> {
    nlohmann::json config_description;
    try {
        boost::python::object py_json       = boost::python::import("json");
        boost::python::object py_json_dumps = py_json.attr("dumps");

        boost::python::object py_plugin_conf_description =
            container_.get_config_description()();
        boost::python::object py_str_json_conf_description =
            py_json_dumps(py_plugin_conf_description);

        std::string cpp_plugin_conf_description =
            boost::python::extract<std::string>(py_str_json_conf_description);
        config_description = nlohmann::json::parse(cpp_plugin_conf_description);
    } catch (const boost::python::error_already_set &) {
        return PyExceptionInfo::build().value();
    }
    return config_description;
}

auto BasePluginWrapper::get_default_config()
    -> std::variant<PyExceptionInfo, nlohmann::json> {
    nlohmann::json default_config;
    try {
        boost::python::object py_json       = boost::python::import("json");
        boost::python::object py_json_dumps = py_json.attr("dumps");

        boost::python::object py_plugin_default_conf =
            container_.get_default_config()();
        boost::python::object py_str_json_default_conf =
            py_json_dumps(py_plugin_default_conf);

        std::string cpp_plugin_default_conf =
            boost::python::extract<std::string>(py_str_json_default_conf);
        default_config = nlohmann::json::parse(cpp_plugin_default_conf);
    } catch (const boost::python::error_already_set &) {
        return PyExceptionInfo::build().value();
    }
    return default_config;
}

auto BasePluginWrapper::set_config(nlohmann::json &&new_config)
    -> std::variant<PyExceptionInfo, nlohmann::json> {
    nlohmann::json diagnostics;
    try {
        boost::python::object py_json       = boost::python::import("json");
        boost::python::object py_json_loads = py_json.attr("loads");
        boost::python::object py_json_dumps = py_json.attr("dumps");

        std::string           new_conf_str  = new_config.dump();
        boost::python::object py_new_conf   = py_json_loads(py_json_loads);
        boost::python::object py_conf_diagnostics =
            container_.set_config()(py_new_conf);
        boost::python::object py_conf_diagnostics_str =
            py_json_dumps(py_conf_diagnostics);
        std::string cpp_conf_diagnostics_str =
            boost::python::extract<std::string>(py_conf_diagnostics_str);
        diagnostics = nlohmann::json::parse(cpp_conf_diagnostics_str);
        return diagnostics;
    } catch (const boost::python::error_already_set &) {
        return PyExceptionInfo::build().value();
    }
    return diagnostics;
}
