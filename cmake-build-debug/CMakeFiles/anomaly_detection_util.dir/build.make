# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /home/kali/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/212.5284.51/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/kali/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/212.5284.51/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kali/BackendProjects/AnomalyDetector

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kali/BackendProjects/AnomalyDetector/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/anomaly_detection_util.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/anomaly_detection_util.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/anomaly_detection_util.dir/flags.make

CMakeFiles/anomaly_detection_util.dir/MainTrain.cpp.o: CMakeFiles/anomaly_detection_util.dir/flags.make
CMakeFiles/anomaly_detection_util.dir/MainTrain.cpp.o: ../MainTrain.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kali/BackendProjects/AnomalyDetector/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/anomaly_detection_util.dir/MainTrain.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/anomaly_detection_util.dir/MainTrain.cpp.o -c /home/kali/BackendProjects/AnomalyDetector/MainTrain.cpp

CMakeFiles/anomaly_detection_util.dir/MainTrain.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/anomaly_detection_util.dir/MainTrain.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kali/BackendProjects/AnomalyDetector/MainTrain.cpp > CMakeFiles/anomaly_detection_util.dir/MainTrain.cpp.i

CMakeFiles/anomaly_detection_util.dir/MainTrain.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/anomaly_detection_util.dir/MainTrain.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kali/BackendProjects/AnomalyDetector/MainTrain.cpp -o CMakeFiles/anomaly_detection_util.dir/MainTrain.cpp.s

CMakeFiles/anomaly_detection_util.dir/anomaly_detection_util.cpp.o: CMakeFiles/anomaly_detection_util.dir/flags.make
CMakeFiles/anomaly_detection_util.dir/anomaly_detection_util.cpp.o: ../anomaly_detection_util.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kali/BackendProjects/AnomalyDetector/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/anomaly_detection_util.dir/anomaly_detection_util.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/anomaly_detection_util.dir/anomaly_detection_util.cpp.o -c /home/kali/BackendProjects/AnomalyDetector/anomaly_detection_util.cpp

CMakeFiles/anomaly_detection_util.dir/anomaly_detection_util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/anomaly_detection_util.dir/anomaly_detection_util.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kali/BackendProjects/AnomalyDetector/anomaly_detection_util.cpp > CMakeFiles/anomaly_detection_util.dir/anomaly_detection_util.cpp.i

CMakeFiles/anomaly_detection_util.dir/anomaly_detection_util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/anomaly_detection_util.dir/anomaly_detection_util.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kali/BackendProjects/AnomalyDetector/anomaly_detection_util.cpp -o CMakeFiles/anomaly_detection_util.dir/anomaly_detection_util.cpp.s

CMakeFiles/anomaly_detection_util.dir/timeseries.cpp.o: CMakeFiles/anomaly_detection_util.dir/flags.make
CMakeFiles/anomaly_detection_util.dir/timeseries.cpp.o: ../timeseries.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kali/BackendProjects/AnomalyDetector/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/anomaly_detection_util.dir/timeseries.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/anomaly_detection_util.dir/timeseries.cpp.o -c /home/kali/BackendProjects/AnomalyDetector/timeseries.cpp

CMakeFiles/anomaly_detection_util.dir/timeseries.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/anomaly_detection_util.dir/timeseries.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kali/BackendProjects/AnomalyDetector/timeseries.cpp > CMakeFiles/anomaly_detection_util.dir/timeseries.cpp.i

CMakeFiles/anomaly_detection_util.dir/timeseries.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/anomaly_detection_util.dir/timeseries.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kali/BackendProjects/AnomalyDetector/timeseries.cpp -o CMakeFiles/anomaly_detection_util.dir/timeseries.cpp.s

CMakeFiles/anomaly_detection_util.dir/SimpleAnomalyDetector.cpp.o: CMakeFiles/anomaly_detection_util.dir/flags.make
CMakeFiles/anomaly_detection_util.dir/SimpleAnomalyDetector.cpp.o: ../SimpleAnomalyDetector.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kali/BackendProjects/AnomalyDetector/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/anomaly_detection_util.dir/SimpleAnomalyDetector.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/anomaly_detection_util.dir/SimpleAnomalyDetector.cpp.o -c /home/kali/BackendProjects/AnomalyDetector/SimpleAnomalyDetector.cpp

CMakeFiles/anomaly_detection_util.dir/SimpleAnomalyDetector.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/anomaly_detection_util.dir/SimpleAnomalyDetector.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kali/BackendProjects/AnomalyDetector/SimpleAnomalyDetector.cpp > CMakeFiles/anomaly_detection_util.dir/SimpleAnomalyDetector.cpp.i

CMakeFiles/anomaly_detection_util.dir/SimpleAnomalyDetector.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/anomaly_detection_util.dir/SimpleAnomalyDetector.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kali/BackendProjects/AnomalyDetector/SimpleAnomalyDetector.cpp -o CMakeFiles/anomaly_detection_util.dir/SimpleAnomalyDetector.cpp.s

# Object files for target anomaly_detection_util
anomaly_detection_util_OBJECTS = \
"CMakeFiles/anomaly_detection_util.dir/MainTrain.cpp.o" \
"CMakeFiles/anomaly_detection_util.dir/anomaly_detection_util.cpp.o" \
"CMakeFiles/anomaly_detection_util.dir/timeseries.cpp.o" \
"CMakeFiles/anomaly_detection_util.dir/SimpleAnomalyDetector.cpp.o"

# External object files for target anomaly_detection_util
anomaly_detection_util_EXTERNAL_OBJECTS =

anomaly_detection_util: CMakeFiles/anomaly_detection_util.dir/MainTrain.cpp.o
anomaly_detection_util: CMakeFiles/anomaly_detection_util.dir/anomaly_detection_util.cpp.o
anomaly_detection_util: CMakeFiles/anomaly_detection_util.dir/timeseries.cpp.o
anomaly_detection_util: CMakeFiles/anomaly_detection_util.dir/SimpleAnomalyDetector.cpp.o
anomaly_detection_util: CMakeFiles/anomaly_detection_util.dir/build.make
anomaly_detection_util: CMakeFiles/anomaly_detection_util.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kali/BackendProjects/AnomalyDetector/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable anomaly_detection_util"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/anomaly_detection_util.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/anomaly_detection_util.dir/build: anomaly_detection_util
.PHONY : CMakeFiles/anomaly_detection_util.dir/build

CMakeFiles/anomaly_detection_util.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/anomaly_detection_util.dir/cmake_clean.cmake
.PHONY : CMakeFiles/anomaly_detection_util.dir/clean

CMakeFiles/anomaly_detection_util.dir/depend:
	cd /home/kali/BackendProjects/AnomalyDetector/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kali/BackendProjects/AnomalyDetector /home/kali/BackendProjects/AnomalyDetector /home/kali/BackendProjects/AnomalyDetector/cmake-build-debug /home/kali/BackendProjects/AnomalyDetector/cmake-build-debug /home/kali/BackendProjects/AnomalyDetector/cmake-build-debug/CMakeFiles/anomaly_detection_util.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/anomaly_detection_util.dir/depend

