#include "PyExceptionInfo.hpp"
#include "spdlog/common.h"
#include "spdlog/spdlog.h"
#include <boost/python/exec.hpp>
#include <boost/python/extract.hpp>

auto PyExceptionInfo::build() -> std::optional<PyExceptionInfo> {
    PyExceptionInfo info;
    try {
        PyErr_Clear();
        auto py_err         = boost::python::eval("str(sys.last_value)");
        auto py_stack_trace = boost::python::eval(
            "'\\n'.join(traceback.format_exception(sys.last_type, "
            "sys.last_value, sys.last_traceback))");
        info.stack_trace_ =
            std::move(boost::python::extract<std::string>(py_stack_trace));
        info.error_summary_ =
            std::move(boost::python::extract<std::string>(py_err));
    } catch (...) {
        spdlog::error("Couldn't extract python exception info");
        return std::nullopt;
    }
    return info;
}

inline auto PyExceptionInfo::stack_trace() const -> const std::string & {
    return stack_trace_;
}

inline auto PyExceptionInfo::error_summary() const -> const std::string & {
    return error_summary_;
}