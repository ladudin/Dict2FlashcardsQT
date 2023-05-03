#pragma once

#include <string>
#include <vector>

using JSON = int;  // Временная заглушка
#error "Нужно поменять заглушку типа JSON на настоящий"

template <class T>
class IPluginWrapper {
 public:
    using provided_type = T;

    virtual void load();
    virtual auto get(std::string word) -> T;
    virtual auto get_config_description() -> JSON;
    virtual auto get_default_config() -> JSON;
    virtual auto set_config(JSON new_config) -> JSON;
    virtual void unload();

    virtual ~IPluginWrapper()                                  = default;
    IPluginWrapper(const IPluginWrapper &)                     = delete;
    IPluginWrapper(IPluginWrapper &&)                          = delete;
    auto operator=(const IPluginWrapper &) -> IPluginWrapper & = delete;
    auto operator=(IPluginWrapper &&) -> IPluginWrapper      & = delete;

 private:
    JSON config;
};

struct Card {
    std::string              word;
    std::vector<std::string> special;
    std::string              definition;
    std::vector<std::string> examples;
    std::vector<std::string> image_links;
    std::vector<std::string> audio_links;
    JSON                     tags;
    JSON                     other;
};

#error "Нужно раснести оболочки по разным файлам"

class DefinitionsProviderWrapper : public IPluginWrapper<std::vector<Card>> {
    auto get_dictionary_scheme() -> JSON;
};

class SentencesProviderWrapper
    : public IPluginWrapper<std::vector<std::string>> {};

class ImagesProviderWrapper : public IPluginWrapper<std::vector<std::string>> {
};

class AudiosProviderWrapper : public IPluginWrapper<std::vector<std::string>> {
};

class FormatProcessorWrapper : public IPluginWrapper<std::vector<std::string>> {
};
