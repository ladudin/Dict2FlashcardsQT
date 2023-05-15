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

class AudiosProviderWrapper
    : public BasePluginWrapper<std::pair<std::vector<AudioInfo>, std::string>> {
 public:
    auto get(const std::string &word, uint64_t batch_size)
        -> std::variant<AudiosProviderWrapper::type, PyExceptionInfo>;
};

static_assert(is_plugin_wrapper<AudiosProviderWrapper>);

#endif  // !AUDIOS_PROVIDER_WRAPPER_H
