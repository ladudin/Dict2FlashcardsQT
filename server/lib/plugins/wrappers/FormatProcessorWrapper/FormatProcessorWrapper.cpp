#include "FormatProcessorWrapper.hpp"
#include "Container.hpp"
#include "IPluginWrapper.hpp"

FormatProcessorWrapper::FormatProcessorWrapper(std::string &&name,
                                               Container   &&container)
    : name_(name), container_(container) {
}

auto FormatProcessorWrapper::build(std::string name, Container container)
    -> std::variant<FormatProcessorWrapper, PyExceptionInfo> {
    auto wrapper =
        FormatProcessorWrapper(std::move(name), std::move(container));
    try {
        boost::python::object py_json        = boost::python::import("json");
        boost::python::object py_json_dumps  = py_json.attr("dumps");

        boost::python::object py_plugin_conf = container.get_default_config()();
        boost::python::object py_str_json_conf = py_json_dumps(py_plugin_conf);

        std::string           cpp_plugin_conf =
            boost::python::extract<std::string>(py_str_json_conf);
        wrapper.config_ = nlohmann::json::parse(cpp_plugin_conf);
    } catch (const boost::python::error_already_set &) {
        return PyExceptionInfo::build().value();
    }
    return wrapper;
}
