#ifndef AUDIOS_PROVIDER_WRAPPER_H
#define AUDIOS_PROVIDER_WRAPPER_H

#include "IPluginWrapper.hpp"
#include <string>
#include <utility>
#include <vector>

class AudiosProviderWrapper
    : public IPluginWrapper<std::pair<std::vector<std::string>, std::string>> {
};

#endif  // !AUDIOS_PROVIDER_WRAPPER_H
