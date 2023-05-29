cmake_minimum_required(VERSION 3.12)
project(EE569_hw2_8831981929_HanyunZhao)

set(CMAKE_CXX_STANDARD 14)

set(OpenCV_DIR "D:\\OpenCV\\opencv\\mingw-build")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

#add_executable(EE569_hw2_8831981929_HanyunZhao SobelEdgeDetector.cpp fileIO.h CannyEdgeDetector.cpp Thresholding.cpp DitheringMatrix.cpp ErrorDiffusion.cpp SeparableED.cpp MBVQ.cpp)
add_executable(EE569_hw2_8831981929_HanyunZhao fileIO.h CannyEdgeDetector.cpp)

# add libs you need
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs opencv_photo)

# linking
target_link_libraries(EE569_hw2_8831981929_HanyunZhao ${OpenCV_LIBS})