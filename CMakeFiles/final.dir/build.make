# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /media/kibby/WorkSpace/CMPT365FinalProj

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /media/kibby/WorkSpace/CMPT365FinalProj

# Include any dependencies generated for this target.
include CMakeFiles/final.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/final.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/final.dir/flags.make

CMakeFiles/final.dir/src/main.cpp.o: CMakeFiles/final.dir/flags.make
CMakeFiles/final.dir/src/main.cpp.o: src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/kibby/WorkSpace/CMPT365FinalProj/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/final.dir/src/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/final.dir/src/main.cpp.o -c /media/kibby/WorkSpace/CMPT365FinalProj/src/main.cpp

CMakeFiles/final.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/final.dir/src/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/kibby/WorkSpace/CMPT365FinalProj/src/main.cpp > CMakeFiles/final.dir/src/main.cpp.i

CMakeFiles/final.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/final.dir/src/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/kibby/WorkSpace/CMPT365FinalProj/src/main.cpp -o CMakeFiles/final.dir/src/main.cpp.s

CMakeFiles/final.dir/src/main.cpp.o.requires:

.PHONY : CMakeFiles/final.dir/src/main.cpp.o.requires

CMakeFiles/final.dir/src/main.cpp.o.provides: CMakeFiles/final.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/final.dir/build.make CMakeFiles/final.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/final.dir/src/main.cpp.o.provides

CMakeFiles/final.dir/src/main.cpp.o.provides.build: CMakeFiles/final.dir/src/main.cpp.o


# Object files for target final
final_OBJECTS = \
"CMakeFiles/final.dir/src/main.cpp.o"

# External object files for target final
final_EXTERNAL_OBJECTS =

final: CMakeFiles/final.dir/src/main.cpp.o
final: CMakeFiles/final.dir/build.make
final: /usr/local/lib/libopencv_dnn.so.3.3.1
final: /usr/local/lib/libopencv_ml.so.3.3.1
final: /usr/local/lib/libopencv_objdetect.so.3.3.1
final: /usr/local/lib/libopencv_shape.so.3.3.1
final: /usr/local/lib/libopencv_stitching.so.3.3.1
final: /usr/local/lib/libopencv_superres.so.3.3.1
final: /usr/local/lib/libopencv_videostab.so.3.3.1
final: /usr/local/lib/libopencv_calib3d.so.3.3.1
final: /usr/local/lib/libopencv_features2d.so.3.3.1
final: /usr/local/lib/libopencv_flann.so.3.3.1
final: /usr/local/lib/libopencv_highgui.so.3.3.1
final: /usr/local/lib/libopencv_photo.so.3.3.1
final: /usr/local/lib/libopencv_video.so.3.3.1
final: /usr/local/lib/libopencv_videoio.so.3.3.1
final: /usr/local/lib/libopencv_imgcodecs.so.3.3.1
final: /usr/local/lib/libopencv_imgproc.so.3.3.1
final: /usr/local/lib/libopencv_core.so.3.3.1
final: CMakeFiles/final.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/media/kibby/WorkSpace/CMPT365FinalProj/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable final"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/final.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/final.dir/build: final

.PHONY : CMakeFiles/final.dir/build

CMakeFiles/final.dir/requires: CMakeFiles/final.dir/src/main.cpp.o.requires

.PHONY : CMakeFiles/final.dir/requires

CMakeFiles/final.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/final.dir/cmake_clean.cmake
.PHONY : CMakeFiles/final.dir/clean

CMakeFiles/final.dir/depend:
	cd /media/kibby/WorkSpace/CMPT365FinalProj && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /media/kibby/WorkSpace/CMPT365FinalProj /media/kibby/WorkSpace/CMPT365FinalProj /media/kibby/WorkSpace/CMPT365FinalProj /media/kibby/WorkSpace/CMPT365FinalProj /media/kibby/WorkSpace/CMPT365FinalProj/CMakeFiles/final.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/final.dir/depend
