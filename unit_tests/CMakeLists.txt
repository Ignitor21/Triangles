add_executable(unit_tests unit_test.cpp)

target_link_libraries(unit_tests PRIVATE ${GTEST_LIBRARIES} PRIVATE ${CMAKE_THREAD_LIBS_INIT})

gtest_discover_tests(unit_tests)