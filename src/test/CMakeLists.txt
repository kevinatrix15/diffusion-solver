SET (this_target diffusion-solver.Test)

# Add include directories
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/googletest/include)

# add gtest link directories
if (UNIX)
    execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion
            OUTPUT_VARIABLE GCC_VERSION)
    if (GCC_VERSION VERSION_GREATER 6.0 OR GCC_VERSION VERSION_EQUAL 6.0)
      LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/googletest/linux/g++6)
    elseif (GCC_VERSION VERSION_GREATER 5.0 OR GCC_VERSION VERSION_EQUAL 5.0)
      LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/googletest/linux/g++5)
    else()
      LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/googletest/linux)
    endif()
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
    LINK_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/googletest/x64/Release)
endif()

# Add link directories
LINK_DIRECTORIES(
)

# Select all c++ files
FILE (GLOB CPP "*.cpp")

# Set binary for tests creation
ADD_EXECUTABLE(${this_target} ${CPP} )

# Set libraries needed by the test binary
TARGET_LINK_LIBRARIES( ${this_target}
  diffusion-solver
  ${LIBS}
  gtest
  gtest_main
  gmock
)

# Set projects this test depends on
ADD_DEPENDENCIES(${this_target}
    diffusion-solver
)

# Set the test binary to run
ADD_TEST(NAME ${this_target} COMMAND ${this_target} --gtest_output=xml:./test-output.xml)


# Setup IDE parameters
PROJECT(${this_target})
SOURCE_GROUP(CPP FILES ${CPP})
