#ifndef AUDIOS_PROVIDER_WRAPPER_H
#define AUDIOS_PROVIDER_WRAPPER_H

#include "BasePluginWrapper.hpp"
#include "PyExceptionInfo.hpp"
#include <cstdint>
#include <string>
#include <utility>
#include <variant>
#include <vector>

struct AudioInfo {
    std::string audio;
    std::string additional_info;
};

class AudiosProviderWrapper : public BasePluginWrapper {
 public:
    using type = std::pair<std::vector<AudioInfo>, std::string>;

    static auto build(Container container)
        -> std::variant<AudiosProviderWrapper, PyExceptionInfo>;

    auto get(const std::string &word, uint64_t batch_size)
        -> std::variant<AudiosProviderWrapper::type, PyExceptionInfo>;

 private:
    explicit AudiosProviderWrapper(BasePluginWrapper &&base);
};

static_assert(is_plugin_wrapper<AudiosProviderWrapper>);

#endif  // !AUDIOS_PROVIDER_WRAPPER_H
