#ifndef BASICPLUGINWRAPPER_H
#define BASICPLUGINWRAPPER_H

#include <memory>
#include <string>
#include <vector>

#include "IRequestable.h"
#include "interfaces/IBasicPluginWrapper.h"

class BasicPluginWrapper : virtual public IBasicPluginWrapper {
 public:
    BasicPluginWrapper(std::shared_ptr<IRequestable> connection,
                       std::string                   plugin_type);
    std::string init(const std::string &plugin_name) override;
    std::pair<std::string, std::string> get_default_config() override;
    std::pair<std::string, std::string> get_default_scheme() override;
    std::pair<std::string, std::string>
    set_config(const std::string &new_config) override;
    virtual std::pair<LoadResult, std::string> list_plugins() override;
    virtual std::pair<LoadResult, std::string> load_new_plugins() override;

 protected:
    std::shared_ptr<IRequestable> connection_;
    std::string                   plugin_type_;
};

#endif  // BASICPLUGINWRAPPER_H
