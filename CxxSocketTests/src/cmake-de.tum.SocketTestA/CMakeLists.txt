cmake_minimum_required(VERSION 2.8.5)
PROJECT(SocketTestA)
include(CMakeForceCompiler)
find_package(JNI)

SET(PARALLEL "1" CACHE STRING "parallel mode")

if (JNI_FOUND)
    message (STATUS "JNI_INCLUDE_DIRS=${JNI_INCLUDE_DIRS}")
    message (STATUS "JNI_LIBRARIES=${JNI_LIBRARIES}")
    INCLUDE_DIRECTORIES(${JNI_INCLUDE_DIRS})
endif()


IF(PARALLEL)
    message (STATUS "Prorgam is able to run parallel") 
    add_definitions(-DPARALLEL)
    CMAKE_FORCE_CXX_COMPILER(mpicxx "mpi compiler") 
ENDIF()
set(CMAKE_CXX_FLAGS "-std=c++0x")
#no qt in parallel mode
IF(NOT PARALLEL)
IF(NOT VTK_BINARY_DIR)
FIND_PACKAGE(VTK)
IF(NOT VTK_DIR)
  MESSAGE(FATAL_ERROR "Please set VTK_DIR.")
ENDIF(NOT VTK_DIR)
INCLUDE(${VTK_USE_FILE})
ENDIF(NOT VTK_BINARY_DIR)

	
# use what QVTK built with
SET(QT_MOC_EXECUTABLE ${VTK_QT_MOC_EXECUTABLE} CACHE FILEPATH "")
SET(QT_UIC_EXECUTABLE ${VTK_QT_UIC_EXECUTABLE} CACHE FILEPATH "")
SET(QT_QMAKE_EXECUTABLE ${VTK_QT_QMAKE_EXECUTABLE} CACHE FILEPATH "")
FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE(${QT_USE_FILE})

# Use the include path and library for Qt that is used by VTK.
INCLUDE_DIRECTORIES(
  ${QT_INCLUDE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
)

SET(SimpleViewSrcs ../../src/de/tum/SimpleView.cxx ../../src/de/tum/vtkMyImageData.cxx )
SET(SimpleViewUI ../../src/de/tum/SimpleView.ui)
SET(SimpleViewHeaders ../../src/de/tum/SimpleView.h ../../src/de/tum/MyTimer.hpp ../../src/de/tum/vtkMyImageData.h)
SET(SimpleViewResources ../../src/de/tum/Icons/icons.qrc)

# The rest should just work (sure...)
QT4_WRAP_UI(UISrcs ${SimpleViewUI})
QT4_WRAP_CPP(MOCSrcs ${SimpleViewHeaders} )
QT4_ADD_RESOURCES(ResourceSrcs ${SimpleViewResources})
ENDIF(NOT PARALLEL)

	
IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
#CMAKE_FORCE_CXX_COMPILER(icpc "Intel Cxx Compiler") 
#CMAKE_FORCE_C_COMPILER(icc "Intel C Compiler")     
#CMAKE_FORCE_Fortran_COMPILER(ifort "Intel Fortran Compiler")
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

 	 
ADD_EXECUTABLE(SocketTestA ${SRC_COMP_EXEC} ${SimpleViewSrcs} ${UISrcs} ${MOCSrcs} ${ResourceSrcs})
ADD_LIBRARY(SocketTestA-dev STATIC ${SRC_COMP_LIB} )
IF(PARALLEL)
target_link_libraries(SocketTestA 
  pthread)
ENDIF(PARALLEL)
IF(NOT PARALLEL)
target_link_libraries(SocketTestA 
  pthread 
  QVTK
  ${QT_LIBRARIES}
  vtkRendering
  vtkGraphics
  vtkIO
  vtkCommon
  vtkInfovis
  vtkViews)
ENDIF(NOT PARALLEL)
