#ifndef DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_SENTENCE_PLUGIN_WRAPPER_SENTENCEPLUGINWRAPPER_H
#define DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_SENTENCE_PLUGIN_WRAPPER_SENTENCEPLUGINWRAPPER_H

#include <string>
#include <vector>

#include "../basic_plugin_wrapper/BasicPluginWrapper.h"
#include "../plugin_wrapper_interfaces/IMultimediaPluginWrapper.h"

class SentencePluginWrapper : public BasicPluginWrapper, virtual public IMultimediaPluginWrapper {
    std::vector<std::string> get(const std::string& word, size_t count) override;
};

std::string SentencePluginWrapper::BasicPluginWrapper::plugin_type_("Sentence");

#endif  // DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_SENTENCE_PLUGIN_WRAPPER_SENTENCEPLUGINWRAPPER_H
