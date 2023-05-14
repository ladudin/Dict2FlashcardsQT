#ifndef SENTENCES_PROVIDER_WRAPPER_H
#define SENTENCES_PROVIDER_WRAPPER_H

#include "Container.hpp"
#include "IPluginWrapper.hpp"
#include "PyExceptionInfo.hpp"
#include <cstdint>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <utility>
#include <vector>

class SentencesProviderWrapper
    : public IPluginWrapper<std::pair<std::vector<std::string>, std::string>> {
 public:
    static auto build(Container containter)
        -> std::variant<SentencesProviderWrapper, PyExceptionInfo>;

    auto get(const std::string &word, uint64_t batch_size)
        -> std::variant<SentencesProviderWrapper::type, PyExceptionInfo>;
    auto load() -> std::optional<PyExceptionInfo> override;
    auto unload() -> std::optional<PyExceptionInfo> override;
    auto get_config_description()
        -> std::variant<PyExceptionInfo, nlohmann::json> override;
    auto get_default_config()
        -> std::variant<PyExceptionInfo, nlohmann::json> override;
    auto set_config(nlohmann::json &&new_config)
        -> std::variant<PyExceptionInfo, nlohmann::json> override;

 private:
    explicit SentencesProviderWrapper(Container &&container);

    Container      container_;
    nlohmann::json config_;
};

static_assert(is_plugin_wrapper<SentencesProviderWrapper>);

#endif
