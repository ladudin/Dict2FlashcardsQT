find_package(nlohmann_json 3.7.0 REQUIRED)

add_library(plugin_server server.cpp)
target_link_libraries(plugin_server
    serverside_plugin_wrappers
    session
    ${Boost_LIBRARIES}
    ${PYTHON_LIBRARIES}
)
target_include_directories(plugin_server
    PUBLIC
    ./
    PRIVATE
    ${Boost_INCLUDE_DIRS}
    ${PYTHON_INCLUDE_DIRS}
)
