
cmake_minimum_required(VERSION 3.0.0)
project(X11GL VERSION 0.1.0)


find_package(X11 REQUIRED)
message(STATUS "X11 library path: ${X11_LIB_DIR}")

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
message(STATUS "OpenGL library path: ${OPENGL_LIB_DIR}")

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/*.c ${CMAKE_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${CMAKE_SOURCE_DIR}/*.h ${CMAKE_SOURCE_DIR}/*.hpp)

include_directories( ${OPENGL_INCLUDE_DIRS} ${X11_INCLUDE_DIRS} )

add_executable(X11GL 
    src/main.cpp
    #${SOURCE_FILES}    
    src/x11gl/X11GL.cpp
    src/x11gl/loader.cpp
    src/x11gl/gears.cpp
)

target_link_libraries(X11GL ${OPENGL_LIBRARIES} ${X11_LIBRARIES} )
#target_link_libraries(X11GL ${OPENGL_LIB_DIR} ${X11_LIB_DIR} )

# include(CTest)u
# enable_testing()

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)