#ifndef FORMAT_PROCESSOR_WRAPPER_H
#define FORMAT_PROCESSOR_WRAPPER_H

#include <filesystem>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <utility>
#include <vector>

#include "Container.hpp"
#include "IPluginWrapper.hpp"
#include "PyExceptionInfo.hpp"

class FormatProcessorWrapper : public IPluginWrapper<std::string> {
 public:
    static auto build(Container container)
        -> std::variant<FormatProcessorWrapper, PyExceptionInfo>;

    auto get(ResultFilesPaths &&paths)
        -> std::variant<FormatProcessorWrapper::type, PyExceptionInfo>;
    auto load() -> std::optional<PyExceptionInfo> override;
    auto unload() -> std::optional<PyExceptionInfo> override;
    auto get_config_description()
        -> std::variant<PyExceptionInfo, nlohmann::json> override;
    auto get_default_config()
        -> std::variant<PyExceptionInfo, nlohmann::json> override;
    auto set_config(nlohmann::json &&new_config)
        -> std::variant<PyExceptionInfo, nlohmann::json> override;

 private:
    explicit FormatProcessorWrapper(Container &&container);

    Container      container_;
    nlohmann::json config_;
};

static_assert(is_plugin_wrapper<FormatProcessorWrapper>);

#endif
