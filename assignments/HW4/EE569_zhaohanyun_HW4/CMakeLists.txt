# cmake_minimum_required(VERSION <specify CMake version here>)
cmake_minimum_required(VERSION 3.12)
project(EE569_zhaohanyun_HW4)

set(CMAKE_CXX_STANDARD 14)
set(OpenCV_DIR "D:\\OpenCV\\opencv\\mingw-build")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

#add_executable(EE569_zhaohanyun_HW4 featureExtraction.cpp fileIO.h)
#add_executable(EE569_zhaohanyun_HW4  fileIO.h TextureSeg.cpp)
##add_executable(EE569_zhaohanyun_HW4  fileIO.h PrintColor.cpp)
add_executable(EE569_zhaohanyun_HW4  fileIO.h myfuckingSIFT.cpp)

set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_xfeature2d)
target_link_libraries(EE569_zhaohanyun_HW4 ${OpenCV_LIBS})



