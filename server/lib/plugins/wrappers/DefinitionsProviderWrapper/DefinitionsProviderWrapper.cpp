#include "DefinitionsProviderWrapper.hpp"
#include "PyExceptionInfo.hpp"
#include "pyerrors.h"
#include <boost/python/errors.hpp>
#include <boost/python/extract.hpp>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <utility>
#include <vector>

DefinitionsProviderWrapper::DefinitionsProviderWrapper(BasePluginWrapper &&base)
    : BasePluginWrapper(std::move(base)) {
}

auto DefinitionsProviderWrapper::get(const std::string &word,
                                     const std::string &filter_query,
                                     uint64_t           batch_size,
                                     bool               restart)
    -> std::variant<DefinitionsProviderWrapper::type, PyExceptionInfo> {
    if (restart) {
        auto found_item = generators_.find(word);
        if (found_item != generators_.end()) {
            generators_.erase(found_item);
        }
    }
    if (generators_.find(word) == generators_.end()) {
        try {
            boost::python::object test = container_.get()(word);
            generators_[word]          = test;
            generators_[word]->attr("__next__")();
        } catch (boost::python::error_already_set &) {
            generators_.erase(generators_.find(word));
            return PyExceptionInfo::build().value();
        }
    }

    try {
        boost::python::object py_json       = boost::python::import("json");
        boost::python::object py_json_dumps = py_json.attr("dumps");

        boost::python::object py_res =
            generators_[word]->attr("send")(batch_size);
        boost::python::object py_json_res = py_json_dumps(py_res);

        std::string str_res = boost::python::extract<std::string>(py_json_res);
        nlohmann::json json_res = nlohmann::json::parse(str_res);

        // TODO(blackdeer): PROPER ERROR HANDLING
        if (!json_res.is_array()) {
            return {};
        }
        auto error_message = json_res[1].get<std::string>();
        auto cards         = json_res[0].get<std::vector<Card>>();
        return std::make_pair(cards, error_message);
    } catch (boost::python::error_already_set &) {
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
    return {};
}

auto DefinitionsProviderWrapper::get_dictionary_scheme()
    -> std::variant<nlohmann::json, PyExceptionInfo> {
    return {};
}
