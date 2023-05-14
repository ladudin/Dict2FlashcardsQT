#ifndef FORMAT_PROCESSOR_WRAPPER_H
#define FORMAT_PROCESSOR_WRAPPER_H

#include "IPluginWrapper.hpp"

#include <string>
#include <utility>
#include <vector>

class FormatProcessorWrapper
    : public IPluginWrapper<std::pair<std::vector<std::string>, std::string>> {
 public:
    explicit FormatProcessorWrapper(Container container);

    void load() override;
    auto get(std::string word) -> provided_type override;
    auto get_config_description() -> nlohmann::json override;
    auto get_default_config() -> nlohmann::json override;
    auto set_config(nlohmann::json new_config) -> nlohmann::json override;
    void unload() override;

    FormatProcessorWrapper(const FormatProcessorWrapper &) = default;
    FormatProcessorWrapper(FormatProcessorWrapper &&)      = default;
    auto operator=(const FormatProcessorWrapper &)
        -> FormatProcessorWrapper & = default;
    auto operator=(FormatProcessorWrapper &&)
        -> FormatProcessorWrapper & = default;
};

#endif
