
cmake_minimum_required(VERSION 3.0.0)
project(X11GL VERSION 0.1.0)

# Compile and build
#   cmake .
#   cmake --build . 
# Pack result
#   cpack
# Lazy
#   cmake . && cmake --build . && cpack

find_package(X11 REQUIRED)
message(STATUS "X11 library path: ${X11_LIB_DIR}")

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
message(STATUS "OpenGL library path: ${OPENGL_LIB_DIR}")

#file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/*.c ${CMAKE_SOURCE_DIR}/*.cpp)
#file(GLOB_RECURSE HEADER_FILES ${CMAKE_SOURCE_DIR}/*.h ${CMAKE_SOURCE_DIR}/*.hpp)

include_directories( ${OPENGL_INCLUDE_DIRS} ${X11_INCLUDE_DIRS} )

add_executable(X11GL 
    src/main.cpp
    #${SOURCE_FILES}    
    src/x11gl/X11GL.cpp
)

target_link_libraries(X11GL ${OPENGL_LIBRARIES} ${X11_LIBRARIES} )
#target_link_libraries(X11GL ${OPENGL_LIB_DIR} ${X11_LIB_DIR} )

# include(CTest)u
# enable_testing()


# https://thelinuxcode.com/cmake-cpack-linux/ 

# Enable packaging
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# Valid Generators
# DEB - For Debian/Ubuntu packages.
# RPM - For RedHat/CentOS packages.
# ZIP - For cross-platform zip files.
# NSIS - For Windows installers.
# DragNDrop - For macOS bundles.
set(CPACK_GENERATOR "DEB")
# for DEB
set(CPACK_DEBIAN_PACKAGE_DEPENDS "vulkan")
set(CPACK_PACKAGE_CONTACT "Me")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Me again")
set(CPACK_PACKAGE_DESCRIPTION "Just learning this...")
set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${CMAKE_CURRENT_SOURCE_DIR}/Debian/postinst")

# Include CPack
include(CPack)