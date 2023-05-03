#ifndef DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_BASIC_PLUGIN_WRAPPER_BASICPLUGINWRAPPER_H
#define DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_BASIC_PLUGIN_WRAPPER_BASICPLUGINWRAPPER_H

#include <string>
#include <vector>
#include <memory>

#include "../../data_providers/irequestable/IRequestable.h"
#include "../plugin_wrapper_interfaces/IBasicPluginWrapper.h"

class BasicPluginWrapper : virtual public IBasicPluginWrapper {
 public:
    BasicPluginWrapper(std::shared_ptr<IRequestable> connection);
    ~BasicPluginWrapper();
    bool                     init(std::string name) override;
    std::string              get_default_config() override;
    std::string              get_default_scheme() override;
    void                     set_config(const std::string &new_config) override;
    std::vector<std::string> list_plugins() override;
    std::vector<std::string> load_new_plugins() override;
 private:
    std::shared_ptr<IRequestable> connection_;
    static std::string plugin_type_;
};

#endif  // DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_BASIC_PLUGIN_WRAPPER_BASICPLUGINWRAPPER_H
