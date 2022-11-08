cmake_minimum_required(VERSION 3.21)
project(OpenGL)

set(CMAKE_CXX_STANDARD 20)


set(GLUT_PATH C:/SDK/glut-3.7.6-bin)
include_directories(${GLUT_PATH})
add_custom_target(glut COMMAND ${CMAKE_COMMAND} -E copy ${GLUT_PATH}/glut32.dll ${CMAKE_BINARY_DIR})
set(OPENGL_LIBS glut32)

# Generate targets for each single file
file(GLOB APP_SOURCES *.cpp */*.cpp)
foreach (file ${APP_SOURCES})
    get_filename_component(filename ${file} NAME_WE)
    message("${filename}")
    add_executable(${filename} ${file})
    target_link_libraries(${filename} ${OPENGL_LIBS})
    add_dependencies(${filename} glut)
endforeach (file ${APP_SOURCES})