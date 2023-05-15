#ifndef IBASICPLUGINWRAPPER_H
#define IBASICPLUGINWRAPPER_H

#include <string>
#include <vector>

#include "LoadResult.h"

struct IBasicPluginWrapper {
    virtual ~IBasicPluginWrapper()                                   = default;
    virtual std::string init(const std::string &plugin_name)         = 0;
    virtual std::pair<std::string, std::string> get_default_config() = 0;
    virtual std::pair<std::string, std::string> get_default_scheme() = 0;
    virtual std::pair<std::string, std::string>
    set_config(const std::string &new_config)                     = 0;
    virtual std::pair<LoadResult, std::string> list_plugins()     = 0;
    virtual std::pair<LoadResult, std::string> load_new_plugins() = 0;
};

#endif  // IBASICPLUGINWRAPPER_H