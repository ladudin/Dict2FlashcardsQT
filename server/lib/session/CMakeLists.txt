add_library(session session.cpp)
target_include_directories(session PUBLIC
    ./
    PRIVATE
    ${Boost_INCLUDE_DIRS}
    ${PYTHON_INCLUDE_DIRS}
)

target_link_libraries(session
    response_generators
    ${Boost_LIBRARIES}
    ${PYTHON_LIBRARIES}
)
