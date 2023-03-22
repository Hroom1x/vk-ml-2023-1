cmake_minimum_required(VERSION 3.6)
project(homework)

set(CMAKE_CXX_STANDARD 17)
set(COMPILE_FLAGS "-Wall -Werror -Wpedantic -Wextra")
set(
        SOURCE_FILES
        src/utilities.cpp
        src/utilities.hpp
        src/main.cpp
)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILE_FLAGS}")

add_executable(homework ${SOURCE_FILES})
