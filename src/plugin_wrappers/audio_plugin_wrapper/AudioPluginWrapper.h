#ifndef DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_AUDIO_PLUGIN_WRAPPER_AUDIOPLUGINWRAPPER_H
#define DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_AUDIO_PLUGIN_WRAPPER_AUDIOPLUGINWRAPPER_H

#include <string>
#include <vector>

#include "../basic_plugin_wrapper/BasicPluginWrapper.h"
#include "../plugin_wrapper_interfaces/IMultimediaPluginWrapper.h"

class AudioPluginWrapper : public BasicPluginWrapper, virtual public IMultimediaPluginWrapper {
    std::vector<std::string> get(const std::string& word, size_t count) override;
};

std::string AudioPluginWrapper::BasicPluginWrapper::plugin_type_("Audio");

#endif  // DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_AUDIO_PLUGIN_WRAPPER_AUDIOPLUGINWRAPPER_H
