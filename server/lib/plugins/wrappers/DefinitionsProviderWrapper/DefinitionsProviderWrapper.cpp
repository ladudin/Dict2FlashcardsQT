#include "DefinitionsProviderWrapper.hpp"
#include "PyExceptionInfo.hpp"
#include "pyerrors.h"
#include <boost/python/errors.hpp>
#include <boost/python/extract.hpp>
#include <nlohmann/json_fwd.hpp>
#include <string>

auto DefinitionsProviderWrapper::get(const std::string &word,
                                     const std::string &filter_query,
                                     uint64_t           batch_size,
                                     bool               restart)
    -> std::variant<DefinitionsProviderWrapper::type, PyExceptionInfo> {
    if (restart) {
        generators_.erase(generators_.find(word));
    }
    if (generators_.find(word) == generators_.end()) {
        try {
            generators_[word] = container_.get()();
            generators_[word]->attr("__next__")();
        } catch (const boost::python::error_already_set &) {
            generators_.erase(generators_.find(word));
            return PyExceptionInfo::build().value();
        }
    }

    nlohmann::json json_res;
    try {
        boost::python::object py_json       = boost::python::import("json");
        boost::python::object py_json_dumps = py_json.attr("dumps");

        boost::python::object py_res =
            generators_[word]->attr("send")(batch_size);
        boost::python::object py_json_res = py_json_dumps(py_res);

        std::string str_res = boost::python::extract<std::string>(py_json_res);

        json_res            = nlohmann::json::parse(str_res);
    } catch (const boost::python::error_already_set &) {
        boost::python::object py_err =
            boost::python::eval("str(sys.last_value)");
        std::string exception_type =
            boost::python::extract<std::string>(py_err);
        if (exception_type == "<class 'StopIteration'>") {
            PyErr_Clear();
            return {};
        }
        return PyExceptionInfo::build().value();
    }
    return json_res;
}

auto DefinitionsProviderWrapper::get_dictionary_scheme()
    -> std::variant<nlohmann::json, PyExceptionInfo> {
    return {};
}
