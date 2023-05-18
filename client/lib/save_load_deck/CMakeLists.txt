message(${CMAKE_CURRENT_SOURCE_DIR})

add_library(save_load_deck save_load.cpp)
target_link_libraries(save_load_deck PUBLIC common)
target_include_directories(basic_plugin_wrapper INTERFACE ./)