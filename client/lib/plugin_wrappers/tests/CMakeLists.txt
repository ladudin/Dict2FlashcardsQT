set(TEST_FILES src/BasicPluginWrapper_tests.cpp
        src/WordPluginWrapper_tests.cpp
        src/AudioPluginWrapper_tests.cpp
        src/ImagePluginWrapper_tests.cpp
        src/SentencePluginWrapper_tests.cpp
        src/FormatProcessorPluginWrapper_tests.cpp)

add_executable(plugin_wrappers_test ${TEST_FILES})

target_include_directories(plugin_wrappers_test PRIVATE include)

target_link_libraries(plugin_wrappers_test client_plugin_wrappers
        GTest::gtest_main)

add_test(plugin_wrappers_test plugin_wrappers_test)
