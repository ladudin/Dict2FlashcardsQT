#ifndef DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_WORD_PLUGIN_WRAPPER_WORDPLUGINWRAPPER_H
#define DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_WORD_PLUGIN_WRAPPER_WORDPLUGINWRAPPER_H

#include <string>
#include <vector>
#include <memory>

#include "../basic_plugin_wrapper/BasicPluginWrapper.h"
#include "../plugin_wrapper_interfaces/IWordPluginWrapper.h"

class WordPluginWrapper : public BasicPluginWrapper, virtual public IWordPluginWrapper {
 public:
    WordPluginWrapper(std::shared_ptr<IRequestable> connection);
    std::vector<Card> get(const std::string &word) override;
    std::string       get_dict_scheme() override;
};

#endif  // DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_WORD_PLUGIN_WRAPPER_WORDPLUGINWRAPPER_H