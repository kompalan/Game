cmake_minimum_required(VERSION 3.20)
project(Game)
set(APPLICATION_LIBRARY GameLib)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(${APPLICATION_LIBRARY})
include_directories(${APPLICATION_LIBRARY})

set(SOURCE_FILES main.cpp)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(Tests)
add_subdirectory(include/glm)
add_subdirectory(include/glfw-3.3.5)

#file(COPY logs/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
# Copy resources into output directory
file(COPY shaders/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

if(APPLE)
    # When building for MacOS, also copy resources into the bundle resources
    set(RESOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.app/Contents/Resources)
    file(COPY shaders/ DESTINATION ${RESOURCE_DIR}/)
endif()

add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE ${SOURCE_FILES})

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${GLEW_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES} glfw glm ${APPLICATION_LIBRARY})
