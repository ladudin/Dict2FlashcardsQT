#include "SentencesProviderWrapper.hpp"
#include <boost/python/extract.hpp>
#include <boost/python/import.hpp>

auto SentencesProviderWrapper::SentencesProvidersFunctions::build(
    boost::python::object module)
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

auto SentencesProviderWrapper::build(const std::string    &name,
                                     boost::python::object module)
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

auto SentencesProviderWrapper::get(const std::string &word, uint64_t batch_size)
    -> std::variant<SentencesProviderWrapper::type, PyExceptionInfo> {
    return {};
}
