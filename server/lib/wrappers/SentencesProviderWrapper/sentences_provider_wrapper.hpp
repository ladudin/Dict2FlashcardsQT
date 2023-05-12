#include "IPluginWrapper.hpp"
#include <string>
#include <utility>
#include <vector>

class SentencesProviderWrapper
    : public IPluginWrapper<std::pair<std::vector<std::string>, std::string>> {
};
