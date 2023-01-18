cmake_minimum_required(VERSION 2.8)

project(MyProject)

include_directories(include)

add_executable(battaglia_navale
    src/main.cpp
)

add_executable(replay
    src/main-replay.cpp
)

SET(GCC_COVERAGE_COMPILE_FLAGS "g- O2-")