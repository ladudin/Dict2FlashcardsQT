#ifndef I_FORMAT_PROCESSOR_WRAPPER_H
#define I_FORMAT_PROCESSOR_WRAPPER_H

#include "IPluginWrapper.hpp"

#include <filesystem>
#include <string>

struct ResultFilesPaths {
    std::filesystem::path cards;
    std::filesystem::path audios;
    std::filesystem::path images;
};

class IFormatProcessorWrapper : public virtual IPluginWrapper {
 public:
    using type = std::string;

    virtual auto save(const ResultFilesPaths &paths)
        -> std::variant<type, PyExceptionInfo> = 0;
};

#endif
