#include "SentencesProviderWrapper.hpp"
#include "BasePluginWrapper.hpp"
#include <boost/python/extract.hpp>
#include <boost/python/import.hpp>

auto SentencesProviderWrapper::SentencesProvidersFunctions::build(
    const boost::python::object &module)
    -> std::variant<SentencesProvidersFunctions, PyExceptionInfo> {
    auto plugin_container = SentencesProvidersFunctions();
    try {
        plugin_container.get = module.attr("get");
    } catch (const boost::python::error_already_set &) {
        return PyExceptionInfo::build().value();
    }
    return plugin_container;
}

SentencesProviderWrapper::SentencesProviderWrapper(BasePluginWrapper &&base)
    : BasePluginWrapper(std::move(base)) {
}

SentencesProviderWrapper::SentencesProviderWrapper(
    const SentencesProviderWrapper &other)
    : BasePluginWrapper(other.name(), other.common_),
      specifics_(other.specifics_) {
}

auto SentencesProviderWrapper::get(const std::string &word,
                                   uint64_t           batch_size,
                                   bool               restart) -> std::
    variant<SentencesProviderWrapper::type, std::string, PyExceptionInfo> {
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
            auto sentences     = json_res[0].get<std::vector<std::string>>();
            auto error_message = json_res[1].get<std::string>();
            return std::make_pair(sentences, error_message);
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
    std::vector<std::string> empty(0);
    return std::make_pair(empty, "");
}

auto SentencesProviderWrapper::build(const std::string           &name,
                                     const boost::python::object &module)
    -> std::variant<SentencesProviderWrapper, PyExceptionInfo> {
    auto base_or_error = BasePluginWrapper::build(name, module);
    if (std::holds_alternative<PyExceptionInfo>(base_or_error)) {
        return std::get<PyExceptionInfo>(base_or_error);
    }
    auto base = std::move(std::get<BasePluginWrapper>(base_or_error));

    auto specifics_or_error = SentencesProvidersFunctions::build(module);
    if (std::holds_alternative<PyExceptionInfo>(specifics_or_error)) {
        return std::get<PyExceptionInfo>(specifics_or_error);
    }
    auto specifics = std::get<SentencesProvidersFunctions>(specifics_or_error);

    auto wrapper   = SentencesProviderWrapper(std::move(base));
    wrapper.specifics_ = specifics;
    return wrapper;
}
