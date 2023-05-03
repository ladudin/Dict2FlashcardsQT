#ifndef SERVER_H
#define SERVER_H

#include "wrappers.hpp"
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using UserID = uint16_t;

class User {
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
    // DefinitionsProviderWrapper definitions_provider_;
    // SentencesProviderWrapper   sentences_provider_;
    // ImagesProviderWrapper      images_provider_;
    // AudiosProviderWrapper      audios_provider_;
    // FormatProcessorWrapper     format_processor_;
};

class TCPSession : public std::enable_shared_from_this<TCPSession> {
 public:
    explicit TCPSession(boost::asio::ip::tcp::socket socket);

    void start();

 private:
    boost::asio::ip::tcp::socket socket_;
    boost::asio::streambuf       request_buffer;
    char                         data_[1024];

    void                         do_read();

    void                         do_write(std::size_t length);
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
    boost::asio::io_context         &io_context_;
    boost::asio::ip::tcp::acceptor   acceptor_;
    std::unordered_map<UserID, User> users;

    void                             start_accept();

    void                             handle_accept(
                                    // TCPConnection::pointer          new_connection,
        const boost::system::error_code &error);
    // clang-format on
};

#endif  // SERVER_H!
