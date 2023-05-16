add_executable(python_loading main.cpp)

find_package(Boost COMPONENTS filesystem system date_time python REQUIRED)
message("Include dirs of boost: " ${Boost_INCLUDE_DIRS})
message("Libs of boost: " ${Boost_LIBRARIES})

find_package(PythonLibs REQUIRED)
message("Include dirs of Python: " ${PYTHON_INCLUDE_DIRS})
message("Libs of Python: " ${PYTHON_LIBRARIES})

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${PYTHON_INCLUDE_DIRS}
)

target_link_libraries(python_loading
    ${Boost_LIBRARIES}
    ${PYTHON_LIBRARIES}
)
