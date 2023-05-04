#ifndef DICT2FLASHCARDSQT_SRC_DATAPROVIDER_IREQUESTABLE_IREQUESTABLE_H
#define DICT2FLASHCARDSQT_SRC_DATAPROVIDER_IREQUESTABLE_IREQUESTABLE_H

#include <string>

class IRequestable {
 public:
    virtual ~IRequestable()                                 = default;
    virtual std::string request(const std::string &message) = 0;
};

#endif  // DICT2FLASHCARDSQT_SRC_DATAPROVIDER_IREQUESTABLE_IREQUESTABLE_H
