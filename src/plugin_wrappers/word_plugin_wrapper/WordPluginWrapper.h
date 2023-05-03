#ifndef DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_WORD_PLUGIN_WRAPPER_WORDPLUGINWRAPPER_H
#define DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_WORD_PLUGIN_WRAPPER_WORDPLUGINWRAPPER_H

#include <string>
#include <vector>

#include "../basic_plugin_wrapper/BasicPluginWrapper.h"
#include "../plugin_wrapper_interfaces/IWordPluginWrapper.h"

class WordPluginWrapper : public BasicPluginWrapper, virtual public IWordPluginWrapper {
 public:
    std::vector<Card> get(const std::string &word) override;
    std::string       get_dict_scheme() override;
};

std::string WordPluginWrapper::BasicPluginWrapper::plugin_type_("Word");

#endif  // DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_WORD_PLUGIN_WRAPPER_WORDPLUGINWRAPPER_H