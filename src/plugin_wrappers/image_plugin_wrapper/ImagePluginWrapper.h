#ifndef DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_IMAGE_PLUGIN_WRAPPER_IMAGEPLUGINWRAPPER_H
#define DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_IMAGE_PLUGIN_WRAPPER_IMAGEPLUGINWRAPPER_H

#include <string>
#include <vector>

#include "../basic_plugin_wrapper/BasicPluginWrapper.h"
#include "../plugin_wrapper_interfaces/IMultimediaPluginWrapper.h"

class ImagePluginWrapper : public BasicPluginWrapper, virtual public IMultimediaPluginWrapper {
    std::vector<std::string> get(const std::string& word, size_t count) override;
};

std::string ImagePluginWrapper::BasicPluginWrapper::plugin_type_("Image");

#endif  // DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_IMAGE_PLUGIN_WRAPPER_IMAGEPLUGINWRAPPER_H
