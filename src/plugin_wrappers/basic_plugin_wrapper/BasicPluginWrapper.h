#ifndef DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_BASIC_PLUGIN_WRAPPER_BASICPLUGINWRAPPER_H
#define DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_BASIC_PLUGIN_WRAPPER_BASICPLUGINWRAPPER_H

#include <memory>
#include <string>
#include <variant>
#include <vector>

#include "containers/ExceptionInfo.h"
#include "data_providers/irequestable/IRequestable.h"
#include "plugin_wrappers/plugin_wrapper_interfaces/IBasicPluginWrapper.h"

class BasicPluginWrapper : virtual public IBasicPluginWrapper {
 public:
    BasicPluginWrapper(std::shared_ptr<IRequestable> connection,
                       std::string                   plugin_type);
    Result<std::monostate> init(const std::string &plugin_name) override;
    std::variant<std::string, ExceptionInfo> get_default_config() override;
    std::variant<std::string, ExceptionInfo> get_default_scheme() override;
    std::variant<std::string, ExceptionInfo>
    set_config(const std::string &new_config) override;
    std::variant<LoadResult, ExceptionInfo> list_plugins() override;
    std::variant<LoadResult, ExceptionInfo> load_new_plugins() override;

 protected:
    std::shared_ptr<IRequestable> connection_;
    std::string                   plugin_type_;
};

// https://en.cppreference.com/w/cpp/utility/variant/visit
//template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
// explicit deduction guide (not needed as of C++20)
//template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

template<typename...Func>
struct overload : Func... {
    using Func::operator()...;
};

template<typename...Func> overload(Func...) -> overload<Func...>;

#endif  // DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_BASIC_PLUGIN_WRAPPER_BASICPLUGINWRAPPER_H
