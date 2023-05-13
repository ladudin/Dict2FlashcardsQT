#ifndef FORMAT_PROCESSOR_WRAPPER_H
#define FORMAT_PROCESSOR_WRAPPER_H

#include "IPluginWrapper.hpp"

#include <string>
#include <utility>
#include <vector>

class FormatProcessorWrapper
    : public IPluginWrapper<std::pair<std::vector<std::string>, std::string>> {
};

#endif
