#include "PyExceptionInfo.hpp"
#include "spdlog/common.h"
#include "spdlog/spdlog.h"
#include <boost/python/exec.hpp>
#include <boost/python/extract.hpp>
#include <boost/python/import.hpp>
#include <boost/python/object_fwd.hpp>

auto PyExceptionInfo::build(boost::python::object &plugin_namespace)
    -> std::optional<PyExceptionInfo> {
    // Print обязатетен
    // https://stackoverflow.com/a/57896281
    PyExceptionInfo info;
    try {
        PyErr_Print();

        boost::python::exec("import traceback, sys", plugin_namespace);

        boost::python::object py_err =
            boost::python::eval("str(sys.last_value)", plugin_namespace);

        boost::python::object py_stack_trace = boost::python::eval(
            "'\\n'.join(traceback.format_exception(sys.last_type, "
            "sys.last_value, sys.last_traceback))",
            plugin_namespace);
        info.stack_trace_ =
            std::move(boost::python::extract<std::string>(py_stack_trace));
        info.error_summary_ =
            std::move(boost::python::extract<std::string>(py_err));
        PyErr_Clear();
    } catch (const boost::python::error_already_set &) {
        spdlog::error("Couldn't extract python exception info");
        return std::nullopt;
    }
    return info;
}
