# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 4.0

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
CMAKE_COMMAND = C:\msys64\ucrt64\bin\cmake.exe

# The command to remove a file.
RM = C:\msys64\ucrt64\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Alen\Documents\GithubPrivate\CS-Work\6thSemester\BachelorThesis\Thesis\EDIConverter

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Alen\Documents\GithubPrivate\CS-Work\6thSemester\BachelorThesis\Thesis\EDIConverter\build

# Include any dependencies generated for this target.
include CMakeFiles/edi_converter.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/edi_converter.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/edi_converter.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/edi_converter.dir/flags.make

CMakeFiles/edi_converter.dir/codegen:
.PHONY : CMakeFiles/edi_converter.dir/codegen

CMakeFiles/edi_converter.dir/main.cpp.obj: CMakeFiles/edi_converter.dir/flags.make
CMakeFiles/edi_converter.dir/main.cpp.obj: CMakeFiles/edi_converter.dir/includes_CXX.rsp
CMakeFiles/edi_converter.dir/main.cpp.obj: C:/Users/Alen/Documents/GithubPrivate/CS-Work/6thSemester/BachelorThesis/Thesis/EDIConverter/main.cpp
CMakeFiles/edi_converter.dir/main.cpp.obj: CMakeFiles/edi_converter.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\Alen\Documents\GithubPrivate\CS-Work\6thSemester\BachelorThesis\Thesis\EDIConverter\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/edi_converter.dir/main.cpp.obj"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/edi_converter.dir/main.cpp.obj -MF CMakeFiles\edi_converter.dir\main.cpp.obj.d -o CMakeFiles\edi_converter.dir\main.cpp.obj -c C:\Users\Alen\Documents\GithubPrivate\CS-Work\6thSemester\BachelorThesis\Thesis\EDIConverter\main.cpp

CMakeFiles/edi_converter.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/edi_converter.dir/main.cpp.i"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Alen\Documents\GithubPrivate\CS-Work\6thSemester\BachelorThesis\Thesis\EDIConverter\main.cpp > CMakeFiles\edi_converter.dir\main.cpp.i

CMakeFiles/edi_converter.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/edi_converter.dir/main.cpp.s"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Alen\Documents\GithubPrivate\CS-Work\6thSemester\BachelorThesis\Thesis\EDIConverter\main.cpp -o CMakeFiles\edi_converter.dir\main.cpp.s

# Object files for target edi_converter
edi_converter_OBJECTS = \
"CMakeFiles/edi_converter.dir/main.cpp.obj"

# External object files for target edi_converter
edi_converter_EXTERNAL_OBJECTS =

edi_converter.exe: CMakeFiles/edi_converter.dir/main.cpp.obj
edi_converter.exe: CMakeFiles/edi_converter.dir/build.make
edi_converter.exe: C:/msys64/ucrt64/lib/libxml2.dll.a
edi_converter.exe: C:/msys64/ucrt64/lib/libxslt.dll.a
edi_converter.exe: CMakeFiles/edi_converter.dir/linkLibs.rsp
edi_converter.exe: CMakeFiles/edi_converter.dir/objects1.rsp
edi_converter.exe: CMakeFiles/edi_converter.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\Alen\Documents\GithubPrivate\CS-Work\6thSemester\BachelorThesis\Thesis\EDIConverter\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable edi_converter.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\edi_converter.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/edi_converter.dir/build: edi_converter.exe
.PHONY : CMakeFiles/edi_converter.dir/build

CMakeFiles/edi_converter.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\edi_converter.dir\cmake_clean.cmake
.PHONY : CMakeFiles/edi_converter.dir/clean

CMakeFiles/edi_converter.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Alen\Documents\GithubPrivate\CS-Work\6thSemester\BachelorThesis\Thesis\EDIConverter C:\Users\Alen\Documents\GithubPrivate\CS-Work\6thSemester\BachelorThesis\Thesis\EDIConverter C:\Users\Alen\Documents\GithubPrivate\CS-Work\6thSemester\BachelorThesis\Thesis\EDIConverter\build C:\Users\Alen\Documents\GithubPrivate\CS-Work\6thSemester\BachelorThesis\Thesis\EDIConverter\build C:\Users\Alen\Documents\GithubPrivate\CS-Work\6thSemester\BachelorThesis\Thesis\EDIConverter\build\CMakeFiles\edi_converter.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/edi_converter.dir/depend

