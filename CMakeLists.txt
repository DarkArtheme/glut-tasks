cmake_minimum_required(VERSION 3.21)
project(OpenGL)

set(CMAKE_CXX_STANDARD 20)


set(GLUT_PATH C:/SDK/glut-3.7.6-bin)
include_directories(${GLUT_PATH})
add_custom_target(glut COMMAND ${CMAKE_COMMAND} -E copy ${GLUT_PATH}/glut32.dll ${CMAKE_BINARY_DIR})
set(OPENGL_LIBS glut32)

add_executable(OpenGL lab4.cpp)
target_link_libraries(OpenGL ${OPENGL_LIBS})
add_dependencies(OpenGL glut)