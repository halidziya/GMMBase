cmake_minimum_required(VERSION 2.6)
project(GMMBase)

macro(use_cxx11)
    if (CMAKE_VERSION VERSION_LESS "3.1")
        if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
            set (CMAKE_CXX_FLAGS "--std=gnu++11 ${CMAKE_CXX_FLAGS}")
        endif ()
    else ()
        set (CMAKE_CXX_STANDARD 11)
    endif ()
endmacro(use_cxx11)


set(CMAKE_CXX_STANDARD 11)
use_cxx11()


ADD_LIBRARY( GMMBase STATIC
Algorithms.cpp
DataSet.h
Global.h
Algorithms.h
GMMBase.h  
DataSet.cpp
Global.cpp
)


TARGET_LINK_LIBRARIES( GMMBase )
INCLUDE_DIRECTORIES(../FastMat/)
LINK_DIRECTORIES(../FastMat)
find_package (Threads)
TARGET_LINK_LIBRARIES(GMMBase FastMat)
TARGET_LINK_LIBRARIES (GMMBase ${CMAKE_THREAD_LIBS_INIT})
