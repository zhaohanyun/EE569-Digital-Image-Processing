cmake_minimum_required(VERSION 3.12)
project(EE569_hw1_8831981929_HanyunZhao)

set(CMAKE_CXX_STANDARD 14)

set(OpenCV_DIR "D:\\OpenCV\\opencv\\mingw-build")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(EE569_hw1_8831981929_HanyunZhao BilinearDemosaicing.cpp HistogramMani1.cpp HistogramMani2.cpp CLAHE.cpp CLAHEcv.cpp CLAHE2.cpp ImageDeno.cpp ImgDenoMean.cpp ImgDenoGauss.cpp BilateralFilter.cpp NLMcv.cpp  FrostedGlassFilter.cpp)
#add_executable(EE569_hw1_8831981929_HanyunZhao CLAHEcv.cpp)
#add_executable(EE569_hw1_8831981929_HanyunZhao NLMcv.cpp)
#add_executable(EE569_hw1_8831981929_HanyunZhao MixNoiseColor.cpp)

# add libs you need
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs opencv_photo)

# linking
target_link_libraries(EE569_hw1_8831981929_HanyunZhao ${OpenCV_LIBS})