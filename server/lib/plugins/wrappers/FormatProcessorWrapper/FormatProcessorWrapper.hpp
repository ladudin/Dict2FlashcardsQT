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

    FormatProcessorWrapper(const FormatProcessorWrapper &);
    FormatProcessorWrapper(FormatProcessorWrapper &&) = default;
    auto operator=(const FormatProcessorWrapper &)
        -> FormatProcessorWrapper & = delete;
    auto operator=(FormatProcessorWrapper &&)
        -> FormatProcessorWrapper & = default;

    static auto build(const std::string &name, boost::python::object module)
        -> std::variant<FormatProcessorWrapper, PyExceptionInfo>;

    auto save(ResultFilesPaths &&paths)
        -> std::variant<FormatProcessorWrapper::type, PyExceptionInfo>;

 protected:
    struct FormatProcessorsFunctions {
        static auto build(boost::python::object module)
            -> std::variant<FormatProcessorsFunctions, PyExceptionInfo>;

        boost::python::object save;
    };

    FormatProcessorsFunctions specifics_;

 private:
    explicit FormatProcessorWrapper(BasePluginWrapper &&base);
};

static_assert(is_plugin_wrapper<FormatProcessorWrapper>);

#endif
