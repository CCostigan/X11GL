# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /media/groot/Untitled/AllNew2021/X11GL

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /media/groot/Untitled/AllNew2021/X11GL

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target package_source
package_source:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Run CPack packaging tool for source..."
	/usr/bin/cpack --config ./CPackSourceConfig.cmake /media/groot/Untitled/AllNew2021/X11GL/CPackSourceConfig.cmake
.PHONY : package_source

# Special rule for the target package_source
package_source/fast: package_source

.PHONY : package_source/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target package
package: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Run CPack packaging tool..."
	/usr/bin/cpack --config ./CPackConfig.cmake
.PHONY : package

# Special rule for the target package
package/fast: package

.PHONY : package/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /media/groot/Untitled/AllNew2021/X11GL/CMakeFiles /media/groot/Untitled/AllNew2021/X11GL/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /media/groot/Untitled/AllNew2021/X11GL/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named X11GL

# Build rule for target.
X11GL: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 X11GL
.PHONY : X11GL

# fast build rule for target.
X11GL/fast:
	$(MAKE) -f CMakeFiles/X11GL.dir/build.make CMakeFiles/X11GL.dir/build
.PHONY : X11GL/fast

src/main.o: src/main.cpp.o

.PHONY : src/main.o

# target to build an object file
src/main.cpp.o:
	$(MAKE) -f CMakeFiles/X11GL.dir/build.make CMakeFiles/X11GL.dir/src/main.cpp.o
.PHONY : src/main.cpp.o

src/main.i: src/main.cpp.i

.PHONY : src/main.i

# target to preprocess a source file
src/main.cpp.i:
	$(MAKE) -f CMakeFiles/X11GL.dir/build.make CMakeFiles/X11GL.dir/src/main.cpp.i
.PHONY : src/main.cpp.i

src/main.s: src/main.cpp.s

.PHONY : src/main.s

# target to generate assembly for a file
src/main.cpp.s:
	$(MAKE) -f CMakeFiles/X11GL.dir/build.make CMakeFiles/X11GL.dir/src/main.cpp.s
.PHONY : src/main.cpp.s

src/x11gl/X11GL.o: src/x11gl/X11GL.cpp.o

.PHONY : src/x11gl/X11GL.o

# target to build an object file
src/x11gl/X11GL.cpp.o:
	$(MAKE) -f CMakeFiles/X11GL.dir/build.make CMakeFiles/X11GL.dir/src/x11gl/X11GL.cpp.o
.PHONY : src/x11gl/X11GL.cpp.o

src/x11gl/X11GL.i: src/x11gl/X11GL.cpp.i

.PHONY : src/x11gl/X11GL.i

# target to preprocess a source file
src/x11gl/X11GL.cpp.i:
	$(MAKE) -f CMakeFiles/X11GL.dir/build.make CMakeFiles/X11GL.dir/src/x11gl/X11GL.cpp.i
.PHONY : src/x11gl/X11GL.cpp.i

src/x11gl/X11GL.s: src/x11gl/X11GL.cpp.s

.PHONY : src/x11gl/X11GL.s

# target to generate assembly for a file
src/x11gl/X11GL.cpp.s:
	$(MAKE) -f CMakeFiles/X11GL.dir/build.make CMakeFiles/X11GL.dir/src/x11gl/X11GL.cpp.s
.PHONY : src/x11gl/X11GL.cpp.s

src/x11gl/gears.o: src/x11gl/gears.cpp.o

.PHONY : src/x11gl/gears.o

# target to build an object file
src/x11gl/gears.cpp.o:
	$(MAKE) -f CMakeFiles/X11GL.dir/build.make CMakeFiles/X11GL.dir/src/x11gl/gears.cpp.o
.PHONY : src/x11gl/gears.cpp.o

src/x11gl/gears.i: src/x11gl/gears.cpp.i

.PHONY : src/x11gl/gears.i

# target to preprocess a source file
src/x11gl/gears.cpp.i:
	$(MAKE) -f CMakeFiles/X11GL.dir/build.make CMakeFiles/X11GL.dir/src/x11gl/gears.cpp.i
.PHONY : src/x11gl/gears.cpp.i

src/x11gl/gears.s: src/x11gl/gears.cpp.s

.PHONY : src/x11gl/gears.s

# target to generate assembly for a file
src/x11gl/gears.cpp.s:
	$(MAKE) -f CMakeFiles/X11GL.dir/build.make CMakeFiles/X11GL.dir/src/x11gl/gears.cpp.s
.PHONY : src/x11gl/gears.cpp.s

src/x11gl/loader.o: src/x11gl/loader.cpp.o

.PHONY : src/x11gl/loader.o

# target to build an object file
src/x11gl/loader.cpp.o:
	$(MAKE) -f CMakeFiles/X11GL.dir/build.make CMakeFiles/X11GL.dir/src/x11gl/loader.cpp.o
.PHONY : src/x11gl/loader.cpp.o

src/x11gl/loader.i: src/x11gl/loader.cpp.i

.PHONY : src/x11gl/loader.i

# target to preprocess a source file
src/x11gl/loader.cpp.i:
	$(MAKE) -f CMakeFiles/X11GL.dir/build.make CMakeFiles/X11GL.dir/src/x11gl/loader.cpp.i
.PHONY : src/x11gl/loader.cpp.i

src/x11gl/loader.s: src/x11gl/loader.cpp.s

.PHONY : src/x11gl/loader.s

# target to generate assembly for a file
src/x11gl/loader.cpp.s:
	$(MAKE) -f CMakeFiles/X11GL.dir/build.make CMakeFiles/X11GL.dir/src/x11gl/loader.cpp.s
.PHONY : src/x11gl/loader.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... package_source"
	@echo "... rebuild_cache"
	@echo "... package"
	@echo "... X11GL"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
	@echo "... src/x11gl/X11GL.o"
	@echo "... src/x11gl/X11GL.i"
	@echo "... src/x11gl/X11GL.s"
	@echo "... src/x11gl/gears.o"
	@echo "... src/x11gl/gears.i"
	@echo "... src/x11gl/gears.s"
	@echo "... src/x11gl/loader.o"
	@echo "... src/x11gl/loader.i"
	@echo "... src/x11gl/loader.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

