#ifndef PLUGINS_LOADER_H
#define PLUGINS_LOADER_H

#include <string>

template <typename Wrapper>
class IPluginsLoader {
    virtual ~IPluginsLoader() = default;

    virtual auto get(const std::string &plugin_name) -> Wrapper;
};

template <typename Wrapper>
class PluginsLoader : public IPluginsLoader<Wrapper> {
    explicit PluginsLoader(const std::string &plugins_dir) {
    }

 private:
};

#endif
