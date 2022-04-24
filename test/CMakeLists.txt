cmake_minimum_required(VERSION 3.16)

set(TESTS ${PROJECT_NAME}_test)

set(TEST_SOURCES
  main.cpp
  test.cpp
)

set(PROJECT_SOURCES
  ../src/hello.cpp
)

set(BINDINGS
  ../../bindings/imgui_impl_glfw.cpp
  ../../bindings/imgui_impl_opengl3.cpp
)

include_directories( .
  ${PROJECT_SOURCE_DIR}/src
)

add_executable(${TESTS}
  ${TEST_SOURCES}
  ${PROJECT_SOURCES}
  ${BINDINGS}
)

set(CMAKE_BUILD_RPATH_USE_ORIGIN ON)

find_package(GTest)
find_package(Threads)
find_package(box2d)
find_package(imgui)
find_package(glfw3)
find_package(glad)
find_package(fmt)
target_link_libraries(${TESTS} GTest::GTest Threads::Threads box2d::box2d glfw::glfw imgui::imgui glad::glad fmt::fmt)

add_test(NAME ${TESTS} COMMAND ${TESTS})
