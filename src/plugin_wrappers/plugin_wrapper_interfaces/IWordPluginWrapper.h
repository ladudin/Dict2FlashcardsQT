#ifndef DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_PLUGIN_WRAPPER_INTERFACES_IWORDPLUGINWRAPPER_H
#define DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_PLUGIN_WRAPPER_INTERFACES_IWORDPLUGINWRAPPER_H

#include "../plugin_wrapper_interfaces/IBasicPluginWrapper.h"

#include <string>

class IWordPluginWrapper : virtual public IBasicPluginWrapper {
 public:
    virtual std::vector<Card> get(const std::string &word) = 0;
    virtual std::string       get_dict_scheme()            = 0;
};

#endif  // DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_PLUGIN_WRAPPER_INTERFACES_IWORDPLUGINWRAPPER_H
