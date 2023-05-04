#ifndef DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_SENTENCE_PLUGIN_WRAPPER_SENTENCEPLUGINWRAPPER_H
#define DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_SENTENCE_PLUGIN_WRAPPER_SENTENCEPLUGINWRAPPER_H

#include <memory>
#include <string>
#include <vector>

#include "plugin_wrappers/basic_plugin_wrapper/BasicPluginWrapper.h"
#include "plugin_wrappers/plugin_wrapper_interfaces/IMultimediaPluginWrapper.h"

class SentencePluginWrapper : public BasicPluginWrapper,
                              virtual public IMultimediaPluginWrapper {
 public:
    SentencePluginWrapper(std::shared_ptr<IRequestable> connection);
    std::vector<std::string> get(const std::string &word,
                                 size_t             count) override;
};

#endif  // DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_SENTENCE_PLUGIN_WRAPPER_SENTENCEPLUGINWRAPPER_H
