#ifndef DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_IMAGE_PLUGIN_WRAPPER_IMAGEPLUGINWRAPPER_H
#define DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_IMAGE_PLUGIN_WRAPPER_IMAGEPLUGINWRAPPER_H

#include <string>
#include <vector>
#include <memory>

#include "plugin_wrappers/basic_plugin_wrapper/BasicPluginWrapper.h"
#include "plugin_wrappers/plugin_wrapper_interfaces/IMultimediaPluginWrapper.h"

class ImagePluginWrapper : public BasicPluginWrapper,
                           virtual public IMultimediaPluginWrapper {
 public:
    ImagePluginWrapper(std::shared_ptr<IRequestable> connection);
    std::vector<std::string> get(const std::string &word,
                                 size_t             count) override;
};

#endif  // DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_IMAGE_PLUGIN_WRAPPER_IMAGEPLUGINWRAPPER_H
