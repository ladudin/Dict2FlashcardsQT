#ifndef WRAPPERS_H
#define WRAPPERS_H

#include <nlohmann/json.hpp>
#include <string>
#include <utility>
#include <vector>





template <class T>
class IPluginWrapper {
 public:
    using provided_type = T;

    virtual void load();
    virtual auto get(std::string word) -> T;
    virtual auto get_config_description() -> nlohmann::json;
    virtual auto get_default_config() -> nlohmann::json;
    virtual auto set_config(nlohmann::json new_config) -> nlohmann::json;
    virtual void unload();

    virtual ~IPluginWrapper()                                  = default;
    IPluginWrapper(const IPluginWrapper &)                     = delete;
    IPluginWrapper(IPluginWrapper &&)                          = delete;
    auto operator=(const IPluginWrapper &) -> IPluginWrapper & = delete;
    auto operator=(IPluginWrapper &&) -> IPluginWrapper      & = delete;

 private:
    nlohmann::json config;
};

struct Card {
    std::string              word;
    std::vector<std::string> special;
    std::string              definition;
    std::vector<std::string> examples;
    std::vector<std::string> image_links;
    std::vector<std::string> audio_links;
    nlohmann::json           tags;
    nlohmann::json           other;
};

#error "Нужно раснести оболочки по разным файлам"

class DefinitionsProviderWrapper
    : public IPluginWrapper<std::pair<std::vector<Card>, std::string>> {
    auto get_dictionary_scheme() -> nlohmann::json;
};

class SentencesProviderWrapper
    : public IPluginWrapper<std::pair<std::vector<std::string>, std::string>> {
};

class ImagesProviderWrapper
    : public IPluginWrapper<std::pair<std::vector<std::string>, std::string>> {
};

class AudiosProviderWrapper
    : public IPluginWrapper<std::pair<std::vector<std::string>, std::string>> {
};

class FormatProcessorWrapper
    : public IPluginWrapper<std::pair<std::vector<std::string>, std::string>> {
};

#endif  // WRAPPERS_H
