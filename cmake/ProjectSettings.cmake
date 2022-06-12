# Generate compile_commands.json to make it easier to work with clang based tools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
#   add_compile_options(-fcolor-diagnostics)
# elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
#   add_compile_options(-fdiagnostics-color=always)
# else()
#   message(STATUS "No colored compiler diagnostic set for '${CMAKE_CXX_COMPILER_ID}' compiler.")
# endif()


if(ENABLE_UNITY)
  set(CMAKE_UNITY_BUILD ON)
endif()


if(ENABLE_IPO)
  include(CheckIPOSupported)
  check_ipo_supported(
    RESULT result
    OUTPUT output)
  if(result)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
  else()
    message(SEND_ERROR "IPO is not supported: ${output}")
  endif()
endif()

if(TURN_OFF_ASSERTS)
  add_compile_definitions(NDEBUG)
endif()

if(ENABLE_COVERAGE_TESTS)
  if(MSVC)
    message(SEND_ERROR "Currently coverage tests are not supported for MSVC")
  elseif(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    add_compile_options(--coverage -O0 -g)
    add_link_options(--coverage)
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-fprofile-arcs -ftest-coverage)
    add_link_options(-lgcov --coverage)
  endif()
endif()

function(enable_ccache_globally)
  if(ENABLE_CCACHE)
    find_program(CCACHE ccache)
    if(CCACHE)
      set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    else()
      message(AUTHOR_WARNING "ccache requested but not found")
    endif()
  endif()
endfunction()
