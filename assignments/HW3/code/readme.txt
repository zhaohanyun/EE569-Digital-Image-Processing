# EE569 Homework Assignment #3
# Date: Mar 10, 2022
# Name: Hanyun Zhao
# ID: 8831981929
# email: zhaohanyun@usc.edu

# Compiled on WINDOWS 10
1.1
g++ -o warping warping.cpp
warping raw_images/Forky.raw Output/warppedForky.raw
warping raw_images/22.raw Output/warpped22.raw
1.2
g++ -o InverseWarping InverseWarping.cpp
InverseWarping Output/warppedForky.raw Output/InverseForky.raw
InverseWarping Output/warpped22.raw Output/Inverse22.raw

2.
activate CMakeList.txt line
add_executable(EE569_hw3_831981929_HanyunZhao fileIO.h stitching.cpp)

3.a
g++ -o thinning thinning.cpp
thinning raw_images/flower.raw Output/thinFlower.raw 247
thinning raw_images/jar.raw Output/thinjar.raw 252
thinning raw_images/spring.raw Output/thinspring.raw 252

3.b
activate CMakeList.txt line
add_executable(EE569_hw3_831981929_HanyunZhao fileIO.h defect.cpp)

3.c
activate CMakeList.txt line
add_executable(EE569_hw3_831981929_HanyunZhao fileIO.h beans.cpp)