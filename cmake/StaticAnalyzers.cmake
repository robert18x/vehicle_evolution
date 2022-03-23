if(ENABLE_CPPCHECK)
  find_program(CPPCHECK cppcheck)
  if(CPPCHECK)
    set(CMAKE_CXX_CPPCHECK
      ${CPPCHECK}
        --suppress=missingInclude missingIncludeSystem
        --enable=all
        -I ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/tests
        --inline-suppr
        --inconclusive
        --project=${CMAKE_BINARY_DIR}/compile_commands.json)
    if(WARNINGS_AS_ERRORS)
      list(APPEND CMAKE_CXX_CPPCHECK --error-exitcode=2)
    endif()
  else()
    message(AUTHOR_WARNING "cppcheck requested but executable not found")
  endif()
endif()

if(ENABLE_CLANG_TIDY)
  find_program(CLANGTIDY clang-tidy)
  if(CLANGTIDY)
    set(CMAKE_CXX_CLANG_TIDY ${CLANGTIDY} -extra-arg=-Wno-unknown-warning-option)
    if(WARNINGS_AS_ERRORS)
      list(APPEND CMAKE_CXX_CLANG_TIDY -warnings-as-errors=*)
    endif()
  else()
    message(AUTHOR_WARNING "clang-tidy requested but executable not found")
  endif()
endif()
