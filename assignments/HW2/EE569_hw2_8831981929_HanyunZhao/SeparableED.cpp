//
// Created by Administrator on 2022/2/20.
//
#include <iostream>
#include "fileIO.h"
#include <cmath>

void RGBCMY(unsigned char*** Imagedata,int BytesPerPixel=3,int width=500,int height=375){
    int i,j,k;
    for(i=0;i<height;i++){
        for(j=0;j<width;j++){
            for(k=0;k<BytesPerPixel;k++){
                Imagedata[i][j][k]=(unsigned char)(255-Imagedata[i][j][k]);
            }
        }
    }
}

void FS_Diffusion(unsigned char***Imagedata, unsigned char*** ImageOutput,int BytesPerPixel=3,int width=500, int height=375){
    double***Error=AllocateMem<double>(3,width,height);
    int T=128;
    int i,j,k;
    for(k=0;k<BytesPerPixel;k++) {
        for (i = 1; i < height - 1; i++) {
            for (j = 1; j < width - 1; j++) {
                double F_new = Imagedata[i][j][k] + Error[i][j][k];
                auto result = (unsigned char) (F_new > T ? 255 : 0);
                double error = result - F_new;
                Error[i][j + 1][k] -= 7 / 16.0 * error;
                Error[i + 1][j - 1][k] -= 3 / 16.0 * error;
                Error[i + 1][j][k] -= 5 / 16.0 * error;
                Error[i + 1][j + 1][k] -= 1 / 16.0 * error;
                ImageOutput[i][j][k] = result;
            }
        }
    }

    FreeImage<double>(Error,3,width,height);
}


int main(int argc, char*argv[]) {
    int BytesPerPixel = 3;
    int width = 500;
    int height = 375;
    int i, j, k;

    unsigned char***ImageData=AllocateMem<unsigned char>(BytesPerPixel,width,height);//original image
    unsigned char***ImageDataCMY=AllocateMem<unsigned char>(BytesPerPixel,width,height);
    unsigned char***ImageOutput=AllocateMem<unsigned char>(BytesPerPixel,width,height);

    string PathInput = "HW2_images/Bird.raw";
    string PathOutput="Output/SeparableED.raw";
    LoadImage(ImageData,PathInput,BytesPerPixel,width,height);
   // cout<<(int)ImageData[20][350][0]<<" "<<(int)ImageData[20][350][1]<<" "<<(int)ImageData[20][350][2]<<endl;
    RGBCMY(ImageData);
    FS_Diffusion(ImageData,ImageOutput,BytesPerPixel);
    RGBCMY(ImageOutput);
    OutputImage(ImageOutput,PathOutput,BytesPerPixel,width,height);


    FreeImage<unsigned char>(ImageData,BytesPerPixel,width,height);
    FreeImage<unsigned char>(ImageDataCMY,BytesPerPixel,width,height);
    FreeImage<unsigned char>(ImageOutput,BytesPerPixel,width,height);
    cout<<"here"<<endl;
    return 0;
}