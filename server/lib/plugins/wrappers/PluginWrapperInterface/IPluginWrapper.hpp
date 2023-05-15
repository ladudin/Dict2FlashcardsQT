#ifndef PLUGIN_WRAPPER_INTERFACE_H
#define PLUGIN_WRAPPER_INTERFACE_H

#include "Container.hpp"
#include "PyExceptionInfo.hpp"
#include <concepts>
#include <cstdint>
#include <filesystem>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <utility>

template <class T>
class IPluginWrapper {
 public:
    using type                                                     = T;
    virtual ~IPluginWrapper()                                      = default;

    [[nodiscard]] virtual auto name() const -> const std::string & = 0;
    virtual auto               load() -> std::optional<PyExceptionInfo> = 0;
    virtual auto               get_config_description()
        -> std::variant<PyExceptionInfo, nlohmann::json> = 0;
    virtual auto get_default_config()
        -> std::variant<PyExceptionInfo, nlohmann::json> = 0;
    virtual auto set_config(nlohmann::json &&new_config)
        -> std::variant<PyExceptionInfo, nlohmann::json>    = 0;
    virtual auto unload() -> std::optional<PyExceptionInfo> = 0;
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
            T::build(name, container)
        } -> std::same_as<std::variant<T, PyExceptionInfo>>;
    };

template <class T>
concept implements_wrapper_interface =
    requires(T dependent_instance) {
        []<typename X>(IPluginWrapper<X> &) {}(dependent_instance);
    };

template <class T>
concept implements_wrapper_get = (
    // DefinitionsProvider, SentencesProvider, AudiosProvider, ImagesProvider
    requires(T                  dependent_instance,
             const std::string &word,
             uint64_t           batch_size) {
        {
            dependent_instance.get(word, batch_size)
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
    implements_wrapper_interface<T> && container_constructible<T> &&
    implements_wrapper_get<T>;

#endif  // !PLUGIN_WRAPPER_INTERFACE_H
