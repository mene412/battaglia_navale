# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_SOURCE_DIR = "/home/local/muttand11213/untitled folder/battaglia_navale-main"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/local/muttand11213/untitled folder/battaglia_navale-main"

# Include any dependencies generated for this target.
include CMakeFiles/battaglia_navale.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/battaglia_navale.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/battaglia_navale.dir/flags.make

CMakeFiles/battaglia_navale.dir/src/main.cpp.o: CMakeFiles/battaglia_navale.dir/flags.make
CMakeFiles/battaglia_navale.dir/src/main.cpp.o: src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/local/muttand11213/untitled folder/battaglia_navale-main/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/battaglia_navale.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/battaglia_navale.dir/src/main.cpp.o -c "/home/local/muttand11213/untitled folder/battaglia_navale-main/src/main.cpp"

CMakeFiles/battaglia_navale.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/battaglia_navale.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/local/muttand11213/untitled folder/battaglia_navale-main/src/main.cpp" > CMakeFiles/battaglia_navale.dir/src/main.cpp.i

CMakeFiles/battaglia_navale.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/battaglia_navale.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/local/muttand11213/untitled folder/battaglia_navale-main/src/main.cpp" -o CMakeFiles/battaglia_navale.dir/src/main.cpp.s

# Object files for target battaglia_navale
battaglia_navale_OBJECTS = \
"CMakeFiles/battaglia_navale.dir/src/main.cpp.o"

# External object files for target battaglia_navale
battaglia_navale_EXTERNAL_OBJECTS =

battaglia_navale: CMakeFiles/battaglia_navale.dir/src/main.cpp.o
battaglia_navale: CMakeFiles/battaglia_navale.dir/build.make
battaglia_navale: libBattleship.a
battaglia_navale: CMakeFiles/battaglia_navale.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/local/muttand11213/untitled folder/battaglia_navale-main/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable battaglia_navale"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/battaglia_navale.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/battaglia_navale.dir/build: battaglia_navale

.PHONY : CMakeFiles/battaglia_navale.dir/build

CMakeFiles/battaglia_navale.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/battaglia_navale.dir/cmake_clean.cmake
.PHONY : CMakeFiles/battaglia_navale.dir/clean

CMakeFiles/battaglia_navale.dir/depend:
	cd "/home/local/muttand11213/untitled folder/battaglia_navale-main" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/local/muttand11213/untitled folder/battaglia_navale-main" "/home/local/muttand11213/untitled folder/battaglia_navale-main" "/home/local/muttand11213/untitled folder/battaglia_navale-main" "/home/local/muttand11213/untitled folder/battaglia_navale-main" "/home/local/muttand11213/untitled folder/battaglia_navale-main/CMakeFiles/battaglia_navale.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/battaglia_navale.dir/depend

