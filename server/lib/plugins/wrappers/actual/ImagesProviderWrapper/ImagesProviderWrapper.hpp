#ifndef IMAGES_PROVIDER_WRAPPER_H
#define IMAGES_PROVIDER_WRAPPER_H

#include <nlohmann/json_fwd.hpp>
#include <string>
#include <utility>
#include <variant>
#include <vector>

#include "BasePluginWrapper.hpp"
#include "IImagesProviderWrapper.hpp"
#include "PyExceptionInfo.hpp"

class ImagesProviderWrapper : public IImagesProviderWrapper,
                              public BasePluginWrapper {
 public:
    ImagesProviderWrapper(const ImagesProviderWrapper &);
    ImagesProviderWrapper(ImagesProviderWrapper &&) = default;
    auto operator=(const ImagesProviderWrapper &)
        -> ImagesProviderWrapper & = delete;
    auto operator=(ImagesProviderWrapper &&)
        -> ImagesProviderWrapper & = default;

    static auto build(const std::string           &name,
                      const boost::python::object &module)
        -> std::variant<ImagesProviderWrapper, PyExceptionInfo>;

    auto get(const std::string &word, uint64_t batch_size)
        -> std::variant<ImagesProviderWrapper::type, PyExceptionInfo> override;

 protected:
    struct ImagesProvidersFunctions {
        static auto build(const boost::python::object &module)
            -> std::variant<ImagesProvidersFunctions, PyExceptionInfo>;

        boost::python::object get;
    };

    ImagesProvidersFunctions specifics_;

 private:
    explicit ImagesProviderWrapper(BasePluginWrapper &&base);
};

static_assert(is_plugin_wrapper<ImagesProviderWrapper>);

#endif
