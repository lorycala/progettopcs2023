# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.24

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\Qt\Tools\CMake_64\bin\cmake.exe

# The command to remove a file.
RM = C:\Qt\Tools\CMake_64\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Huawei\Desktop\progettopcs\externals\Main_Source\eigen3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Huawei\Desktop\progettopcs\externals\Main_Build\eigen3

# Utility rule file for demos.

# Include any custom commands dependencies for this target.
include demos/CMakeFiles/demos.dir/compiler_depend.make

# Include the progress variables for this target.
include demos/CMakeFiles/demos.dir/progress.make

demos: demos/CMakeFiles/demos.dir/build.make
.PHONY : demos

# Rule to build all files generated by this target.
demos/CMakeFiles/demos.dir/build: demos
.PHONY : demos/CMakeFiles/demos.dir/build

demos/CMakeFiles/demos.dir/clean:
	cd /d C:\Users\Huawei\Desktop\progettopcs\externals\Main_Build\eigen3\demos && $(CMAKE_COMMAND) -P CMakeFiles\demos.dir\cmake_clean.cmake
.PHONY : demos/CMakeFiles/demos.dir/clean

demos/CMakeFiles/demos.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Huawei\Desktop\progettopcs\externals\Main_Source\eigen3 C:\Users\Huawei\Desktop\progettopcs\externals\Main_Source\eigen3\demos C:\Users\Huawei\Desktop\progettopcs\externals\Main_Build\eigen3 C:\Users\Huawei\Desktop\progettopcs\externals\Main_Build\eigen3\demos C:\Users\Huawei\Desktop\progettopcs\externals\Main_Build\eigen3\demos\CMakeFiles\demos.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : demos/CMakeFiles/demos.dir/depend

