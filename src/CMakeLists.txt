set(SOURCES
  window.cpp
)

set(BINDINGS
  ../../bindings/imgui_impl_glfw.cpp
  ../../bindings/imgui_impl_opengl3.cpp
)

add_executable(${PROJECT_NAME}
  ${SOURCES}
  ${BINDINGS}
  main.cpp
  draw.cpp
)

find_package(Threads)
find_package(box2d)
find_package(imgui)
find_package(glfw3)
find_package(glad)
find_package(fmt)
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC Threads::Threads box2d::box2d glfw::glfw imgui::imgui glad::glad fmt::fmt)

