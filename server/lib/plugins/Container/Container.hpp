#ifndef CONTAINERS_H
#define CONTAINERS_H

#include "PyExceptionInfo.hpp"
#include <boost/python.hpp>
#include <boost/python/extract.hpp>
#include <boost/python/import.hpp>
#include <string>
#include <variant>

class Container {
 public:
    static auto build(boost::python::object &&module)
        -> std::variant<Container, std::optional<PyExceptionInfo>>;

    Container(const Container &)                    = default;
    Container(Container &&)                         = default;
    Container         &operator=(const Container &) = default;
    Container         &operator=(Container &&)      = default;

    [[nodiscard]] auto load() -> boost::python::object &;
    [[nodiscard]] auto get() -> boost::python::object &;
    [[nodiscard]] auto get_config_description() -> boost::python::object &;
    [[nodiscard]] auto set_config() -> boost::python::object &;
    [[nodiscard]] auto get_default_config() -> boost::python::object &;
    [[nodiscard]] auto unload() -> boost::python::object &;

 private:
    Container();
    boost::python::object load_;
    boost::python::object get_;
    boost::python::object get_config_description_;
    boost::python::object set_config_;
    boost::python::object get_default_config_;
    boost::python::object unload_;
};

#endif  // !CONTAINERS_H
