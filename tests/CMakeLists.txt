add_definitions(-DUNIT_TESTS)
add_executable(hw16_testsNew
        ../q1/stack.h
        ../q1/main.cpp
        stack_tests.cpp
        q1_tests.cpp
        tests_main.cpp
)
