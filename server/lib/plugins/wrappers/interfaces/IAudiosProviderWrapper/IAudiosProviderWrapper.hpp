#ifndef I_AUDIOS_PROVIDER_WRAPPER_H
#define I_AUDIOS_PROVIDER_WRAPPER_H

#include <string>
#include <utility>
#include <vector>

#include "IPluginWrapper.hpp"

struct AudioInfo {
    std::string audio;
    std::string additional_info;
};

class IAudiosProviderWrapper : public virtual IPluginWrapper {
 public:
    using type = std::pair<std::vector<AudioInfo>, std::string>;

    virtual auto get(const std::string &word, uint64_t batch_size)
        -> std::variant<type, PyExceptionInfo> = 0;
};

#endif  // !I_AUDIOS_PROVIDER_WRAPPER
