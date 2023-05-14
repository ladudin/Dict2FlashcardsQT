message(${CMAKE_CURRENT_SOURCE_DIR})

add_library(plugin_types_locations_config PluginTypesLocationsConfig.cpp)
target_include_directories(plugin_types_locations_config PUBLIC ./)
