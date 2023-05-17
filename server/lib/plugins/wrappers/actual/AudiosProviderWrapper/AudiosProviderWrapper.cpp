#include "AudiosProviderWrapper.hpp"
#include "BasePluginWrapper.hpp"
#include "PyExceptionInfo.hpp"
#include "spdlog/common.h"
#include "spdlog/spdlog.h"
#include <algorithm>
#include <boost/python/extract.hpp>
#include <boost/python/import.hpp>
#include <cstdint>
#include <nlohmann/json_fwd.hpp>
#include <optional>
#include <string>
#include <utility>
#include <variant>
#include <vector>

auto AudiosProviderWrapper::AudiosProvidesFunctions::build(
    const boost::python::object &module)
    -> std::variant<AudiosProvidesFunctions, PyExceptionInfo> {
    auto plugin_container = AudiosProvidesFunctions();
    try {
        plugin_container.get = module.attr("get");
    } catch (const boost::python::error_already_set &) {
        return PyExceptionInfo::build().value();
    }
    return plugin_container;
}

AudiosProviderWrapper::AudiosProviderWrapper(const AudiosProviderWrapper &other)
    : BasePluginWrapper(other.name(), other.common_),
      specifics_(other.specifics_) {
}

AudiosProviderWrapper::AudiosProviderWrapper(BasePluginWrapper &&base)
    : BasePluginWrapper(std::move(base)) {
}

auto AudiosProviderWrapper::build(const std::string           &name,
                                  const boost::python::object &module)
    -> std::variant<AudiosProviderWrapper, PyExceptionInfo> {
    auto base_or_error = BasePluginWrapper::build(name, module);
    if (std::holds_alternative<PyExceptionInfo>(base_or_error)) {
        return std::get<PyExceptionInfo>(base_or_error);
    }
    auto base = std::move(std::get<BasePluginWrapper>(base_or_error));

    auto specifics_or_error = AudiosProvidesFunctions::build(module);
    if (std::holds_alternative<PyExceptionInfo>(specifics_or_error)) {
        return std::get<PyExceptionInfo>(specifics_or_error);
    }
    auto specifics     = std::get<AudiosProvidesFunctions>(specifics_or_error);

    auto wrapper       = AudiosProviderWrapper(std::move(base));
    wrapper.specifics_ = specifics;
    return wrapper;
}

auto AudiosProviderWrapper::get(const std::string &word, uint64_t batch_size)
    -> std::variant<AudiosProviderWrapper::type, PyExceptionInfo> {
    std::vector<AudioInfo> test;
    return std::make_pair(test, "");
}
