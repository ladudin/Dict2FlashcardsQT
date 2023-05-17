#include "FormatProcessorWrapper.hpp"
#include "BasePluginWrapper.hpp"

FormatProcessorWrapper::FormatProcessorWrapper(BasePluginWrapper &&base)
    : BasePluginWrapper(std::move(base)) {
}

auto FormatProcessorWrapper::build(BaseContainer container)
    -> std::variant<FormatProcessorWrapper, PyExceptionInfo> {
    auto base_or_error = BasePluginWrapper::build(std::move(container));
    if (std::holds_alternative<PyExceptionInfo>(base_or_error)) {
        return std::get<PyExceptionInfo>(base_or_error);
    }
    auto base = std::move(std::get<BasePluginWrapper>(base_or_error));
    return FormatProcessorWrapper(std::move(base));
}

auto FormatProcessorWrapper::get(ResultFilesPaths &&paths)
    -> std::variant<FormatProcessorWrapper::type, PyExceptionInfo> {
    return {};
}
