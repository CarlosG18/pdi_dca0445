# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/eduardo09/gabriel/ufrn/semestres/2024.2/pdi/pdi_dca0445/labs/uni2/pontilhismo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/eduardo09/gabriel/ufrn/semestres/2024.2/pdi/pdi_dca0445/labs/uni2/pontilhismo/build

# Include any dependencies generated for this target.
include CMakeFiles/pontilhismo.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/pontilhismo.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/pontilhismo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/pontilhismo.dir/flags.make

CMakeFiles/pontilhismo.dir/pontilhismo.cpp.o: CMakeFiles/pontilhismo.dir/flags.make
CMakeFiles/pontilhismo.dir/pontilhismo.cpp.o: /home/eduardo09/gabriel/ufrn/semestres/2024.2/pdi/pdi_dca0445/labs/uni2/pontilhismo/pontilhismo.cpp
CMakeFiles/pontilhismo.dir/pontilhismo.cpp.o: CMakeFiles/pontilhismo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/eduardo09/gabriel/ufrn/semestres/2024.2/pdi/pdi_dca0445/labs/uni2/pontilhismo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/pontilhismo.dir/pontilhismo.cpp.o"
	/usr/sbin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/pontilhismo.dir/pontilhismo.cpp.o -MF CMakeFiles/pontilhismo.dir/pontilhismo.cpp.o.d -o CMakeFiles/pontilhismo.dir/pontilhismo.cpp.o -c /home/eduardo09/gabriel/ufrn/semestres/2024.2/pdi/pdi_dca0445/labs/uni2/pontilhismo/pontilhismo.cpp

CMakeFiles/pontilhismo.dir/pontilhismo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/pontilhismo.dir/pontilhismo.cpp.i"
	/usr/sbin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/eduardo09/gabriel/ufrn/semestres/2024.2/pdi/pdi_dca0445/labs/uni2/pontilhismo/pontilhismo.cpp > CMakeFiles/pontilhismo.dir/pontilhismo.cpp.i

CMakeFiles/pontilhismo.dir/pontilhismo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/pontilhismo.dir/pontilhismo.cpp.s"
	/usr/sbin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/eduardo09/gabriel/ufrn/semestres/2024.2/pdi/pdi_dca0445/labs/uni2/pontilhismo/pontilhismo.cpp -o CMakeFiles/pontilhismo.dir/pontilhismo.cpp.s

# Object files for target pontilhismo
pontilhismo_OBJECTS = \
"CMakeFiles/pontilhismo.dir/pontilhismo.cpp.o"

# External object files for target pontilhismo
pontilhismo_EXTERNAL_OBJECTS =

pontilhismo: CMakeFiles/pontilhismo.dir/pontilhismo.cpp.o
pontilhismo: CMakeFiles/pontilhismo.dir/build.make
pontilhismo: /usr/lib/libopencv_highgui.so.4.10.0
pontilhismo: /usr/lib/libopencv_videoio.so.4.10.0
pontilhismo: /usr/lib/libopencv_imgcodecs.so.4.10.0
pontilhismo: /usr/lib/libopencv_imgproc.so.4.10.0
pontilhismo: /usr/lib/libopencv_core.so.4.10.0
pontilhismo: CMakeFiles/pontilhismo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/eduardo09/gabriel/ufrn/semestres/2024.2/pdi/pdi_dca0445/labs/uni2/pontilhismo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable pontilhismo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pontilhismo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/pontilhismo.dir/build: pontilhismo
.PHONY : CMakeFiles/pontilhismo.dir/build

CMakeFiles/pontilhismo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/pontilhismo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/pontilhismo.dir/clean

CMakeFiles/pontilhismo.dir/depend:
	cd /home/eduardo09/gabriel/ufrn/semestres/2024.2/pdi/pdi_dca0445/labs/uni2/pontilhismo/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/eduardo09/gabriel/ufrn/semestres/2024.2/pdi/pdi_dca0445/labs/uni2/pontilhismo /home/eduardo09/gabriel/ufrn/semestres/2024.2/pdi/pdi_dca0445/labs/uni2/pontilhismo /home/eduardo09/gabriel/ufrn/semestres/2024.2/pdi/pdi_dca0445/labs/uni2/pontilhismo/build /home/eduardo09/gabriel/ufrn/semestres/2024.2/pdi/pdi_dca0445/labs/uni2/pontilhismo/build /home/eduardo09/gabriel/ufrn/semestres/2024.2/pdi/pdi_dca0445/labs/uni2/pontilhismo/build/CMakeFiles/pontilhismo.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/pontilhismo.dir/depend

