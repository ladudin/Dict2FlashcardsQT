#ifndef PY_EXCEPTION_INFO_H
#define PY_EXCEPTION_INFO_H

#include <optional>
#include <string>
#include <utility>

class PyExceptionInfo {
 public:
    static auto               build() -> std::optional<PyExceptionInfo>;

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
