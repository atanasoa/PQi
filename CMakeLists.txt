cmake_minimum_required(VERSION 2.8.6)
PROJECT(PQi)

# Cmake modules/macros are in a subdirectory to keep this file cleaner
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# enable the corresponding languages to do the compiler detection

#clustering sources
FILE(GLOB_RECURSE PQI_SRC src/*.cpp)

#include commons
INCLUDE_DIRECTORIES(commons)
INCLUDE_DIRECTORIES(src)
SET(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}/bin")




ADD_LIBRARY(pqi STATIC ${PQI_SRC} )

