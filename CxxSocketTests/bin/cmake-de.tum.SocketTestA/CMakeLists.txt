cmake_minimum_required(VERSION 2.8.6)
PROJECT(SocketTestA)

find_package(JNI)

if (JNI_FOUND)
    message (STATUS "JNI_INCLUDE_DIRS=${JNI_INCLUDE_DIRS}")
    message (STATUS "JNI_LIBRARIES=${JNI_LIBRARIES}")
    INCLUDE_DIRECTORIES(${JNI_INCLUDE_DIRS})
endif()

include(CMakeForceCompiler)	
IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
CMAKE_FORCE_CXX_COMPILER(icpc "Intel Cxx Compiler") 
CMAKE_FORCE_C_COMPILER(icc "Intel C Compiler")     
CMAKE_FORCE_Fortran_COMPILER(ifort "Intel Fortran Compiler")
ELSE()
CMAKE_FORCE_CXX_COMPILER(icl.exe "Intel Cxx Compiler") 
CMAKE_FORCE_C_COMPILER(icl.exe "Intel C Compiler")     
CMAKE_FORCE_Fortran_COMPILER(ifort.exe "Intel Fortran Compiler")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")   

message(STATUS ${CMAKE_Fortran_COMPILER})
message(STATUS ${CMAKE_CXX_COMPILER})
message(STATUS ${CMAKE_C_COMPILER})


INCLUDE_DIRECTORIES(../../commons)
INCLUDE_DIRECTORIES(../../src)
INCLUDE_DIRECTORIES(../../components/java)
SET(EXECUTABLE_OUTPUT_PATH "../../native")
SET(LIBRARY_OUTPUT_PATH  "../../native/lib")



SET(SRC_COMP_EXEC
    ../../components/java/de/tum/SocketTestAC2CxxProxy.cpp 
	../../components/java/de/tum/SocketTestAAbstractImplementation.cpp
	../../src/de/tum/SocketTestAImplementation.cpp
	
	
)

SET(SRC_COMP_LIB
	../../components/java/de/tum/SocketTestAAbstractImplementation.cpp
     ../../src/de/tum/SocketTestAImplementation.cpp
     ../../components/java/de/tum/SocketTestAC2CxxProxy.cpp)

 	 
ADD_EXECUTABLE(SocketTestA ${SRC_COMP_EXEC} )
ADD_LIBRARY(SocketTestA-dev STATIC ${SRC_COMP_LIB} )
target_link_libraries(SocketTestA pthread)