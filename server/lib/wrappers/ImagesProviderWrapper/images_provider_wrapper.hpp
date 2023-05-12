#include "IPluginWrapper.hpp"

#include <string>
#include <utility>
#include <vector>

class ImagesProviderWrapper
    : public IPluginWrapper<std::pair<std::vector<std::string>, std::string>> {
};
