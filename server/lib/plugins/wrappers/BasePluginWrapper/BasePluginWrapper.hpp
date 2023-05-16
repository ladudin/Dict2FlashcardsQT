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

    static auto build(Container container)
        -> std::variant<BasePluginWrapper, PyExceptionInfo>;

    ~BasePluginWrapper() override = default;

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
    explicit BasePluginWrapper(Container &&container);

    Container      container_;
    nlohmann::json config_;
};

struct ResultFilesPaths {
    std::filesystem::path cards;
    std::filesystem::path audios;
    std::filesystem::path images;
};

template <class T>
concept container_constructible =
    requires(T instance, std::string name, Container container) {
        {
            T::build(container)
        } -> std::same_as<std::variant<T, PyExceptionInfo>>;
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
    std::derived_from<T, BasePluginWrapper> && container_constructible<T> &&
    implements_wrapper_get<T>;

#endif  // !BASE_PLUGIN_WRAPPER_H
