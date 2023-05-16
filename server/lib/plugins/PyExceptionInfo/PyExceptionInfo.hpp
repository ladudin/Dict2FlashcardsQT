#ifndef PY_EXCEPTION_INFO_H
#define PY_EXCEPTION_INFO_H

#include <boost/python/object_fwd.hpp>
#include <optional>
#include <string>
#include <utility>

class PyExceptionInfo {
 public:
    static auto build(boost::python::object &plugin_namespace)
        -> std::optional<PyExceptionInfo>;

    [[nodiscard]] inline auto stack_trace() const -> const std::string & {
        return stack_trace_;
    }

    [[nodiscard]] inline auto error_summary() const -> const std::string & {
        return error_summary_;
    }

 private:
    std::string stack_trace_;
    std::string error_summary_;

    PyExceptionInfo() = default;
};

#endif  // !PY_EXCEPTION_INFO_H
