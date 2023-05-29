set(LANG_HEADERS
    include/scaner.hpp
    include/parcer.hpp
    include/interpreter.hpp
    include/classes.hpp
    include/exception.hpp
)

set(LANG_SOURCE
    src/scaner.cpp
    src/parcer.cpp
    src/interpreter.cpp
    src/classes.cpp
    src/exception.cpp
)

add_library(query_lang ${LANG_SOURCE} ${LANG_HEADERS})
target_include_directories(query_lang PUBLIC ./include)

add_executable(query_lang_main src/main.cpp)
target_link_libraries(query_lang_main query_lang)

add_library(querying src/querying.cpp)
target_include_directories(querying PUBLIC ./include)
target_link_libraries(querying query_lang)