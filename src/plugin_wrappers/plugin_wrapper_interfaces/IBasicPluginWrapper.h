#ifndef DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_PLUGIN_WRAPPER_INTERFACES_IBASICPLUGINWRAPPER_H
#define DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_PLUGIN_WRAPPER_INTERFACES_IBASICPLUGINWRAPPER_H

#include <string>
#include <map>
#include <vector>

class IBasicPluginWrapper {
 public:
    virtual ~IBasicPluginWrapper()                    = default;
    virtual void        init(std::string plugin_name) = 0;
    virtual std::string get_default_config()          = 0;
    virtual std::string get_default_scheme()          = 0;
    virtual std::map<std::string, std::string>
    set_config(const std::string &new_config)           = 0;
    virtual std::vector<std::string> list_plugins()     = 0;
    virtual std::vector<std::string> load_new_plugins() = 0;
};

#endif  // DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_PLUGIN_WRAPPER_INTERFACES_IBASICPLUGINWRAPPER_H
