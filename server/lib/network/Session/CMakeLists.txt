add_library(session Session.cpp)
target_include_directories(session PUBLIC
    ./
)

target_link_libraries(session
    response_generators
)
