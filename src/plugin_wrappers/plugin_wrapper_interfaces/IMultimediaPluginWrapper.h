#ifndef DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_PLUGIN_WRAPPER_INTERFACES_IMULTIMEDIAPLUGINWRAPPER_H
#define DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_PLUGIN_WRAPPER_INTERFACES_IMULTIMEDIAPLUGINWRAPPER_H

#include "plugin_wrappers/plugin_wrapper_interfaces/IBasicPluginWrapper.h"

#include <string>
#include <vector>

class IMultimediaPluginWrapper : virtual public IBasicPluginWrapper {
 public:
    virtual std::vector<std::string> get(const std::string &word,
                                         size_t             count) = 0;
};

#endif  // DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_PLUGIN_WRAPPER_INTERFACES_IMULTIMEDIAPLUGINWRAPPER_H
