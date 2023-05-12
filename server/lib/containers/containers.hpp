#ifndef CONTAINERS_H
#define CONTAINERS_H

#include <boost/python.hpp>
#include <boost/python/extract.hpp>
#include <boost/python/import.hpp>
#include <string>
#include <variant>

struct ExceptionInfo {
    std::string stack_trace;
    std::string error_summary;
};

class Container {
 public:
    static auto build(boost::python::object &&module)
        -> std::variant<Container, ExceptionInfo>;

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
    boost::python::object load_;
    boost::python::object get_;
    boost::python::object get_config_description_;
    boost::python::object set_config_;
    boost::python::object get_default_config_;
    boost::python::object unload_;
};

#endif  // !CONTAINERS_H
