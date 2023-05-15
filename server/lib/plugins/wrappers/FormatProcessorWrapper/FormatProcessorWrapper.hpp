#ifndef FORMAT_PROCESSOR_WRAPPER_H
#define FORMAT_PROCESSOR_WRAPPER_H

#include <filesystem>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <utility>
#include <vector>

#include "BasePluginWrapper.hpp"
#include "PyExceptionInfo.hpp"

class FormatProcessorWrapper : public BasePluginWrapper<std::string> {
 public:
    auto get(ResultFilesPaths &&paths)
        -> std::variant<FormatProcessorWrapper::type, PyExceptionInfo>;
};

static_assert(is_plugin_wrapper<FormatProcessorWrapper>);

#endif
