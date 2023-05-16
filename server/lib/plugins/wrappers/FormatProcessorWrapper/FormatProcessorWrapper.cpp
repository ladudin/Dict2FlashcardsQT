#include "FormatProcessorWrapper.hpp"
#include "BasePluginWrapper.hpp"

FormatProcessorWrapper::FormatProcessorWrapper(BasePluginWrapper &&base)
    : BasePluginWrapper(std::move(base)) {
}

auto FormatProcessorWrapper::get(ResultFilesPaths &&paths)
    -> std::variant<FormatProcessorWrapper::type, PyExceptionInfo> {
    return {};
}
