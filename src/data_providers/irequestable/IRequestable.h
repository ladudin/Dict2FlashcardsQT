#ifndef DICT2FLASHCARDSQT_SRC_DATAPROVIDER_IREQUESTABLE_IREQUESTABLE_H
#define DICT2FLASHCARDSQT_SRC_DATAPROVIDER_IREQUESTABLE_IREQUESTABLE_H

#include <string>
#include <variant>

#include "containers/ExceptionInfo.h"

class IRequestable {
 public:
    virtual ~IRequestable() = default;
    virtual std::variant<std::string, ExceptionInfo>
    request(const std::string &message) = 0;
};

#endif  // DICT2FLASHCARDSQT_SRC_DATAPROVIDER_IREQUESTABLE_IREQUESTABLE_H
