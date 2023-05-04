add_library(connection connection.cpp)
target_include_directories(connection PUBLIC ./)
target_link_libraries(connection response_generators)
