cmake_minimum_required(VERSION 3.11)

#set the project name
project(LibSortTest)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(../../include
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/source
  ./)

file(GLOB all_SRCS
  "../../include/*.h"
  "../../include/*.hpp"
  "${PROJECT_SOURCE_DIR}/include/*.h"
  "${PROJECT_SOURCE_DIR}/include/*.hpp"
  "${PROJECT_SOURCE_DIR}/source/*.cpp"
  "${PROJECT_SOURCE_DIR}/*.cpp"
  "${PROJECT_SOURCE_DIR}/../../include/*.hpp"
  )

# Do the required setup for CMake
# Get the stuff we need to use Google Test...

#add the executable

add_executable(LibSortTest libsorttest.cpp)
