//
// Created by Administrator on 2022/2/20.
//

#include <iostream>
#include "fileIO.h"
#include <cmath>

void FS_Diffusion(unsigned char***Imagedata, unsigned char*** ImageOutput,int width=600, int height=400){
    double***Error=AllocateMem<double>(1,width,height);
    int T=128;
    int i,j,k;

    for(i=1;i<height-1;i++){
        for(j=1;j<width-1;j++){

            double F_new=Imagedata[i][j][0]+Error[i][j][0];
            auto result=(unsigned char) (F_new>T?255:0);
            double error=result-F_new;
            Error[i][j+1][0]-=7/16.0*error;
            Error[i+1][j-1][0]-=3/16.0*error;
            Error[i+1][j][0]-=5/16.0*error;
            Error[i+1][j+1][0]-=1/16.0*error;

            ImageOutput[i][j][0]=result;

        }
    }
    string PathOutput="Output/FS_Diffusion.raw";
    OutputImage(ImageOutput,PathOutput,1,width,height);

    FreeImage<double>(Error,1,width,height);
}

void JJN_Diffusion(unsigned char***Imagedata, unsigned char*** ImageOutput,int width=600, int height=400){
    double***Error=AllocateMem<double>(1,width,height);
    int T=128;
    int i,j,k;

    for(i=2;i<height-2;i++){
        for(j=2;j<width-2;j++){

            double F_new=Imagedata[i][j][0]+Error[i][j][0];
            auto result=(unsigned char) (F_new>T?255:0);
            double error=result-F_new;
            Error[i][j+1][0]-=7/48.0*error;
            Error[i][j+2][0]-=5/48.0*error;

            Error[i+1][j-2][0]-=3/48.0*error;
            Error[i+1][j-1][0]-=5/48.0*error;
            Error[i+1][j][0]-=7/48.0*error;
            Error[i+1][j+1][0]-=5/48.0*error;
            Error[i+1][j+2][0]-=3/48.0*error;

            Error[i+2][j-2][0]-=1/48.0*error;
            Error[i+2][j-1][0]-=3/48.0*error;
            Error[i+2][j][0]-=5/48.0*error;
            Error[i+2][j+1][0]-=3/48.0*error;
            Error[i+2][j+2][0]-=1/48.0*error;

            ImageOutput[i][j][0]=result;

        }
    }
    string PathOutput="Output/JJN_Diffusion.raw";
    OutputImage(ImageOutput,PathOutput,1,width,height);

    FreeImage<double>(Error,1,width,height);
}

void Stucki_Diffusion(unsigned char***Imagedata, unsigned char*** ImageOutput,int width=600, int height=400){
    double***Error=AllocateMem<double>(1,width,height);
    int T=128;
    int i,j,k;

    for(i=2;i<height-2;i++){
        for(j=2;j<width-2;j++){

            double F_new=Imagedata[i][j][0]+Error[i][j][0];
            auto result=(unsigned char) (F_new>T?255:0);
            double error=result-F_new;
            Error[i][j+1][0]-=8/42.0*error;
            Error[i][j+2][0]-=4/42.0*error;

            Error[i+1][j-2][0]-=2/42.0*error;
            Error[i+1][j-1][0]-=4/42.0*error;
            Error[i+1][j][0]-=8/42.0*error;
            Error[i+1][j+1][0]-=4/42.0*error;
            Error[i+1][j+2][0]-=2/42.0*error;

            Error[i+2][j-2][0]-=1/42.0*error;
            Error[i+2][j-1][0]-=2/42.0*error;
            Error[i+2][j][0]-=4/42.0*error;
            Error[i+2][j+1][0]-=2/42.0*error;
            Error[i+2][j+2][0]-=1/42.0*error;

            ImageOutput[i][j][0]=result;

        }
    }
    string PathOutput="Output/Stucki_Diffusion.raw";
    OutputImage(ImageOutput,PathOutput,1,width,height);

    FreeImage<double>(Error,1,width,height);
}


int main(int argc, char*argv[]) {
    int BytesPerPixel = 3;
    int width = 600;
    int height = 400;
    int i, j, k;

    unsigned char***ImageData=AllocateMem<unsigned char>(1,width,height);//original image

    unsigned char***ImageOutput=AllocateMem<unsigned char>(1,width,height);

    string PathInput = "HW2_images/Bridge.raw";
    LoadImage(ImageData,PathInput,1,width,height);

    FS_Diffusion(ImageData,ImageOutput);
    JJN_Diffusion(ImageData,ImageOutput);
    Stucki_Diffusion(ImageData,ImageOutput);

    FreeImage<unsigned char>(ImageData,1,width,height);
    FreeImage<unsigned char>(ImageOutput,1,width,height);
    cout<<"here"<<endl;
    return 0;
}