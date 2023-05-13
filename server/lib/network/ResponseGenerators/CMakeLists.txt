add_library(response_generators ResponseGenerators.cpp)
target_include_directories(response_generators
    PUBLIC
    ./
)
target_link_libraries(response_generators
    plugins_bundle
    plugins_provider
)
