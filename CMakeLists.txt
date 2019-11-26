cmake_minimum_required(VERSION 3.13)
project(Utilities)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

include_directories($(CMAKE_SOURCE_DIR))
include_directories(.)
include_directories(include/)

#find_package(glm REQUIRED)
#include_directories(${GLM_INCLUDE_DIRS})
add_executable(main main.cpp
        various/XMLUtils.cpp
        #error_handling/exceptions.cpp
        include/fmt/format.cc include/fmt/posix.cc
        graphics/Geometry.cpp
        graphics/ViewFrustum.cpp
        time/FPSCounter.cpp
        include/tinyxml2/tinyxml2.cpp various/XMLSerialisation.h config/XmlConfig.tpp reactive/Binding.h reactive/OneWayBinding.h reactive/TwoWayBinding.h)