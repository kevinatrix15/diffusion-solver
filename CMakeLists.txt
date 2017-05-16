cmake_minimum_required(VERSION 2.8)

PROJECT(diffusion-solver)
ENABLE_TESTING()

# Set the CMAKE source directory
SET(CONFIG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/CMake CACHE FILEPATH "Directory containing project configuration settings")

# set c++ options for whole project
# C++ compile options
if (UNIX)
    ADD_COMPILE_OPTIONS(-std=c++11)
elseif(MSVC)
    ADD_DEFINITIONS(
        -D_CONSOLE
        -DWIN64
        )
    # Remove run-time type information (RTTI) flag (all configurations)
    STRING(REPLACE "/GR" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
    # Enable minimal rebuild (Debug)
    ADD_COMPILE_OPTIONS("$<$<CONFIG:DEBUG>:/Gm>")
    # Enable global optimization (Release)
    ADD_COMPILE_OPTIONS("$<$<CONFIG:RELEASE>:/GL>")
    # Enable function level link (Release)
    ADD_COMPILE_OPTIONS("$<$<CONFIG:RELEASE>:/Gy>")
endif()

# Add include directories

# Find a threading implementation #############################################

FIND_PACKAGE(Threads)

FIND_PACKAGE(OpenMP)
IF(OPENMP_FOUND)
  set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
ENDIF()

# Enable all possible warnings ################################################

# TODO: Enable -pedantic NVCC has been removed.

# C FLAGS
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wextra")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wconversion")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pedantic")

# CXX FLAGS
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wconversion")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -pedantic")

# Set warnings as errors ######################################################

# C FLAGS
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror")

# CXX FLAGS
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")

# Set debug flags

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")

# Set coverage flags ##########################################################

# C FLAGS
set(CMAKE_C_FLAGS_COVERAGE "-fprofile-arcs -ftest-coverage -fPIC -O0")

# CXX FLAGS
set(CMAKE_CXX_FLAGS_COVERAGE "-fprofile-arcs -ftest-coverage -fPIC -O0")

# Handle configurations #######################################################

ADD_SUBDIRECTORY(src)
