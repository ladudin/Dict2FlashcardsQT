add_library(plugins_provider plugins_provider.cpp)
target_include_directories(plugins_provider PUBLIC
    ./
)

target_link_libraries(plugins_provider
    plugins_loader
)
