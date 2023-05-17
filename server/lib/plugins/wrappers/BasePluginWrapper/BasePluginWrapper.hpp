#ifndef BASE_PLUGIN_WRAPPER_H
#define BASE_PLUGIN_WRAPPER_H

#include <boost/python/errors.hpp>
#include <boost/python/extract.hpp>
#include <boost/python/object_fwd.hpp>
#include <memory>
#include <nlohmann/json_fwd.hpp>
#include <optional>
#include <string>
#include <utility>
#include <variant>

#include "IPluginWrapper.hpp"
#include "PyExceptionInfo.hpp"

class BasePluginWrapper : public IPluginWrapper {
 public:
    BasePluginWrapper(const BasePluginWrapper &)                     = delete;
    BasePluginWrapper(BasePluginWrapper &&)                          = default;
    auto operator=(const BasePluginWrapper &) -> BasePluginWrapper & = delete;
    auto operator=(BasePluginWrapper &&) -> BasePluginWrapper      & = default;
    ~BasePluginWrapper() override                                    = default;

    static auto build(std::string &&name, const boost::python::object &module)
        -> std::variant<BasePluginWrapper, PyExceptionInfo>;

    [[nodiscard]] auto name() const -> const std::string & override;
    auto               load() -> std::optional<PyExceptionInfo> override;
    auto               unload() -> std::optional<PyExceptionInfo> override;
    auto               get_config_description()
        -> std::variant<PyExceptionInfo, nlohmann::json> override;
    auto get_default_config()
        -> std::variant<PyExceptionInfo, nlohmann::json> override;
    auto set_config(nlohmann::json &&new_config)
        -> std::variant<PyExceptionInfo, nlohmann::json> override;

 protected:
    struct CommonFunctions {
        static auto build(const boost::python::object &module)
            -> std::variant<CommonFunctions, PyExceptionInfo>;

        boost::python::object load;
        boost::python::object get_config_description;
        boost::python::object set_config;
        boost::python::object get_default_config;
        boost::python::object unload;

     private:
        CommonFunctions();
    };

    BasePluginWrapper(std::string &&name, CommonFunctions &&common);

    std::string     name_;
    CommonFunctions common_;
    nlohmann::json  config_;
};

struct ResultFilesPaths {
    std::filesystem::path cards;
    std::filesystem::path audios;
    std::filesystem::path images;
};

template <class T>
concept implements_wrapper_get = (
    // SentencesProvider, AudiosProvider, ImagesProvider
    requires(T                  dependent_instance,
             const std::string &query,
             uint64_t           batch_size) {
        {
            dependent_instance.get(query, batch_size)
        } -> std::same_as<std::variant<typename T::type, PyExceptionInfo>>;
    } ||
    // DefinitionsProvider
    requires(T                  dependent_instance,
             const std::string &query,
             const std::string &filter,
             bool               restart,
             uint64_t           batch_size) {
        {
            dependent_instance.get(query, filter, batch_size, restart)
        } -> std::same_as<std::variant<typename T::type, PyExceptionInfo>>;
    } ||
    // FormatProcessor
    requires(T dependent_instance, ResultFilesPaths paths) {
        {
            dependent_instance.get(std::move(paths))
        } -> std::same_as<std::variant<typename T::type, PyExceptionInfo>>;
    });

template <class T>
concept is_plugin_wrapper =
    std::derived_from<T, BasePluginWrapper> && implements_wrapper_get<T>;

#endif  // !BASE_PLUGIN_WRAPPER_H
