#ifndef DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_FORMAT_PROCESSOR_PLUGIN_WRAPPER_FORMATPROCESSORPLUGINWRAPPER_H
#define DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_FORMAT_PROCESSOR_PLUGIN_WRAPPER_FORMATPROCESSORPLUGINWRAPPER_H

#include <string>
#include <memory>

#include "plugin_wrappers/basic_plugin_wrapper/BasicPluginWrapper.h"
#include "plugin_wrappers/plugin_wrapper_interfaces/IFormatProcessorPluginWrapper.h"

class FormatProcessorPluginWrapper
    : public BasicPluginWrapper,
      virtual public IFormatProcessorPluginWrapper {
 public:
    FormatProcessorPluginWrapper(std::shared_ptr<IRequestable> connection);
    void save(const std::string &cards_path,
              const std::string &links_path,
              const std::string &media_path) override;
};

#endif  // DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_FORMAT_PROCESSOR_PLUGIN_WRAPPER_FORMATPROCESSORPLUGINWRAPPER_H
