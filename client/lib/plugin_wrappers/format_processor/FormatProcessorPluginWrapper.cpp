#include "FormatProcessorPluginWrapper.h"

#include <memory>
#include <string>

#include "IRequestable.h"

FormatProcessorPluginWrapper::FormatProcessorPluginWrapper(
    std::shared_ptr<IRequestable> connection)
    : BasicPluginWrapper(std::move(connection), "format_processor") {
}

std::string FormatProcessorPluginWrapper::save(const std::string &cards_path,
                                               const std::string &links_path,
                                               const std::string &media_path) {
}