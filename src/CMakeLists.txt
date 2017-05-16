SET (this_target diffusion-solver)

# Add directories for headers
INCLUDE_DIRECTORIES(
    ./
)

# select all c++ files as CPP
FILE (GLOB CPP "*.cpp")

# remove Main.cpp from files -- although it should work without it, glob-ing
# is necessary to remove it.
FILE(GLOB MAIN "Main.cpp")
LIST(REMOVE_ITEM CPP ${MAIN})

# Select all header files
FILE(GLOB H "*.h")

# Add libraries to link command line
# WARNING: Order is significant in the list below
SET (LIBS
    ${CMAKE_THREAD_LIBS_INIT}
)
if (UNIX)
    LIST( APPEND LIBS m) # math library
endif()

# setup binary ################################################################

# generate binary
ADD_EXECUTABLE(${this_target}_bin ${CPP} "Main.cpp")

SET_TARGET_PROPERTIES(${this_target}_bin PROPERTIES OUTPUT_NAME ${this_target})

# set libraries to link against
TARGET_LINK_LIBRARIES(${this_target}_bin ${LIBS})

# Add dependent libraries
#ADD_DEPENDENCIES(${this_target}_bin)

# Specify output folders
SET_TARGET_PROPERTIES( ${this_target}_bin
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# setup library ###############################################################

# generate static library
ADD_LIBRARY(${this_target} STATIC ${CPP})
SET_TARGET_PROPERTIES(${this_target} PROPERTIES OUTPUT_NAME ${this_target})

# Specify output folders
SET_TARGET_PROPERTIES( ${this_target}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

# Setup parameters for IDE generation #########################################
PROJECT(${this_target})
SOURCE_GROUP(Headers FILES ${H})
SOURCE_GROUP(CPP FILES ${CPP} "Main.cpp")

# add test directory
ADD_SUBDIRECTORY(test)
