#include "ImagesProviderWrapper.hpp"

ImagesProviderWrapper::ImagesProviderWrapper(BasePluginWrapper &&base)
    : BasePluginWrapper(std::move(base)) {
}

auto ImagesProviderWrapper::get(const std::string &word, uint64_t batch_size)
    -> std::variant<ImagesProviderWrapper::type, PyExceptionInfo> {
    return {};
}
