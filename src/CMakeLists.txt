set(SOURCES
  hello.cpp
)

add_executable(${PROJECT_NAME}
  ${SOURCES}
  main.cpp
)

find_package(box2d)
find_package(Threads)
target_link_libraries(${PROJECT_NAME} box2d::box2d Threads::Threads)
