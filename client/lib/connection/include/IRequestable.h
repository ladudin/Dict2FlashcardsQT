#ifndef IREQUESTABLE_H
#define IREQUESTABLE_H

#include <string>

class IRequestable {
 public:
    virtual ~IRequestable() = default;
    virtual std::pair<bool, std::string>
    request(std::string message) = 0;
};

#endif  // IREQUESTABLE_H
