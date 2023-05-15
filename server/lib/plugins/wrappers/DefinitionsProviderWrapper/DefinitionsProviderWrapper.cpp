#include "DefinitionsProviderWrapper.hpp"

auto DefinitionsProviderWrapper::get(const std::string &word,
                                     uint64_t           batch_size)
    -> std::variant<DefinitionsProviderWrapper::type, PyExceptionInfo> {
    return {};
}
