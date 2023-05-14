message(${CMAKE_CURRENT_SOURCE_DIR})

add_library(plugins_provider PluginsProvider.cpp)
target_include_directories(plugins_provider PUBLIC
    ./
)

target_link_libraries(plugins_provider
    plugins_loader
    plugin_types_locations_config
)
