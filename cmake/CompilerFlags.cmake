if(ENABLE_OPTIMALIZATION)
  set(MSVC_OPTIMALIZATION
    /O2
  )

  set(GCC_OPTIMALIZATION
    -O3
  )

  set(CLANG_OPTIMALIZATION
    -O3
  )

  if(MSVC)
    set(COMPILER_FLAGS ${MSVC_OPTIMALIZATION})
  elseif(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    set(COMPILER_FLAGS ${CLANG_OPTIMALIZATION})
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(COMPILER_FLAGS ${GCC_OPTIMALIZATION})
  else()
    message(AUTHOR_WARNING "Compiler flag set for '${CMAKE_CXX_COMPILER_ID}' compiler.")
  endif()

  add_compile_options(${COMPILER_FLAGS})
endif()



if(ENABLE_DEBUG)
  set(MSVC_DEBUG
    /DEBUG
  )

  set(GCC_DEBUG
    -ggdb
  )

  set(CLANG_DEBUG
    -ggdb
  )

  if(MSVC)
    set(COMPILER_FLAGS ${MSVC_DEBUG})
  elseif(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    set(COMPILER_FLAGS ${CLANG_DEBUG})
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(COMPILER_FLAGS ${GCC_DEBUG})
  else()
    message(AUTHOR_WARNING "Compiler flag set for '${CMAKE_CXX_COMPILER_ID}' compiler.")
  endif()

  add_compile_options(${COMPILER_FLAGS})
endif()
