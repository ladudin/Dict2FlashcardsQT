#ifndef RESPONSE_GENERATORS_H
#define RESPONSE_GENERATORS_H

#include <nlohmann/json.hpp>
#include <string>

class IResponceGenerator {
 public:
    explicit IResponceGenerator();

    virtual ~IResponceGenerator() = default;

    virtual auto handle(std::string request) -> nlohmann::json;

    IResponceGenerator(const IResponceGenerator &) = default;
    IResponceGenerator(IResponceGenerator &&)      = default;
    auto operator=(const IResponceGenerator &)
        -> IResponceGenerator                                   & = default;
    auto operator=(IResponceGenerator &&) -> IResponceGenerator & = default;
};

class ResponceGenerator : public IResponceGenerator {
 public:
    ResponceGenerator();

    auto handle(std::string request) -> nlohmann::json override;
};

#endif  // !RESPONSE_GENERATORS_H
