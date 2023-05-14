#ifndef PLUGIN_WRAPPER_INTERFACE_H
#define PLUGIN_WRAPPER_INTERFACE_H

#include "Container.hpp"
#include <concepts>
#include <cstdint>
#include <filesystem>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>

template <class T>
class IPluginWrapper {
 public:
    using type                                              = T;
    virtual ~IPluginWrapper()                               = default;

    virtual void load()                                     = 0;
    virtual auto get_config_description() -> nlohmann::json = 0;
    virtual auto get_default_config() -> nlohmann::json     = 0;
    virtual auto set_config(nlohmann::json &&new_config) -> nlohmann::json = 0;
    virtual void unload()                                                  = 0;
};

struct ResultFilesPaths {
    std::filesystem::path cards;
    std::filesystem::path audios;
    std::filesystem::path images;
};

template <class T>
concept container_constructible = std::constructible_from<T, Container>;

template <class T>
concept implements_wrapper_interface =
    requires(T dependent_instance) {
        []<typename X>(IPluginWrapper<X> &) {}(dependent_instance);
    };

template <class T>
concept implements_wrapper_get = (
    // DefinitionsProvider, SentencesProvider, AudiosProvider, ImagesProvider
    requires(T dependent_instance) {
        {
            [](T dependent_instance) {
                const std::string &word = "";
                uint64_t           batch_size;
                return dependent_instance.get(word, batch_size);
            }(dependent_instance)
        } -> std::same_as<typename T::type>;
    } ||
    // FormatProcessor
    requires(T dependent_instance) {
        {
            [](T dependent_instance) {
                ResultFilesPaths paths{};
                return dependent_instance.get(std::move(paths));
            }(dependent_instance)
        } -> std::same_as<typename T::type>;
    });

template <class T>
concept is_plugin_wrapper =
    implements_wrapper_interface<T> && container_constructible<T> &&
    implements_wrapper_get<T>;

#endif  // !PLUGIN_WRAPPER_INTERFACE_H
