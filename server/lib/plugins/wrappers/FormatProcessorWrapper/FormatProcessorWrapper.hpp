#ifndef FORMAT_PROCESSOR_WRAPPER_H
#define FORMAT_PROCESSOR_WRAPPER_H

#include <filesystem>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <utility>
#include <vector>

#include "BasePluginWrapper.hpp"
#include "PyExceptionInfo.hpp"

class FormatProcessorWrapper : public BasePluginWrapper {
 public:
    using type = std::string;

    static auto build(Container container)
        -> std::variant<FormatProcessorWrapper, PyExceptionInfo>;

    auto get(ResultFilesPaths &&paths)
        -> std::variant<FormatProcessorWrapper::type, PyExceptionInfo>;

 private:
    explicit FormatProcessorWrapper(BasePluginWrapper &&base);
};

static_assert(is_plugin_wrapper<FormatProcessorWrapper>);

#endif
