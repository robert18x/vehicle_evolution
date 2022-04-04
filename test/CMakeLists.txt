cmake_minimum_required(VERSION 3.16)

set(TESTS ${PROJECT_NAME}_test)

set(TEST_SOURCES
  main.cpp
  test.cpp
)

set(PROJECT_SOURCES
  ../src/hello.cpp
)

include_directories( .
  ${PROJECT_SOURCE_DIR}/src
)

add_executable(${TESTS}
  ${TEST_SOURCES}
  ${PROJECT_SOURCES}
)

set(CMAKE_BUILD_RPATH_USE_ORIGIN ON)

find_package(box2d)
find_package(GTest)
find_package(Threads)
target_link_libraries(${TESTS} GTest::GTest box2d::box2d Threads::Threads)

add_test(NAME ${TESTS} COMMAND ${TESTS})
