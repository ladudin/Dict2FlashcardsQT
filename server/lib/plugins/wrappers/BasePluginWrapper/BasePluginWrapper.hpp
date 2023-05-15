#ifndef BASE_PLUGIN_WRAPPER_H
#define BASE_PLUGIN_WRAPPER_H

#include "IPluginWrapper.hpp"
#include "PyExceptionInfo.hpp"

#include <boost/python/errors.hpp>
#include <boost/python/extract.hpp>
#include <boost/python/object_fwd.hpp>
#include <optional>
#include <utility>

using T = int;

// template <typename T>
class BasePluginWrapper : public IPluginWrapper<T> {
 public:
    static auto build(std::string name, Container container)
        -> std::variant<BasePluginWrapper /* <T> */, PyExceptionInfo> {
        auto wrapper =
            BasePluginWrapper /* <T> */ (std::move(name), std::move(container));
        try {
            boost::python::object py_json       = boost::python::import("json");
            boost::python::object py_json_dumps = py_json.attr("dumps");

            boost::python::object py_plugin_default_conf =
                wrapper.container_.get_default_config()();
            boost::python::object py_str_json_default_conf =
                py_json_dumps(py_plugin_default_conf);

            std::string cpp_plugin_default_conf =
                boost::python::extract<std::string>(py_str_json_default_conf);
            wrapper.config_ = nlohmann::json::parse(cpp_plugin_default_conf);
        } catch (const boost::python::error_already_set &) {
            return PyExceptionInfo::build().value();
        }
        return wrapper;
    }

    [[nodiscard]] auto name() const -> const std::string & override {
        return name_;
    }

    auto load() -> std::optional<PyExceptionInfo> override {
        try {
            boost::python::object plugin_load = container_.load();
            plugin_load();
        } catch (const boost::python::error_already_set &) {
            return PyExceptionInfo::build();
        }
        return std::nullopt;
    }

    auto unload() -> std::optional<PyExceptionInfo> override {
        try {
            boost::python::object plugin_unload = container_.load();
            plugin_unload();
        } catch (const boost::python::error_already_set &) {
            return PyExceptionInfo::build();
        }
        return std::nullopt;
    }

    auto get_config_description()
        -> std::variant<PyExceptionInfo, nlohmann::json> override {
        nlohmann::json config_description;
        try {
            boost::python::object py_json       = boost::python::import("json");
            boost::python::object py_json_dumps = py_json.attr("dumps");

            boost::python::object py_plugin_conf_description =
                container_.get_config_description()();
            boost::python::object py_str_json_conf_description =
                py_json_dumps(py_plugin_conf_description);

            std::string cpp_plugin_conf_description =
                boost::python::extract<std::string>(
                    py_str_json_conf_description);
            config_description =
                nlohmann::json::parse(cpp_plugin_conf_description);
        } catch (const boost::python::error_already_set &) {
            return PyExceptionInfo::build().value();
        }
        return config_description;
    }

    auto get_default_config()
        -> std::variant<PyExceptionInfo, nlohmann::json> override {
        nlohmann::json config_description;
        try {
            boost::python::object py_json       = boost::python::import("json");
            boost::python::object py_json_dumps = py_json.attr("dumps");

            boost::python::object py_plugin_conf_description =
                container_.get_config_description()();
            boost::python::object py_str_json_conf_description =
                py_json_dumps(py_plugin_conf_description);

            std::string cpp_plugin_conf_description =
                boost::python::extract<std::string>(
                    py_str_json_conf_description);
            config_description =
                nlohmann::json::parse(cpp_plugin_conf_description);
        } catch (const boost::python::error_already_set &) {
            return PyExceptionInfo::build().value();
        }
        return config_description;
    }

    auto set_config(nlohmann::json &&new_config)
        -> std::variant<PyExceptionInfo, nlohmann::json> override {
    }

 private:
    explicit BasePluginWrapper /* <T> */ (std::string &&name,
                                          Container   &&container);

    std::string    name_;
    Container      container_;
    nlohmann::json config_;
};

#endif  // !BASE_PLUGIN_WRAPPER_H
