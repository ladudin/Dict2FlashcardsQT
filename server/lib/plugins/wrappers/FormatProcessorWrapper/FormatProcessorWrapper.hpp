#ifndef FORMAT_PROCESSOR_WRAPPER_H
#define FORMAT_PROCESSOR_WRAPPER_H

#include "IPluginWrapper.hpp"

#include <filesystem>
#include <string>
#include <utility>
#include <vector>

class FormatProcessorWrapper : public IPluginWrapper<std::string> {
 public:
    explicit FormatProcessorWrapper(Container container);

    auto get(ResultFilesPaths &&paths) -> FormatProcessorWrapper::type;
    auto load() -> void override;
    auto get_config_description() -> nlohmann::json override;
    auto get_default_config() -> nlohmann::json override;
    auto set_config(nlohmann::json &&new_config) -> nlohmann::json override;
    auto unload() -> void override;

    FormatProcessorWrapper(const FormatProcessorWrapper &) = default;
    FormatProcessorWrapper(FormatProcessorWrapper &&)      = default;
    auto operator=(const FormatProcessorWrapper &)
        -> FormatProcessorWrapper & = default;
    auto operator=(FormatProcessorWrapper &&)
        -> FormatProcessorWrapper & = default;
};

#endif
