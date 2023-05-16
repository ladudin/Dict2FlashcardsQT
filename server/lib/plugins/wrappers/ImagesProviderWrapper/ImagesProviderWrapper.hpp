#ifndef IMAGES_PROVIDER_WRAPPER_H
#define IMAGES_PROVIDER_WRAPPER_H

#include <nlohmann/json_fwd.hpp>
#include <string>
#include <utility>
#include <variant>
#include <vector>

#include "BasePluginWrapper.hpp"
#include "PyExceptionInfo.hpp"

class ImagesProviderWrapper : public BasePluginWrapper {
 public:
    using type = std::pair<std::vector<std::string>, std::string>;

    static auto build(Container container)
        -> std::variant<ImagesProviderWrapper, PyExceptionInfo>;

    auto get(const std::string &word, uint64_t batch_size)
        -> std::variant<ImagesProviderWrapper::type, PyExceptionInfo>;

 private:
    explicit ImagesProviderWrapper(BasePluginWrapper &&base);
};

static_assert(is_plugin_wrapper<ImagesProviderWrapper>);

#endif
