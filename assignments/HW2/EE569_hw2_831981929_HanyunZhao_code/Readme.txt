# EE569 Homework Assignment #2
# Date: Feb 20, 2021
# Name: Hanyun Zhao
# ID: 8831981929
# email: zhaohanyun@usc.edu

# Compiled on WINDOWS 10

1.a
g++ -o SobelEdgeDetector SobelEdgeDetector.cpp
SobelEdgeDetector HW2_images/Tiger.raw
Output: x Gradient.raw y Gradient.raw

1.b

To switch between Tiger and Pig, just edit the source file to and change output name properly. To
switch threshold percentage, edit 
``
Threshold(GF,ImageOutput,15);
OutputImage(ImageOutput,"Output/PigEdge15.raw",1);
``
and input a number between 0 and 100 as the third parameter of Threshold() funtion.

1.c 
run Matlab structured_edge_detection.mlx

1.d 
run Matlab PerformanceEvaluation.mlx and ThresholdEvaluation.mlx

2.a
Command for the two thresholding part
g++ -o Thresholding Thresholding.cpp
Thresholding
Output: BridgeFixed.raw, BridgeRandom.raw

Command
g++ -o DitheringMatrix DitheringMatrix.cpp
DitheringMatrix {n} Output/Dithering{n}.raw
Output: Dithering{n}.raw

2.b
Command:
g++ -o ErrorDiffusion ErrorDiffusion.cpp
ErrorDiffusion
Output: FS_Diffusion.raw, JJN_Diffusion.raw, Stucki_Diffusion.raw

3.a
Cammand:
g++ -o SeparableED SeparableED.cpp
SeparableED
Output：SeparableED.raw

3.b
Cammand:
g++ -o MBVQ MBVQ.cpp
MBVQ
Output:MBVQ.raw