#include "AudiosProviderWrapper.hpp"
#include "BasePluginWrapper.hpp"
#include "PyExceptionInfo.hpp"
#include <boost/python/extract.hpp>
#include <boost/python/import.hpp>
#include <cstdint>
#include <nlohmann/json_fwd.hpp>
#include <optional>
#include <string>
#include <utility>
#include <variant>
#include <vector>

AudiosProviderWrapper::AudiosProviderWrapper(BasePluginWrapper &&base)
    : BasePluginWrapper(std::move(base)) {
}

auto AudiosProviderWrapper::build(Container container)
    -> std::variant<AudiosProviderWrapper, PyExceptionInfo> {
    auto base_or_error = BasePluginWrapper::build(std::move(container));
    if (std::holds_alternative<PyExceptionInfo>(base_or_error)) {
        return std::get<PyExceptionInfo>(base_or_error);
    }
    auto base = std::move(std::get<BasePluginWrapper>(base_or_error));
    return AudiosProviderWrapper(std::move(base));
}

auto AudiosProviderWrapper::get(const std::string &word, uint64_t batch_size)
    -> std::variant<AudiosProviderWrapper::type, PyExceptionInfo> {
    std::vector<AudioInfo> test;
    return std::make_pair(test, "");
}
