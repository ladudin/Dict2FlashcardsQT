#include "ImagesProviderWrapper.hpp"
#include <boost/python/extract.hpp>
#include <boost/python/import.hpp>

auto ImagesProviderWrapper::ImagesProvidersFunctions::build(
    const boost::python::object &module)
    -> std::variant<ImagesProvidersFunctions, PyExceptionInfo> {
    auto plugin_container = ImagesProvidersFunctions();
    try {
        plugin_container.get = module.attr("get");
    } catch (const boost::python::error_already_set &) {
        return PyExceptionInfo::build().value();
    }
    return plugin_container;
}

ImagesProviderWrapper::ImagesProviderWrapper(BasePluginWrapper &&base)
    : BasePluginWrapper(std::move(base)) {
}

ImagesProviderWrapper::ImagesProviderWrapper(const ImagesProviderWrapper &other)
    : BasePluginWrapper(other.name(), other.common_),
      specifics_(other.specifics_) {
}

auto ImagesProviderWrapper::build(const std::string           &name,
                                  const boost::python::object &module)
    -> std::variant<ImagesProviderWrapper, PyExceptionInfo> {
    auto base_or_error = BasePluginWrapper::build(name, module);
    if (std::holds_alternative<PyExceptionInfo>(base_or_error)) {
        return std::get<PyExceptionInfo>(base_or_error);
    }
    auto base = std::move(std::get<BasePluginWrapper>(base_or_error));

    auto specifics_or_error = ImagesProvidersFunctions::build(module);
    if (std::holds_alternative<PyExceptionInfo>(specifics_or_error)) {
        return std::get<PyExceptionInfo>(specifics_or_error);
    }
    auto specifics     = std::get<ImagesProvidersFunctions>(specifics_or_error);

    auto wrapper       = ImagesProviderWrapper(std::move(base));
    wrapper.specifics_ = specifics;
    return wrapper;
}

auto ImagesProviderWrapper::get(const std::string &word, uint64_t batch_size)
    -> std::variant<ImagesProviderWrapper::type, PyExceptionInfo> {
    return {};
}
