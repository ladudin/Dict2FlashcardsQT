#ifndef DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_PLUGIN_WRAPPER_INTERFACES_IBASICPLUGINWRAPPER_H
#define DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_PLUGIN_WRAPPER_INTERFACES_IBASICPLUGINWRAPPER_H

#include <map>
#include <string>
#include <variant>
#include <vector>

#include "containers/ExceptionInfo.h"

struct LoadResult {
    std::vector<std::string> success;
    std::vector<std::string> fail;
};

inline bool operator==(const LoadResult &lhs, const LoadResult &rhs) {
    return lhs.success == rhs.success && lhs.fail == rhs.fail;
}

class IBasicPluginWrapper {
 public:
    virtual ~IBasicPluginWrapper()                            = default;
    virtual Result<std::monostate> init(const std::string &plugin_name) = 0;
    virtual std::variant<std::string, ExceptionInfo> get_default_config() = 0;
    virtual std::variant<std::string, ExceptionInfo> get_default_scheme() = 0;
    virtual std::variant<std::string, ExceptionInfo>
    set_config(const std::string &new_config)                          = 0;
    virtual std::variant<LoadResult, ExceptionInfo> list_plugins()     = 0;
    virtual std::variant<LoadResult, ExceptionInfo> load_new_plugins() = 0;
};

#endif  // DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_PLUGIN_WRAPPER_INTERFACES_IBASICPLUGINWRAPPER_H
