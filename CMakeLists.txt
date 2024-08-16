
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


INSTALL(FILES res/FooIcon.png DESTINATION /foo/Icons)
# INSTALL(TARGETS Schrollidge DESTINATION /foo/Applications/)

# https://thelinuxcode.com/cmake-cpack-linux/ 

# Enable packaging
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# Valid Generators
#   7Z                           = 7-Zip file format
#   DEB                          = Debian packages
#   External                     = CPack External packages
#   IFW                          = Qt Installer Framework
#   NSIS                         = Null Soft Installer
#   NSIS64                       = Null Soft Installer (64-bit)
#   NuGet                        = NuGet packages
#   RPM                          = RPM packages
#   STGZ                         = Self extracting Tar GZip compression
#   TBZ2                         = Tar BZip2 compression
#   TGZ                          = Tar GZip compression
#   TXZ                          = Tar XZ compression
#   TZ                           = Tar Compress compression
#   TZST                         = Tar Zstandard compression
#   ZIP                          = ZIP file format
#   NSIS - For Windows installers.
#   DragNDrop - For macOS bundles.
set(CPACK_GENERATOR "TGZ")
# for DEB
# set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "schrollidge")
set(CPACK_PACKAGE_CONTACT "Me")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Me again")
set(CPACK_PACKAGE_DESCRIPTION "The Schrollidge")
set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${CMAKE_CURRENT_SOURCE_DIR}/Debian/postinst")

# Include CPack
include(CPack)