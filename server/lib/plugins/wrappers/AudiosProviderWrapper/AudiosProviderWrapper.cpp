#include "AudiosProviderWrapper.hpp"
#include <boost/python/extract.hpp>
#include <boost/python/import.hpp>
#include <cstdint>
#include <nlohmann/json_fwd.hpp>
#include <optional>
#include <string>
#include <utility>
#include <variant>
#include <vector>

auto AudiosProviderWrapper::get(const std::string &word, uint64_t batch_size)
    -> std::variant<AudiosProviderWrapper::type, PyExceptionInfo> {
    std::vector<AudioInfo> test;
    return std::make_pair(test, "");
}
