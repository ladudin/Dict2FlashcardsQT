set(LANG_SOURCE
    scaner.cpp
    parcer.cpp
    interpreter.cpp
    classes.cpp
)

add_library(query_lang ${LANG_SOURCE})
target_include_directories(query_lang PUBLIC ./)

add_executable(query_lang_main main.cpp)
target_link_libraries(query_lang_main query_lang)