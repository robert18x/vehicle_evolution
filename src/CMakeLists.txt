set(SOURCES
  window.cpp
  world.cpp
  draw.cpp
  car.cpp
)

if(MSVC)
  set(BINDINGS
    ../out/build/bindings/imgui_impl_glfw.cpp
    ../out/build/bindings/imgui_impl_opengl3.cpp
  )
else()
  set(BINDINGS
    ../bindings/imgui_impl_glfw.cpp
    ../bindings/imgui_impl_opengl3.cpp
  )
endif()

add_executable(${PROJECT_NAME}
  ${SOURCES}
  ${BINDINGS}
  main.cpp
)

find_package(Threads)
find_package(box2d)
find_package(imgui)
find_package(glfw3)
find_package(glad)
find_package(fmt)
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC Threads::Threads box2d::box2d glfw::glfw imgui::imgui glad::glad fmt::fmt)

