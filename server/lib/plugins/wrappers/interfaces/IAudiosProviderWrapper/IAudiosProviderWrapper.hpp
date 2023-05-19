#ifndef I_AUDIOS_PROVIDER_WRAPPER_H
#define I_AUDIOS_PROVIDER_WRAPPER_H

#include <nlohmann/detail/macro_scope.hpp>
#include <string>
#include <utility>
#include <vector>

#include "IPluginWrapper.hpp"

struct AudioInfo {
    std::string audio;
    std::string additional_info;
};

inline void from_json(const nlohmann::json &json_arr, AudioInfo &info) {
    json_arr.at(0).get_to(info.audio);
    json_arr.at(1).get_to(info.additional_info);
}

inline void to_json(nlohmann::json &json_arr, const AudioInfo &info) {
    json_arr = {info.audio, info.additional_info};
}

// TODO(blackdeer): REWORK RETURN: ADD SUPPORT FOR LOCAL AND WEB MEDIA
class IAudiosProviderWrapper : public virtual IPluginWrapper {
 public:
    using type = std::pair<std::vector<AudioInfo>, std::string>;

    virtual auto get(const std::string &word, uint64_t batch_size, bool restart)
        -> std::variant<type, std::string, PyExceptionInfo> = 0;
};

#endif  // !I_AUDIOS_PROVIDER_WRAPPER
