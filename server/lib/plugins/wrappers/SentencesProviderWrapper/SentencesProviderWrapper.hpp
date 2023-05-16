#ifndef SENTENCES_PROVIDER_WRAPPER_H
#define SENTENCES_PROVIDER_WRAPPER_H

#include <cstdint>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <utility>
#include <vector>

#include "BasePluginWrapper.hpp"
#include "PyExceptionInfo.hpp"

class SentencesProviderWrapper : public BasePluginWrapper {
 public:
    using type = std::pair<std::vector<std::string>, std::string>;

    explicit SentencesProviderWrapper(BasePluginWrapper &&base);

    auto get(const std::string &word, uint64_t batch_size)
        -> std::variant<SentencesProviderWrapper::type, PyExceptionInfo>;
};

static_assert(is_plugin_wrapper<SentencesProviderWrapper>);

#endif
