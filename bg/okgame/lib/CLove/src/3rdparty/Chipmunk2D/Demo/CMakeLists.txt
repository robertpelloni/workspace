cmake_minimum_required(VERSION 3.5)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

set(chipmunk_demos_include_dirs
  ${chipmunk_SOURCE_DIR}/include/chipmunk
  ${GLEW_INCLUDE_DIR}
  ${OPENGL_INCLUDE_DIR}
)

set(chipmunk_demos_libraries
  chipmunk_static
  ${GLEW_LIBRARIES}
  ${OPENGL_LIBRARIES}
)

file(GLOB chipmunk_demos_source_files "*.c")

include_directories(${chipmunk_demos_include_dirs})
add_executable(chipmunk_demos ${chipmunk_demos_source_files})
target_link_libraries(chipmunk_demos ${chipmunk_demos_libraries})

if(INSTALL_DEMOS)
  install(TARGETS chipmunk_demos RUNTIME DESTINATION bin)
endif(INSTALL_DEMOS)
