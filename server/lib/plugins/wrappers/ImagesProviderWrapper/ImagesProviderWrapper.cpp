#include "ImagesProviderWrapper.hpp"

ImagesProviderWrapper::ImagesProviderWrapper(BasePluginWrapper &&base)
    : BasePluginWrapper(std::move(base)) {
}

auto ImagesProviderWrapper::build(Container container)
    -> std::variant<ImagesProviderWrapper, PyExceptionInfo> {
    auto base_or_error = BasePluginWrapper::build(std::move(container));
    if (std::holds_alternative<PyExceptionInfo>(base_or_error)) {
        return std::get<PyExceptionInfo>(base_or_error);
    }
    auto base = std::move(std::get<BasePluginWrapper>(base_or_error));
    return ImagesProviderWrapper(std::move(base));
}

auto ImagesProviderWrapper::get(const std::string &word, uint64_t batch_size)
    -> std::variant<ImagesProviderWrapper::type, PyExceptionInfo> {
    return {};
}
