# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.15

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\Program Files\JetBrains\CLion 2019.3.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\Program Files\JetBrains\CLion 2019.3.2\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\Wiktor Szymkowski\CLionProjects\ZMO\META"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\Wiktor Szymkowski\CLionProjects\ZMO\META\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/META.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/META.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/META.dir/flags.make

CMakeFiles/META.dir/main.cpp.obj: CMakeFiles/META.dir/flags.make
CMakeFiles/META.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\Wiktor Szymkowski\CLionProjects\ZMO\META\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/META.dir/main.cpp.obj"
	"D:\Program Files (x86)\mingw-w64\i686-8.1.0-posix-dwarf-rt_v6-rev0\mingw32\bin\g++.exe"  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\META.dir\main.cpp.obj -c "C:\Users\Wiktor Szymkowski\CLionProjects\ZMO\META\main.cpp"

CMakeFiles/META.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/META.dir/main.cpp.i"
	"D:\Program Files (x86)\mingw-w64\i686-8.1.0-posix-dwarf-rt_v6-rev0\mingw32\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Wiktor Szymkowski\CLionProjects\ZMO\META\main.cpp" > CMakeFiles\META.dir\main.cpp.i

CMakeFiles/META.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/META.dir/main.cpp.s"
	"D:\Program Files (x86)\mingw-w64\i686-8.1.0-posix-dwarf-rt_v6-rev0\mingw32\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\Wiktor Szymkowski\CLionProjects\ZMO\META\main.cpp" -o CMakeFiles\META.dir\main.cpp.s

# Object files for target META
META_OBJECTS = \
"CMakeFiles/META.dir/main.cpp.obj"

# External object files for target META
META_EXTERNAL_OBJECTS =

META.exe: CMakeFiles/META.dir/main.cpp.obj
META.exe: CMakeFiles/META.dir/build.make
META.exe: CMakeFiles/META.dir/linklibs.rsp
META.exe: CMakeFiles/META.dir/objects1.rsp
META.exe: CMakeFiles/META.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\Wiktor Szymkowski\CLionProjects\ZMO\META\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable META.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\META.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/META.dir/build: META.exe

.PHONY : CMakeFiles/META.dir/build

CMakeFiles/META.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\META.dir\cmake_clean.cmake
.PHONY : CMakeFiles/META.dir/clean

CMakeFiles/META.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\Wiktor Szymkowski\CLionProjects\ZMO\META" "C:\Users\Wiktor Szymkowski\CLionProjects\ZMO\META" "C:\Users\Wiktor Szymkowski\CLionProjects\ZMO\META\cmake-build-debug" "C:\Users\Wiktor Szymkowski\CLionProjects\ZMO\META\cmake-build-debug" "C:\Users\Wiktor Szymkowski\CLionProjects\ZMO\META\cmake-build-debug\CMakeFiles\META.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/META.dir/depend

