cmake_minimum_required(VERSION 2.8.6)
PROJECT(PQi)

# Cmake modules/macros are in a subdirectory to keep this file cleaner
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_CXX_FLAGS "-std=c++0x")
# enable the corresponding languages to do the compiler detection

#clustering sources
FILE(GLOB_RECURSE PQI_KERNEL_SRC src/*.cpp src/queries/*.cpp)

option(EXTERNAL_PEANO "Use external PEANO" ON)
if(EXTERNAL_PEANO)
	find_path(PEANO_INCLUDE_PATH "Peano/include")
	INCLUDE_DIRECTORIES(${PEANO_INCLUDE_PATH})
	set(PEANO_LIBDIR "")
	find_library(PEANO_LIB NAMES peano-dev PATHS ${PEANO_LIBDIR})
	set(PEANO_DIMENSIONS 2 CACHE STRING "number of dimensions")
	add_definitions(-DDim${PEANO_DIMENSIONS})

	option(PEANO_PARALLEL "shall we build a MPI enabled Peano")
	if (PEANO_PARALLEL)
	    find_package(MPI)
	    set(CMAKE_C_COMPILER ${MPI_C_COMPILER})
	    set(CMAKE_CXX_COMPILER ${MPI_CXX_COMPILER})
	    add_definitions(-DParallel)
	endif (PEANO_PARALLEL)

	option(PEANO_TBB "shall we build a TBB enabled Peano")
	if (PEANO_TBB)
	    #set(TBB_ROOT "/work/wittmanr/mytools/tbb41_20121003oss")
	    #set(TBB_INCLUDE_DIRS "${TBB_ROOT}/include")
	    #set(TBB_LIBRARY_DIRS "${TBB_ROOT}/build/linux_intel64_gcc_cc4.6_libc2.15_kernel3.7.1_release")
	    #set(TBB_LINK_FLAGS "-ltbb")

	    #include_directories(${TBB_INCLUDE_DIRS})
	    #link_directories(${TBB_LIBRARY_DIRS})
	    #add_definitions(-DSharedTBB)
	endif (PEANO_TBB)

	option(PEANO_ASSERTS "shall we build with Assertions enabled")
	if (PEANO_ASSERTS)
	    add_definitions(-DAsserts)
	endif (PEANO_ASSERTS)

	option(PEANO_TRACE "shall we build with trace enabled")
	if (PEANO_TRACE)
	     add_definitions(-DTrace)
	endif (PEANO_TRACE)

	option(PEANO_DEBUG "shall we build with Debug enabled")
	if (PEANO_DEBUG)
	    add_definitions(-DDebug)
	endif (PEANO_DEBUG)
else(EXTERNAL_PEANO)
	message(FATAL_ERROR "For this version of QC you need to enable external QC lib")
endif(EXTERNAL_PEANO)

#include commons
INCLUDE_DIRECTORIES(commons)
INCLUDE_DIRECTORIES(src)
SET(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}/bin")




ADD_LIBRARY(pqi STATIC ${PQI_KERNEL_SRC} )
target_link_libraries(pqi ${PEANO_LIB} std++)
