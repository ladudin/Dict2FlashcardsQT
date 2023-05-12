#include "containers.hpp"
#include "pyerrors.h"

// https://stackoverflow.com/questions/1418015/how-to-get-python-exception-text
auto Container::build(boost::python::object &&module)
    -> std::variant<Container, ExceptionInfo> {
    auto plugin_container = Container();
    try {
        plugin_container.load_ = module.attr("load");
        plugin_container.get_  = module.attr("get");
        plugin_container.get_config_description_ =
            module.attr("get_config_description");
        plugin_container.set_config_ = module.attr("set_config");
        plugin_container.get_default_config_ =
            module.attr("get_default_config");
        plugin_container.unload_ = module.attr("unload");
    } catch (...) {
        PyErr_Clear();
        auto py_err         = boost::python::eval("str(sys.last_value)");
        auto py_stack_trace = boost::python::eval(
            "'\\n'.join(traceback.format_exception(sys.last_type, "
            "sys.last_value, sys.last_traceback))");

        ExceptionInfo exception_info;
        exception_info.stack_trace =
            boost::python::extract<std::string>(py_stack_trace);
        exception_info.error_summary =
            boost::python::extract<std::string>(py_err);
        return exception_info;
    }
    return plugin_container;
}

auto Container::load() const -> const boost::python::object & {
    return load_;
}

auto Container::get() const -> const boost::python::object & {
    return get_;
}

auto Container::get_config_description() const
    -> const boost::python::object & {
    return get_config_description_;
}

auto Container::set_config() const -> const boost::python::object & {
    return set_config_;
}

auto Container::get_default_config() const -> const boost::python::object & {
    return get_default_config_;
}

auto Container::unload() const -> const boost::python::object & {
    return unload_;
}
