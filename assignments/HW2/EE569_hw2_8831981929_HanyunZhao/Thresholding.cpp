//
// Created by Administrator on 2022/2/20.
//

#include <iostream>
#include "fileIO.h"
#include <cmath>
#include <random>
void FixedThresholding(unsigned char***Imagedata, unsigned char*** ImageOut, int width=600, int height=400){
    int i,j,k;
    int T=128;
    for(i=0;i<height;i++){
        for(j=0;j<width;j++){
            ImageOut[i][j][0]=(unsigned char)(Imagedata[i][j][0]<T?0:255);
        }
    }
    string PathOutput="Output/BridgeFixed.raw";
    OutputImage(ImageOut,PathOutput,1,width,height);
}


void RandomThresholding(unsigned char***Imagedata, unsigned char*** ImageOut, int width=600, int height=400){
    int i,j,k;
    int T;
    for(i=0;i<height;i++){
        for(j=0;j<width;j++){
            T=rand()%256;
            ImageOut[i][j][0]=(unsigned char)(Imagedata[i][j][0]<T?0:255);
        }
    }
    string PathOutput="Output/BridgeRandom.raw";
    OutputImage(ImageOut,PathOutput,1,width,height);
}

int main() {
    int BytesPerPixel = 3;
    int width = 600;
    int height = 400;
    int i, j, k;

    string PathInput = "HW2_images/Bridge.raw";
    //string PathOutput=argv[2];

    unsigned char ***ImageData = AllocateMem<unsigned char>(1,width,height);//original image
    unsigned char ***ImageOutput = AllocateMem<unsigned char>(1,width,height);
    LoadImage(ImageData,PathInput,1,width,height);


    FixedThresholding(ImageData,ImageOutput);
    RandomThresholding(ImageData,ImageOutput);

    FreeImage<unsigned char>(ImageData,1,width,height);
    FreeImage<unsigned char>(ImageOutput,1,width,height);
    cout<<"here"<<endl;
    return 0;
}