#include "Container.hpp"
#include "spdlog/common.h"
#include "spdlog/spdlog.h"

// https://stackoverflow.com/questions/1418015/how-to-get-python-exception-text
auto Container::build(boost::python::object &&module)
    -> std::variant<Container, std::optional<PyExceptionInfo>> {
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
    } catch (const boost::python::error_already_set &) {
        return PyExceptionInfo::build();
    }
    return plugin_container;
}

Container::Container() = default;

auto Container::load() -> boost::python::object & {
    return load_;
}

auto Container::get() -> boost::python::object & {
    return get_;
}

auto Container::get_config_description() -> boost::python::object & {
    return get_config_description_;
}

auto Container::set_config() -> boost::python::object & {
    return set_config_;
}

auto Container::get_default_config() -> boost::python::object & {
    return get_default_config_;
}

auto Container::unload() -> boost::python::object & {
    return unload_;
}
