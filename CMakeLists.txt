cmake_minimum_required(VERSION 3.13)
project(Utilities)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

include_directories($(CMAKE_SOURCE_DIR))
include_directories(include)

add_executable(main main.cpp error_handling/exceptions.cpp include/fmt/format.cc include/fmt/posix.cc)