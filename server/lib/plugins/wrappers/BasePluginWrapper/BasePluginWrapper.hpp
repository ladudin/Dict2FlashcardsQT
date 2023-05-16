#ifndef BASE_PLUGIN_WRAPPER_H
#define BASE_PLUGIN_WRAPPER_H

#include <boost/python/errors.hpp>
#include <boost/python/extract.hpp>
#include <boost/python/object_fwd.hpp>
#include <nlohmann/json_fwd.hpp>
#include <optional>
#include <string>
#include <utility>
#include <variant>

#include "IPluginWrapper.hpp"
#include "PyExceptionInfo.hpp"

// using T = int;

template <typename T>
class BasePluginWrapper : public IPluginWrapper<T> {
 public:
    static auto build(std::string name, Container container)
        -> std::variant<BasePluginWrapper<T>, PyExceptionInfo> {
        auto wrapper =
            BasePluginWrapper<T>(std::move(name), std::move(container));
        auto config_or_error = wrapper.get_default_config();
        if (std::holds_alternative<PyExceptionInfo>(config_or_error)) {
            auto error = std::get<PyExceptionInfo>(config_or_error);
            return error;
        }
        wrapper.config_ = std::get<nlohmann::json>(config_or_error);
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
            return PyExceptionInfo::build().value();
        }
        return std::nullopt;
    }

    auto unload() -> std::optional<PyExceptionInfo> override {
        try {
            boost::python::object plugin_unload = container_.load();
            plugin_unload();
        } catch (const boost::python::error_already_set &) {
            return PyExceptionInfo::build().value();
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

    auto set_config(nlohmann::json &&new_config)
        -> std::variant<PyExceptionInfo, nlohmann::json> override {
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

 protected:
    explicit BasePluginWrapper<T>(std::string &&name, Container &&container)
        : name_(name), container_(container) {
    }

    std::string    name_;
    Container      container_;
    nlohmann::json config_;
};

template <class T>
concept container_constructible =
    requires(T instance, std::string name, Container container) {
        {
            T::build(name, container)
        } -> std::same_as<
            std::variant<BasePluginWrapper<typename T::type>, PyExceptionInfo>>;
    };

template <class T>
concept implements_wrapper_get = (
    // DefinitionsProvider, SentencesProvider, AudiosProvider, ImagesProvider
    requires(T                  dependent_instance,
             const std::string &query,
             uint64_t           batch_size) {
        {
            dependent_instance.get(query, batch_size)
        } -> std::same_as<std::variant<typename T::type, PyExceptionInfo>>;
    } ||
    requires(T                  dependent_instance,
             const std::string &query,
             const std::string &filter,
             bool restart,
             uint64_t           batch_size) {
        {
            dependent_instance.get(query, filter, batch_size, restart)
        } -> std::same_as<std::variant<typename T::type, PyExceptionInfo>>;
    } ||
    // FormatProcessor
    requires(T dependent_instance, ResultFilesPaths paths) {
        {
            dependent_instance.get(std::move(paths))
        } -> std::same_as<std::variant<typename T::type, PyExceptionInfo>>;
    });

template <class T>
concept is_plugin_wrapper =
    implements_wrapper_interface<T> && container_constructible<T> &&
    implements_wrapper_get<T>;

#endif  // !BASE_PLUGIN_WRAPPER_H
