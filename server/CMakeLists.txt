find_package(Boost COMPONENTS filesystem system date_time python REQUIRED)
message("Include dirs of boost: " ${Boost_INCLUDE_DIRS})
message("Libs of boost: " ${Boost_LIBRARIES})

find_package(PythonLibs REQUIRED)
message("Include dirs of Python: " ${PYTHON_INCLUDE_DIRS})
message("Libs of Python: " ${PYTHON_LIBRARIES})

add_subdirectory(lib)

add_executable(server_main main.cpp)
target_link_libraries(server_main
    plugin_server
)
