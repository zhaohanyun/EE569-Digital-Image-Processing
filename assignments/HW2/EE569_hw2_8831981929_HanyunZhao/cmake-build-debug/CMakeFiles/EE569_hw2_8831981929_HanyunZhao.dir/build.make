# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = C:\Users\Administrator\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\182.4323.58\bin\cmake\win\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\Administrator\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\182.4323.58\bin\cmake\win\bin\cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Administrator\Desktop\EE569\assignments\HW2\EE569_hw2_8831981929_HanyunZhao

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Administrator\Desktop\EE569\assignments\HW2\EE569_hw2_8831981929_HanyunZhao\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/EE569_hw2_8831981929_HanyunZhao.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/EE569_hw2_8831981929_HanyunZhao.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/EE569_hw2_8831981929_HanyunZhao.dir/flags.make

CMakeFiles/EE569_hw2_8831981929_HanyunZhao.dir/CannyEdgeDetector.cpp.obj: CMakeFiles/EE569_hw2_8831981929_HanyunZhao.dir/flags.make
CMakeFiles/EE569_hw2_8831981929_HanyunZhao.dir/CannyEdgeDetector.cpp.obj: CMakeFiles/EE569_hw2_8831981929_HanyunZhao.dir/includes_CXX.rsp
CMakeFiles/EE569_hw2_8831981929_HanyunZhao.dir/CannyEdgeDetector.cpp.obj: ../CannyEdgeDetector.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Administrator\Desktop\EE569\assignments\HW2\EE569_hw2_8831981929_HanyunZhao\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/EE569_hw2_8831981929_HanyunZhao.dir/CannyEdgeDetector.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\EE569_hw2_8831981929_HanyunZhao.dir\CannyEdgeDetector.cpp.obj -c C:\Users\Administrator\Desktop\EE569\assignments\HW2\EE569_hw2_8831981929_HanyunZhao\CannyEdgeDetector.cpp

CMakeFiles/EE569_hw2_8831981929_HanyunZhao.dir/CannyEdgeDetector.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/EE569_hw2_8831981929_HanyunZhao.dir/CannyEdgeDetector.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Administrator\Desktop\EE569\assignments\HW2\EE569_hw2_8831981929_HanyunZhao\CannyEdgeDetector.cpp > CMakeFiles\EE569_hw2_8831981929_HanyunZhao.dir\CannyEdgeDetector.cpp.i

CMakeFiles/EE569_hw2_8831981929_HanyunZhao.dir/CannyEdgeDetector.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/EE569_hw2_8831981929_HanyunZhao.dir/CannyEdgeDetector.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Administrator\Desktop\EE569\assignments\HW2\EE569_hw2_8831981929_HanyunZhao\CannyEdgeDetector.cpp -o CMakeFiles\EE569_hw2_8831981929_HanyunZhao.dir\CannyEdgeDetector.cpp.s

# Object files for target EE569_hw2_8831981929_HanyunZhao
EE569_hw2_8831981929_HanyunZhao_OBJECTS = \
"CMakeFiles/EE569_hw2_8831981929_HanyunZhao.dir/CannyEdgeDetector.cpp.obj"

# External object files for target EE569_hw2_8831981929_HanyunZhao
EE569_hw2_8831981929_HanyunZhao_EXTERNAL_OBJECTS =

EE569_hw2_8831981929_HanyunZhao.exe: CMakeFiles/EE569_hw2_8831981929_HanyunZhao.dir/CannyEdgeDetector.cpp.obj
EE569_hw2_8831981929_HanyunZhao.exe: CMakeFiles/EE569_hw2_8831981929_HanyunZhao.dir/build.make
EE569_hw2_8831981929_HanyunZhao.exe: D:/OpenCV/opencv/mingw-build/lib/libopencv_highgui455.dll.a
EE569_hw2_8831981929_HanyunZhao.exe: D:/OpenCV/opencv/mingw-build/lib/libopencv_photo455.dll.a
EE569_hw2_8831981929_HanyunZhao.exe: D:/OpenCV/opencv/mingw-build/lib/libopencv_videoio455.dll.a
EE569_hw2_8831981929_HanyunZhao.exe: D:/OpenCV/opencv/mingw-build/lib/libopencv_imgcodecs455.dll.a
EE569_hw2_8831981929_HanyunZhao.exe: D:/OpenCV/opencv/mingw-build/lib/libopencv_imgproc455.dll.a
EE569_hw2_8831981929_HanyunZhao.exe: D:/OpenCV/opencv/mingw-build/lib/libopencv_core455.dll.a
EE569_hw2_8831981929_HanyunZhao.exe: CMakeFiles/EE569_hw2_8831981929_HanyunZhao.dir/linklibs.rsp
EE569_hw2_8831981929_HanyunZhao.exe: CMakeFiles/EE569_hw2_8831981929_HanyunZhao.dir/objects1.rsp
EE569_hw2_8831981929_HanyunZhao.exe: CMakeFiles/EE569_hw2_8831981929_HanyunZhao.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Administrator\Desktop\EE569\assignments\HW2\EE569_hw2_8831981929_HanyunZhao\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable EE569_hw2_8831981929_HanyunZhao.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\EE569_hw2_8831981929_HanyunZhao.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/EE569_hw2_8831981929_HanyunZhao.dir/build: EE569_hw2_8831981929_HanyunZhao.exe

.PHONY : CMakeFiles/EE569_hw2_8831981929_HanyunZhao.dir/build

CMakeFiles/EE569_hw2_8831981929_HanyunZhao.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\EE569_hw2_8831981929_HanyunZhao.dir\cmake_clean.cmake
.PHONY : CMakeFiles/EE569_hw2_8831981929_HanyunZhao.dir/clean

CMakeFiles/EE569_hw2_8831981929_HanyunZhao.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Administrator\Desktop\EE569\assignments\HW2\EE569_hw2_8831981929_HanyunZhao C:\Users\Administrator\Desktop\EE569\assignments\HW2\EE569_hw2_8831981929_HanyunZhao C:\Users\Administrator\Desktop\EE569\assignments\HW2\EE569_hw2_8831981929_HanyunZhao\cmake-build-debug C:\Users\Administrator\Desktop\EE569\assignments\HW2\EE569_hw2_8831981929_HanyunZhao\cmake-build-debug C:\Users\Administrator\Desktop\EE569\assignments\HW2\EE569_hw2_8831981929_HanyunZhao\cmake-build-debug\CMakeFiles\EE569_hw2_8831981929_HanyunZhao.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/EE569_hw2_8831981929_HanyunZhao.dir/depend

