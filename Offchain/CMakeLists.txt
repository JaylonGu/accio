cmake_minimum_required(VERSION 3.23)
project(HUB C)

set(CMAKE_C_STANDARD 11)

# add extra include directories
set(INCLUDE /usr/local/include ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_BINARY_DIR}/include)
include_directories(${INCLUDE})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)
# file(GLOB includes "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")