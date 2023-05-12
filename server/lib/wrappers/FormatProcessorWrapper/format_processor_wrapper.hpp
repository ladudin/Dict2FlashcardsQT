#include "IPluginWrapper.hpp"

#include <string>
#include <utility>
#include <vector>

class FormatProcessorWrapper
    : public IPluginWrapper<std::pair<std::vector<std::string>, std::string>> {
};
