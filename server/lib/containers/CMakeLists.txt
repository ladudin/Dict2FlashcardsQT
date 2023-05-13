add_library(containers containers.cpp)
target_include_directories(containers
    PUBLIC
    ./
    ${Boost_INCLUDE_DIRS}
    ${PYTHON_INCLUDE_DIRS}
)

target_link_libraries(
    containers
    py_exception_info
    ${Boost_LIBRARIES}
    ${PYTHON_LIBRARIES}
)
