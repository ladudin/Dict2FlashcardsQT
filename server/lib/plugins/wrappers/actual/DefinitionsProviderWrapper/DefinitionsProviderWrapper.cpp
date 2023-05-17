#include "DefinitionsProviderWrapper.hpp"
#include "PyExceptionInfo.hpp"
#include "pyerrors.h"
#include "pythonrun.h"
#include <boost/python/exec.hpp>
#include <boost/python/import.hpp>
#include <exception>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <utility>
#include <vector>

auto DefinitionsProviderWrapper::DefinitionsProvidersFunctions::build(
    const boost::python::object &module)
    -> std::variant<DefinitionsProvidersFunctions, PyExceptionInfo> {
    auto plugin_container = DefinitionsProvidersFunctions();
    try {
        plugin_container.get = module.attr("get");
    } catch (const boost::python::error_already_set &) {
        return PyExceptionInfo::build().value();
    }
    return plugin_container;
}

DefinitionsProviderWrapper::DefinitionsProviderWrapper(BasePluginWrapper &&base)
    : BasePluginWrapper(std::move(base)) {
}

DefinitionsProviderWrapper::DefinitionsProviderWrapper(
    const DefinitionsProviderWrapper &other)
    : BasePluginWrapper(other.name(), other.common_),
      specifics_(other.specifics_) {
}

auto DefinitionsProviderWrapper::build(const std::string           &name,
                                       const boost::python::object &module)
    -> std::variant<DefinitionsProviderWrapper, PyExceptionInfo> {
    auto base_or_error = BasePluginWrapper::build(name, module);
    if (std::holds_alternative<PyExceptionInfo>(base_or_error)) {
        return std::get<PyExceptionInfo>(base_or_error);
    }
    auto base = std::move(std::get<BasePluginWrapper>(base_or_error));

    auto specifics_or_error = DefinitionsProvidersFunctions::build(module);
    if (std::holds_alternative<PyExceptionInfo>(specifics_or_error)) {
        return std::get<PyExceptionInfo>(specifics_or_error);
    }
    auto specifics =
        std::get<DefinitionsProvidersFunctions>(specifics_or_error);

    auto wrapper       = DefinitionsProviderWrapper(std::move(base));
    wrapper.specifics_ = specifics;
    return wrapper;
}

auto DefinitionsProviderWrapper::get(const std::string &word,
                                     const std::string &filter_query,
                                     uint64_t           batch_size,
                                     bool               restart) -> std::
    variant<DefinitionsProviderWrapper::type, std::string, PyExceptionInfo> {
    if (restart) {
        auto found_item = generators_.find(word);
        if (found_item != generators_.end()) {
            generators_.erase(found_item);
        }
    }
    if (generators_.find(word) == generators_.end()) {
        try {
            boost::python::object test = specifics_.get(word);
            generators_[word]          = test;
            generators_[word]->attr("__next__")();
        } catch (const boost::python::error_already_set &) {
            generators_.erase(generators_.find(word));
            return PyExceptionInfo::build().value();
        }
    }

    try {
        boost::python::object py_json       = boost::python::import("json");
        boost::python::object py_json_dumps = py_json.attr("dumps");

        boost::python::object py_res =
            generators_[word]->attr("send")(batch_size);
        boost::python::object py_json_res = py_json_dumps(py_res);

        std::string str_res = boost::python::extract<std::string>(py_json_res);
        nlohmann::json json_res = nlohmann::json::parse(str_res);

        try {
            auto error_message = json_res[1].get<std::string>();
            auto cards         = json_res[0].get<std::vector<Card>>();
            // TODO(QUERY LANGUAGE): ЗДЕСЬ БУДЕТ ФИЛЬТР ПО ЗАПРОСУ
            return std::make_pair(cards, error_message);
        } catch (const std::exception &error) {
            return error.what();
        }
    } catch (boost::python::error_already_set &) {
        auto        py_exc_info    = PyExceptionInfo::build().value();
        const auto &exception_type = py_exc_info.last_type();

        if (exception_type == "<class 'StopIteration'>") {
            return {};
        }
        return py_exc_info;
    }
    std::vector<Card> empty(0);
    return std::make_pair(empty, "");
}

auto DefinitionsProviderWrapper::get_dictionary_scheme()
    -> std::variant<nlohmann::json, PyExceptionInfo> {
    return {};
}
