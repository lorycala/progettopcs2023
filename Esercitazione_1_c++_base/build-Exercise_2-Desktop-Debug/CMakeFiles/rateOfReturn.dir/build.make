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
CMAKE_SOURCE_DIR = C:\Users\Huawei\Desktop\PCS2023_Exercises\Esercitazione_1_c++_base\Exercise_2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Huawei\Desktop\PCS2023_Exercises\Esercitazione_1_c++_base\build-Exercise_2-Desktop-Debug

# Include any dependencies generated for this target.
include CMakeFiles/rateOfReturn.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/rateOfReturn.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/rateOfReturn.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/rateOfReturn.dir/flags.make

CMakeFiles/rateOfReturn.dir/main.cpp.obj: CMakeFiles/rateOfReturn.dir/flags.make
CMakeFiles/rateOfReturn.dir/main.cpp.obj: CMakeFiles/rateOfReturn.dir/includes_CXX.rsp
CMakeFiles/rateOfReturn.dir/main.cpp.obj: C:/Users/Huawei/Desktop/PCS2023_Exercises/Esercitazione_1_c++_base/Exercise_2/main.cpp
CMakeFiles/rateOfReturn.dir/main.cpp.obj: CMakeFiles/rateOfReturn.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Huawei\Desktop\PCS2023_Exercises\Esercitazione_1_c++_base\build-Exercise_2-Desktop-Debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/rateOfReturn.dir/main.cpp.obj"
	C:\Qt\Tools\mingw1120_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/rateOfReturn.dir/main.cpp.obj -MF CMakeFiles\rateOfReturn.dir\main.cpp.obj.d -o CMakeFiles\rateOfReturn.dir\main.cpp.obj -c C:\Users\Huawei\Desktop\PCS2023_Exercises\Esercitazione_1_c++_base\Exercise_2\main.cpp

CMakeFiles/rateOfReturn.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rateOfReturn.dir/main.cpp.i"
	C:\Qt\Tools\mingw1120_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Huawei\Desktop\PCS2023_Exercises\Esercitazione_1_c++_base\Exercise_2\main.cpp > CMakeFiles\rateOfReturn.dir\main.cpp.i

CMakeFiles/rateOfReturn.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rateOfReturn.dir/main.cpp.s"
	C:\Qt\Tools\mingw1120_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Huawei\Desktop\PCS2023_Exercises\Esercitazione_1_c++_base\Exercise_2\main.cpp -o CMakeFiles\rateOfReturn.dir\main.cpp.s

# Object files for target rateOfReturn
rateOfReturn_OBJECTS = \
"CMakeFiles/rateOfReturn.dir/main.cpp.obj"

# External object files for target rateOfReturn
rateOfReturn_EXTERNAL_OBJECTS =

rateOfReturn.exe: CMakeFiles/rateOfReturn.dir/main.cpp.obj
rateOfReturn.exe: CMakeFiles/rateOfReturn.dir/build.make
rateOfReturn.exe: C:/Users/Huawei/Desktop/PCS2023_Exercises/externals/Main_Install/googletest/lib/libgtest.a
rateOfReturn.exe: C:/Users/Huawei/Desktop/PCS2023_Exercises/externals/Main_Install/googletest/lib/libgtest_main.a
rateOfReturn.exe: C:/Users/Huawei/Desktop/PCS2023_Exercises/externals/Main_Install/googletest/lib/libgmock.a
rateOfReturn.exe: C:/Users/Huawei/Desktop/PCS2023_Exercises/externals/Main_Install/googletest/lib/libgmock_main.a
rateOfReturn.exe: C:/Users/Huawei/Desktop/PCS2023_Exercises/externals/Main_Install/googletest/lib/libgmock.a
rateOfReturn.exe: C:/Users/Huawei/Desktop/PCS2023_Exercises/externals/Main_Install/googletest/lib/libgtest.a
rateOfReturn.exe: CMakeFiles/rateOfReturn.dir/linklibs.rsp
rateOfReturn.exe: CMakeFiles/rateOfReturn.dir/objects1.rsp
rateOfReturn.exe: CMakeFiles/rateOfReturn.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Huawei\Desktop\PCS2023_Exercises\Esercitazione_1_c++_base\build-Exercise_2-Desktop-Debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable rateOfReturn.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\rateOfReturn.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/rateOfReturn.dir/build: rateOfReturn.exe
.PHONY : CMakeFiles/rateOfReturn.dir/build

CMakeFiles/rateOfReturn.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\rateOfReturn.dir\cmake_clean.cmake
.PHONY : CMakeFiles/rateOfReturn.dir/clean

CMakeFiles/rateOfReturn.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Huawei\Desktop\PCS2023_Exercises\Esercitazione_1_c++_base\Exercise_2 C:\Users\Huawei\Desktop\PCS2023_Exercises\Esercitazione_1_c++_base\Exercise_2 C:\Users\Huawei\Desktop\PCS2023_Exercises\Esercitazione_1_c++_base\build-Exercise_2-Desktop-Debug C:\Users\Huawei\Desktop\PCS2023_Exercises\Esercitazione_1_c++_base\build-Exercise_2-Desktop-Debug C:\Users\Huawei\Desktop\PCS2023_Exercises\Esercitazione_1_c++_base\build-Exercise_2-Desktop-Debug\CMakeFiles\rateOfReturn.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/rateOfReturn.dir/depend
