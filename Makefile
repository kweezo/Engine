# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/vegovacraft/Documents/Engine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vegovacraft/Documents/Engine

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake cache editor..."
	/usr/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/vegovacraft/Documents/Engine/CMakeFiles /home/vegovacraft/Documents/Engine//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/vegovacraft/Documents/Engine/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named Engine

# Build rule for target.
Engine: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 Engine
.PHONY : Engine

# fast build rule for target.
Engine/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Engine.dir/build.make CMakeFiles/Engine.dir/build
.PHONY : Engine/fast

Camera.o: Camera.cpp.o
.PHONY : Camera.o

# target to build an object file
Camera.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Engine.dir/build.make CMakeFiles/Engine.dir/Camera.cpp.o
.PHONY : Camera.cpp.o

Camera.i: Camera.cpp.i
.PHONY : Camera.i

# target to preprocess a source file
Camera.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Engine.dir/build.make CMakeFiles/Engine.dir/Camera.cpp.i
.PHONY : Camera.cpp.i

Camera.s: Camera.cpp.s
.PHONY : Camera.s

# target to generate assembly for a file
Camera.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Engine.dir/build.make CMakeFiles/Engine.dir/Camera.cpp.s
.PHONY : Camera.cpp.s

Deltatime.o: Deltatime.cpp.o
.PHONY : Deltatime.o

# target to build an object file
Deltatime.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Engine.dir/build.make CMakeFiles/Engine.dir/Deltatime.cpp.o
.PHONY : Deltatime.cpp.o

Deltatime.i: Deltatime.cpp.i
.PHONY : Deltatime.i

# target to preprocess a source file
Deltatime.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Engine.dir/build.make CMakeFiles/Engine.dir/Deltatime.cpp.i
.PHONY : Deltatime.cpp.i

Deltatime.s: Deltatime.cpp.s
.PHONY : Deltatime.s

# target to generate assembly for a file
Deltatime.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Engine.dir/build.make CMakeFiles/Engine.dir/Deltatime.cpp.s
.PHONY : Deltatime.cpp.s

Engine.o: Engine.cpp.o
.PHONY : Engine.o

# target to build an object file
Engine.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Engine.dir/build.make CMakeFiles/Engine.dir/Engine.cpp.o
.PHONY : Engine.cpp.o

Engine.i: Engine.cpp.i
.PHONY : Engine.i

# target to preprocess a source file
Engine.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Engine.dir/build.make CMakeFiles/Engine.dir/Engine.cpp.i
.PHONY : Engine.cpp.i

Engine.s: Engine.cpp.s
.PHONY : Engine.s

# target to generate assembly for a file
Engine.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Engine.dir/build.make CMakeFiles/Engine.dir/Engine.cpp.s
.PHONY : Engine.cpp.s

Light.o: Light.cpp.o
.PHONY : Light.o

# target to build an object file
Light.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Engine.dir/build.make CMakeFiles/Engine.dir/Light.cpp.o
.PHONY : Light.cpp.o

Light.i: Light.cpp.i
.PHONY : Light.i

# target to preprocess a source file
Light.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Engine.dir/build.make CMakeFiles/Engine.dir/Light.cpp.i
.PHONY : Light.cpp.i

Light.s: Light.cpp.s
.PHONY : Light.s

# target to generate assembly for a file
Light.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Engine.dir/build.make CMakeFiles/Engine.dir/Light.cpp.s
.PHONY : Light.cpp.s

Model.o: Model.cpp.o
.PHONY : Model.o

# target to build an object file
Model.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Engine.dir/build.make CMakeFiles/Engine.dir/Model.cpp.o
.PHONY : Model.cpp.o

Model.i: Model.cpp.i
.PHONY : Model.i

# target to preprocess a source file
Model.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Engine.dir/build.make CMakeFiles/Engine.dir/Model.cpp.i
.PHONY : Model.cpp.i

Model.s: Model.cpp.s
.PHONY : Model.s

# target to generate assembly for a file
Model.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Engine.dir/build.make CMakeFiles/Engine.dir/Model.cpp.s
.PHONY : Model.cpp.s

Physics.o: Physics.cpp.o
.PHONY : Physics.o

# target to build an object file
Physics.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Engine.dir/build.make CMakeFiles/Engine.dir/Physics.cpp.o
.PHONY : Physics.cpp.o

Physics.i: Physics.cpp.i
.PHONY : Physics.i

