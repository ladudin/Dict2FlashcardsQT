#ifndef SENTENCES_PROVIDER_WRAPPER_H
#define SENTENCES_PROVIDER_WRAPPER_H

#include "IPluginWrapper.hpp"
#include <string>
#include <utility>
#include <vector>

class SentencesProviderWrapper
    : public IPluginWrapper<std::pair<std::vector<std::string>, std::string>> {
};

#endif
