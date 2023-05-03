find_package(nlohmann_json 3.7.0 REQUIRED)

add_library(plugin_server server.cpp)
target_link_libraries(plugin_server
    PUBLIC
    serverside_plugin_wrappers
    PRIVATE
    nlohmann_json::nlohmann_json)
target_include_directories(plugin_server PUBLIC ./)
