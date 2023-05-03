#ifndef DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_MULTIMEDIA_PLUGIN_WRAPPER_MULTIMEDIAPLUGINWRAPPER_H
#define DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_MULTIMEDIA_PLUGIN_WRAPPER_MULTIMEDIAPLUGINWRAPPER_H

#include <string>
#include <vector>

#include "../basic_plugin_wrapper/BasicPluginWrapper.h"
#include "../plugin_wrapper_interfaces/IMultimediaPluginWrapper.h"

class MultimediaPluginWrapper : public BasicPluginWrapper, virtual public IMultimediaPluginWrapper {
    MultimediaPluginWrapper(std::shared_ptr<IRequestable>)
    std::vector<std::string> get(const std::string& word, size_t count) override;
};

#endif  // DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_MULTIMEDIA_PLUGIN_WRAPPER_MULTIMEDIAPLUGINWRAPPER_H
