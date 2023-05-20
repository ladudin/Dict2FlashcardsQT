#ifndef IAUDIOPLUGINWRAPPER_H
#define IAUDIOPLUGINWRAPPER_H

#include <string>
#include <vector>

#include "IBasicPluginWrapper.h"

using audio_vector = std::vector<std::pair<std::string, std::string>>;

struct IAudioPluginWrapper : virtual public IBasicPluginWrapper {
    virtual std::pair<audio_vector, std::string>
    get(const std::string &word, size_t batch_size, bool restart) = 0;
};

#endif  // IAUDIOPLUGINWRAPPER_H
