//
// Created by Administrator on 2022/2/16.
//

#include <iostream>
#include "fileIO.h"
#include <cmath>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <string>
#include "fileIO.h"
using namespace std;
using namespace cv;

int width=481;
int height=321;


int main() {
    int BytesPerPixel = 3;
    int width = 481;
    int height = 321;
    int i, j, k;

    unsigned char***ImageData=AllocateMem<unsigned char>();//original image
    unsigned char***ImageOutput=AllocateMem<unsigned char>(1);//output of gradient map

    string PathInput="HW2_images/Pig.jpg";
    string PathOutput="Output/PigCanny-250-300.raw";

    LoadImage(ImageData,PathInput);

    Mat imagein=imread(PathInput);
    Mat imageout;
    cv::Canny(imagein,imageout,250,300);

    for(i=0; i<height; i++) {
        for(j=0; j<width; j++) {
            ImageOutput[i][j][0]=imageout.at<uchar>(i,j);
        }
    }
    OutputImage(ImageOutput,PathOutput,1);

    FreeImage<unsigned char>(ImageData);
    FreeImage<unsigned char>(ImageOutput);

    return 0;

}