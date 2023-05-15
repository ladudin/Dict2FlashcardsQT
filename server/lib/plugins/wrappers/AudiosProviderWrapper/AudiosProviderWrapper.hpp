#ifndef AUDIOS_PROVIDER_WRAPPER_H
#define AUDIOS_PROVIDER_WRAPPER_H

#include "Container.hpp"
#include "IPluginWrapper.hpp"
#include "PyExceptionInfo.hpp"
#include <cstdint>
#include <string>
#include <utility>
#include <variant>
#include <vector>

class AudiosProviderWrapper
    : public IPluginWrapper<std::pair<std::vector<std::string>, std::string>> {
 public:
    static auto build(std::string name, Container container)
        -> std::variant<AudiosProviderWrapper, PyExceptionInfo>;

    [[nodiscard]] auto name() const -> const std::string & override;
    auto               get(const std::string &word, uint64_t batch_size)
        -> std::variant<AudiosProviderWrapper::type, PyExceptionInfo>;
    auto load() -> std::optional<PyExceptionInfo> override;
    auto unload() -> std::optional<PyExceptionInfo> override;
    auto get_config_description()
        -> std::variant<PyExceptionInfo, nlohmann::json> override;
    auto get_default_config()
        -> std::variant<PyExceptionInfo, nlohmann::json> override;
    auto set_config(nlohmann::json &&new_config)
        -> std::variant<PyExceptionInfo, nlohmann::json> override;

 private:
    explicit AudiosProviderWrapper(std::string &&name, Container &&container);

    std::string    name_;
    Container      container_;
    nlohmann::json config_;
};

static_assert(is_plugin_wrapper<AudiosProviderWrapper>);

#endif  // !AUDIOS_PROVIDER_WRAPPER_H
