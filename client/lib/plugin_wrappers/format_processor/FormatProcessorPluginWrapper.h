#ifndef FORMATPROCESSORPLUGINWRAPPER_H
#define FORMATPROCESSORPLUGINWRAPPER_H

#include <memory>
#include <string>

#include "../basic/BasicPluginWrapper.h"
#include "IFormatProcessorPluginWrapper.h"

class FormatProcessorPluginWrapper
    : public BasicPluginWrapper,
      virtual public IFormatProcessorPluginWrapper {
 public:
    FormatProcessorPluginWrapper(std::shared_ptr<IRequestable> connection);
    std::string save(const std::string &cards_path,
                     const std::string &links_path,
                     const std::string &media_path) override;
};

#endif  // FORMATPROCESSORPLUGINWRAPPER_H
