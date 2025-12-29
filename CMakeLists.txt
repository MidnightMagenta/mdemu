cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(PROJECT_NAME "6502")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(${PROJECT_NAME})

add_executable("6502"
    src/main.cc
    src/cpu.cc
    src/machine_NES.cc

    include/cpu.h
    include/memory.h
    include/types.h
    include/units.h
    include/machine_NES.h
)

target_include_directories("6502" PRIVATE include)