# target to preprocess a source file
Physics.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Engine.dir/build.make CMakeFiles/Engine.dir/Physics.cpp.i
.PHONY : Physics.cpp.i

Physics.s: Physics.cpp.s
.PHONY : Physics.s

# target to generate assembly for a file
Physics.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Engine.dir/build.make CMakeFiles/Engine.dir/Physics.cpp.s
.PHONY : Physics.cpp.s

Shader.o: Shader.cpp.o
.PHONY : Shader.o

# target to build an object file
Shader.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Engine.dir/build.make CMakeFiles/Engine.dir/Shader.cpp.o
.PHONY : Shader.cpp.o

Shader.i: Shader.cpp.i
.PHONY : Shader.i

# target to preprocess a source file
Shader.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Engine.dir/build.make CMakeFiles/Engine.dir/Shader.cpp.i
.PHONY : Shader.cpp.i

Shader.s: Shader.cpp.s
.PHONY : Shader.s

# target to generate assembly for a file
Shader.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Engine.dir/build.make CMakeFiles/Engine.dir/Shader.cpp.s
.PHONY : Shader.cpp.s

Sprite.o: Sprite.cpp.o
.PHONY : Sprite.o

# target to build an object file
Sprite.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Engine.dir/build.make CMakeFiles/Engine.dir/Sprite.cpp.o
.PHONY : Sprite.cpp.o

Sprite.i: Sprite.cpp.i
.PHONY : Sprite.i

# target to preprocess a source file
Sprite.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Engine.dir/build.make CMakeFiles/Engine.dir/Sprite.cpp.i
.PHONY : Sprite.cpp.i

Sprite.s: Sprite.cpp.s
.PHONY : Sprite.s

# target to generate assembly for a file
Sprite.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Engine.dir/build.make CMakeFiles/Engine.dir/Sprite.cpp.s
.PHONY : Sprite.cpp.s

Surface.o: Surface.cpp.o
.PHONY : Surface.o

# target to build an object file
Surface.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Engine.dir/build.make CMakeFiles/Engine.dir/Surface.cpp.o
.PHONY : Surface.cpp.o

Surface.i: Surface.cpp.i
.PHONY : Surface.i

# target to preprocess a source file
Surface.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Engine.dir/build.make CMakeFiles/Engine.dir/Surface.cpp.i
.PHONY : Surface.cpp.i

Surface.s: Surface.cpp.s
.PHONY : Surface.s

# target to generate assembly for a file
Surface.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Engine.dir/build.make CMakeFiles/Engine.dir/Surface.cpp.s
.PHONY : Surface.cpp.s

Window.o: Window.cpp.o
.PHONY : Window.o

# target to build an object file
Window.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Engine.dir/build.make CMakeFiles/Engine.dir/Window.cpp.o
.PHONY : Window.cpp.o

Window.i: Window.cpp.i
.PHONY : Window.i

# target to preprocess a source file
Window.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Engine.dir/build.make CMakeFiles/Engine.dir/Window.cpp.i
.PHONY : Window.cpp.i

Window.s: Window.cpp.s
.PHONY : Window.s

# target to generate assembly for a file
Window.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Engine.dir/build.make CMakeFiles/Engine.dir/Window.cpp.s
.PHONY : Window.cpp.s

main.o: main.cpp.o
.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Engine.dir/build.make CMakeFiles/Engine.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i
.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Engine.dir/build.make CMakeFiles/Engine.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s
.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Engine.dir/build.make CMakeFiles/Engine.dir/main.cpp.s
.PHONY : main.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... Engine"
	@echo "... Camera.o"
	@echo "... Camera.i"
	@echo "... Camera.s"
	@echo "... Deltatime.o"
	@echo "... Deltatime.i"
	@echo "... Deltatime.s"
	@echo "... Engine.o"
	@echo "... Engine.i"
	@echo "... Engine.s"
	@echo "... Light.o"
	@echo "... Light.i"
	@echo "... Light.s"
	@echo "... Model.o"
	@echo "... Model.i"
	@echo "... Model.s"
	@echo "... Physics.o"
	@echo "... Physics.i"
	@echo "... Physics.s"
	@echo "... Shader.o"
	@echo "... Shader.i"
	@echo "... Shader.s"
	@echo "... Sprite.o"
	@echo "... Sprite.i"
	@echo "... Sprite.s"
	@echo "... Surface.o"
	@echo "... Surface.i"
	@echo "... Surface.s"
	@echo "... Window.o"
	@echo "... Window.i"
	@echo "... Window.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

