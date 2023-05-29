# cmake_minimum_required(VERSION <specify CMake version here>)
cmake_minimum_required(VERSION 3.12)
project(EE569_hw3_831981929_HanyunZhao)

set(CMAKE_CXX_STANDARD 14)

set(OpenCV_DIR "D:\\OpenCV\\opencv\\mingw-build")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

#add_executable(EE569_hw3_831981929_HanyunZhao warping.cpp fileIO.h InverseWarping.cpp thinning.cpp defect.cpp)
#add_executable(EE569_hw3_831981929_HanyunZhao fileIO.h stitching.cpp)
#add_executable(EE569_hw3_831981929_HanyunZhao fileIO.h beans.cpp)
add_executable(EE569_hw3_831981929_HanyunZhao fileIO.h defect.cpp)
# add libs you need
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs opencv_calib3d
        opencv_features2d opencv_stitching)

# linking
target_link_libraries(EE569_hw3_831981929_HanyunZhao ${OpenCV_LIBS})