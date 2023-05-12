#include "IPluginWrapper.hpp"

#include <string>
#include <utility>
#include <vector>

class AudiosProviderWrapper
    : public IPluginWrapper<std::pair<std::vector<std::string>, std::string>> {
};
