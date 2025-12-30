cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(PROJECT_NAME "6502")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE "debug")

project(${PROJECT_NAME})

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)

# Prevent overriding your compiler flags
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_custom_target(compile_tests ALL
    COMMENT "Compiling tests"
    COMMAND ${CMAKE_MAKE_PROGRAM} -f ${CMAKE_SOURCE_DIR}/tests/Makefile
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/tests
)

add_library("6502-lib" STATIC
    src/cpu.cc
    src/bus.cc
    src/machine_debug.cc

    include/cpu.h
    include/memory.h
    include/types.h
    include/units.h
    include/machine_debug.h
)

target_include_directories("6502-lib" PRIVATE include)

add_executable("6502"
    src/main.cc
)

target_include_directories("6502" PRIVATE include)
target_link_libraries("6502" PRIVATE "6502-lib")
add_dependencies("6502" compile_tests)

enable_testing()

add_executable("6502-mach-dbg-tests"
    tests/mach_dbg/unit/sanity_test.cc
)

target_link_libraries("6502-mach-dbg-tests" PRIVATE
    GTest::gtest_main
    "6502-lib"
)
target_include_directories("6502-mach-dbg-tests" PRIVATE include)

include(GoogleTest)
gtest_discover_tests("6502-mach-dbg-tests"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
