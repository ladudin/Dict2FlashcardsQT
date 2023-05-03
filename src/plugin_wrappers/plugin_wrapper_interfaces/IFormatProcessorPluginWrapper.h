#ifndef DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_PLUGIN_WRAPPER_INTERFACES_IFORMATPROCESSORPLUGINWRAPPER_H
#define DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_PLUGIN_WRAPPER_INTERFACES_IFORMATPROCESSORPLUGINWRAPPER_H

#include "../plugin_wrapper_interfaces/IBasicPluginWrapper.h"

#include <string>

class IFormatProcessorPluginWrapper : virtual public IBasicPluginWrapper {
 public:
    virtual void save(const std::string &cards_path,
                      const std::string &links_path,
                      const std::string &media_path) = 0;
};


#endif  // DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_PLUGIN_WRAPPER_INTERFACES_IFORMATPROCESSORPLUGINWRAPPER_H
