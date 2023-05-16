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
    static auto build(std::string &&name, boost::python::object &&module)
        -> std::variant<Container, std::optional<PyExceptionInfo>>;

    Container(const Container &)                    = default;
    Container(Container &&)                         = default;
    Container         &operator=(const Container &) = default;
    Container         &operator=(Container &&)      = default;

    [[nodiscard]] auto name() const -> const std::string &;
    [[nodiscard]] auto plugin_namespace() const
        -> const boost::python::object &;
    [[nodiscard]] auto load() const -> const boost::python::object &;
    [[nodiscard]] auto get() const -> const boost::python::object &;
    [[nodiscard]] auto get_config_description() const
        -> const boost::python::object &;
    [[nodiscard]] auto set_config() const -> const boost::python::object &;
    [[nodiscard]] auto get_default_config() const
        -> const boost::python::object &;
    [[nodiscard]] auto unload() const -> const boost::python::object &;

 private:
    Container();
    std::string           name_;
    boost::python::object load_;
    boost::python::object get_;
    boost::python::object get_config_description_;
    boost::python::object set_config_;
    boost::python::object get_default_config_;
    boost::python::object unload_;
};

#endif  // !CONTAINERS_H
