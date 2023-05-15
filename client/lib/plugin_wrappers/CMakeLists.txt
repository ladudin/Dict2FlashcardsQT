add_library(client_plugin_wrappers
        src/BasicPluginWrapper.cpp
        src/WordPluginWrapper.cpp
        src/ImagePluginWrapper.cpp
        src/AudioPluginWrapper.cpp
        src/SentencePluginWrapper.cpp
        src/FormatProcessorPluginWrapper.cpp)

target_include_directories(client_plugin_wrappers PRIVATE
        include
        src)

target_include_directories(client_plugin_wrappers PUBLIC include)

target_link_libraries(client_plugin_wrappers PUBLIC connection)