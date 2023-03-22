cmake_minimum_required(VERSION 3.6)
project(homework)

set(CMAKE_CXX_STANDARD 17)
set(
        SOURCE_FILES
        src/utilities.cpp
        src/utilities.hpp
        src/main.cpp
)

add_executable(homework ${SOURCE_FILES})
