add_library(plugins_provider plugins_provider.cpp)
target_include_directories(plugins_provider PUBLIC
    ./
    PRIVATE
    ${Boost_INCLUDE_DIRS}
    ${PYTHON_INCLUDE_DIRS}
)

target_link_libraries(plugins_provider
    plugins_loader
    ${Boost_LIBRARIES}
    ${PYTHON_LIBRARIES}
)
