cmake_minimum_required(VERSION 3.6)
project(homework)

set(CMAKE_CXX_STANDARD 17)
set(COMPILE_FLAGS "-Wall -Werror -Wpedantic -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILE_FLAGS}")
set(SRCS ${PROJECT_SOURCE_DIR}/src/main.cpp
         ${PROJECT_SOURCE_DIR}/src/ioperation.cpp
         ${PROJECT_SOURCE_DIR}/src/parser.cpp)

add_executable(homework ${SRCS})

target_include_directories(homework PUBLIC ${PROJECT_SOURCE_DIR}/include)
