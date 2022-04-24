cmake_minimum_required(VERSION 3.16)

project(vehicle_evolution CXX)

set(CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)

option(ENABLE_UNITY_BUILD "Enable unity build" ON)
option(ENABLE_CCACHE "Enable compiler cache" ON)
option(USE_TBB "Use tbb" OFF)
option(BUILD_DOC "Build documentation" ON)

include(cmake/PreventInSourceBuilds.cmake)
assure_out_of_source_builds()

include(CTest)
# include(cmake/Doxygen.cmake)
include(cmake/CompilerFlags.cmake)


if(NOT CMAKE_BUILD_TYPE)
  message(STATUS "No build type was specified. Choosing debug build")
  set(CMAKE_BUILD_TYPE "Debug")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  option(ENABLE_OPTIMALIZATION "Add set of optimization flags" ON)
  option(ENABLE_IPO "Enable Interprocedural Optimization, aka Link Time Optimization (LTO)" ON)
  option(TURN_OFF_ASSERTS "Ommit all asserts in program" ON)

elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
  option(ENABLE_DEBUG "Add set of debug flags" ON)
  option(ENABLE_WARNINGS "Add set of warnings flags" ON)
  option(WARNINGS_AS_ERRORS "Treat warnings as errors" OFF)
  option(ENABLE_CPPCHECK "Enable static analysis with cppcheck" ON)
  option(ENABLE_CLANG_TIDY "Enable static analysis with clang-tidy" ON)
  option(ENABLE_TESTING "Enable testing" ON)
  option(ENABLE_COVERAGE_TESTS "Enable coverage tests" OFF)
endif()

include(cmake/ProjectSettings.cmake)
include(cmake/CompilerFlags.cmake)
include(cmake/CompilerWarnings.cmake)
# include(cmake/StaticAnalyzers.cmake)
include(cmake/Conan.cmake)

add_subdirectory(src)

if(ENABLE_TESTING)
  add_subdirectory(test)
endif()

enable_ccache_globally()


