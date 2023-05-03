#ifndef SERVER_H
#define SERVER_H

#include "wrappers.hpp"
#include <algorithm>
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <cstdint>
#include <memory>
#include <nlohmann/json_fwd.hpp>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using UserID = uint16_t;

class PluginsBundle {
 public:
    // clang-format off
    auto get_definitions(std::string word)
        -> DefinitionsProviderWrapper::provided_type;

    auto get_sentences(std::string word)
        -> SentencesProviderWrapper::provided_type;

    auto get_images(std::string word) 
        -> ImagesProviderWrapper::provided_type;

    auto get_audios(std::string word) 
        -> AudiosProviderWrapper::provided_type;

    auto save_results(std::string word)
        -> FormatProcessorWrapper::provided_type;
    // clang-format on

    auto get_definitions_providers_config(JSON new_config) -> JSON;
    auto set_definitions_providers_config(JSON new_config) -> JSON;

    auto get_sentences_providers_config(JSON new_config) -> JSON;
    auto set_sentences_providers_config(JSON new_config) -> JSON;

    auto get_images_providers_config(JSON new_config) -> JSON;
    auto set_images_providers_config(JSON new_config) -> JSON;

    auto get_audios_providers_config(JSON new_config) -> JSON;
    auto set_audios_providers_config(JSON new_config) -> JSON;

    auto get_format_processors_config(JSON new_config) -> JSON;
    auto set_format_processors_config(JSON new_config) -> JSON;

 private:
    // std::optional<DefinitionsProviderWrapper> definitions_provider_ =
    //     std::nullopt;
    // std::optional<SentencesProviderWrapper> sentences_provider_ =
    // std::nullopt; std::optional<ImagesProviderWrapper>    images_provider_ =
    // std::nullopt; std::optional<AudiosProviderWrapper>    audios_provider_ =
    // std::nullopt; std::optional<FormatProcessorWrapper>   format_processor_
    // = std::nullopt;
};

class IResponceGenerator {
 public:
    explicit IResponceGenerator(nlohmann::json request);

    virtual ~IResponceGenerator() = default;

    virtual auto handle() -> nlohmann::json;

    IResponceGenerator(const IResponceGenerator &)            = default;
    IResponceGenerator(IResponceGenerator &&)                 = default;
    IResponceGenerator &operator=(const IResponceGenerator &) = default;
    IResponceGenerator &operator=(IResponceGenerator &&)      = default;
};

class ResponceGenerator : public IResponceGenerator {
 public:
    explicit ResponceGenerator(nlohmann::json request);

    auto handle() -> nlohmann::json override;
};

class TCPConnection : public std::enable_shared_from_this<TCPConnection> {
 public:
    explicit TCPConnection(
        boost::asio::ip::tcp::socket        socket,
        std::unique_ptr<IResponceGenerator> response_generator);

    void start();

 private:
    boost::asio::ip::tcp::socket        socket_;
    boost::asio::streambuf              request_buffer;
    std::unique_ptr<IResponceGenerator> response_generator_;

    void                                do_read();
    void                                do_write(std::size_t length);
    void                                handle_request(std::string);
};

class PluginServer {
 public:
    explicit PluginServer(boost::asio::io_context &context, uint16_t port);

    ~PluginServer()                                        = default;
    PluginServer(const PluginServer &)                     = delete;
    PluginServer(PluginServer &&)                          = delete;
    auto operator=(const PluginServer &) -> PluginServer & = delete;
    auto operator=(PluginServer &&) -> PluginServer      & = delete;

 private:
    boost::asio::io_context       &io_context_;
    boost::asio::ip::tcp::acceptor acceptor_;

    void                           start_accept();

    void                           handle_accept(
                                  // TCPConnection::pointer          new_connection,
        const boost::system::error_code &error);
    // clang-format on
};

#endif  // SERVER_H!
