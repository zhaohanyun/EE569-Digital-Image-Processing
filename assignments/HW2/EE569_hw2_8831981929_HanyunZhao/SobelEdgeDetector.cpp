#include <iostream>
#include "fileIO.h"
#include <cmath>
#include <vector>
#include <algorithm>
void RGB2Y(unsigned char***RGB,unsigned char***Y, int width=481, int height=321){
    //RGB[heigth][width][3], Y[heigth][width][1]
    int i,j,k;
    for(i=0; i<height; i++) {
        for(j=0; j<width; j++) {
            Y[i][j][0]=(unsigned char)floor(RGB[i][j][0]*0.2989+RGB[i][j][1]*0.5870+RGB[i][j][2]*0.1140);
        }
    }
}

void Gradient(unsigned char***ImagedataY, double***GF,double ***Gx,double***Gy,
        int width=481, int height=321){
    int i,j,k;
    for(i=1; i<height-1; i++) {
        for(j=1; j<width-1; j++) {
            Gx[i][j][0]=(ImagedataY[i-1][j-1][0]-ImagedataY[i-1][j+1][0]+ImagedataY[i+1][j-1][0]-ImagedataY[i+1][j+1][0]
                    +2*ImagedataY[i][j-1][0]-2*ImagedataY[i][j+1][0])/4.0;
            Gy[i][j][0]=(-ImagedataY[i-1][j-1][0]-ImagedataY[i-1][j+1][0]+ImagedataY[i+1][j-1][0]-ImagedataY[i+1][j+1][0]
                                              -2*ImagedataY[i-1][j][0]+2*ImagedataY[i+1][j][0])/4.0;
            GF[i][j][0]=sqrt(pow(Gx[i][j][0],2)+pow(Gy[i][j][0],2));
        }
    }
}

void Normalize(double***Imagedata,unsigned char*** ImageOutput, int width=481, int height=321){
    //EFFECT:normalize gradient to 0-255
    int i,j,k;
    double max=0;
    for(i=0; i<height; i++) {
        for(j=0; j<width; j++) {
            max=Imagedata[i][j][0]>max?Imagedata[i][j][0]:max;
        }
    }
    for(i=0; i<height; i++) {
        for(j=0; j<width; j++) {
            ImageOutput[i][j][0]=(unsigned char)floor(Imagedata[i][j][0]/max*255);
        }
    }
}

void Threshold(double ***Imagedata, unsigned char*** ImageOutput, double thresPercentage, int width=481,int height=321){
    //EFFECT set the threshold of boundary to be top [thres]%, then adjust pixels to 0(edge) or 255(background)
    //thresPercentage: top [thres]% will be edge
    int i,j,k;
    std::vector<double> pixels;
    for(i=0; i<height; i++) {
        for(j=0; j<width; j++) {
            pixels.push_back(Imagedata[i][j][0]);
        }
    }
    sort(pixels.begin(),pixels.end());
    double threshold=pixels[floor((1-thresPercentage/100)*height*width)];
    for(i=0; i<height; i++) {
        for(j=0; j<width; j++) {
            ImageOutput[i][j][0]=(unsigned char)(Imagedata[i][j][0]<threshold?255:0);
        }
    }
}


int main(int argc, char *argv[]) {
    int BytesPerPixel = 3;
    int width = 481;
    int height = 321;
    int i,j,k;

    string PathInput=argv[1];
    //string PathOutput=argv[2];

    unsigned char***ImageData=AllocateMem<unsigned char>();//original image
    unsigned char***ImageDataY=AllocateMem<unsigned char>(1);//origianl image to Y channel
    unsigned char***ImageOutput=AllocateMem<unsigned char>(1);//output of gradient map
    double***Gx=AllocateMem<double>(1);
    double***Gy=AllocateMem<double>(1);
    double***GF=AllocateMem<double>(1);

    LoadImage(ImageData,PathInput);
    RGB2Y(ImageData,ImageDataY);

    Gradient(ImageDataY,GF,Gx,Gy);

    Normalize(Gx,ImageOutput);
    OutputImage(ImageOutput,"Output/Pig x Gradient.raw",1);

    Normalize(Gy,ImageOutput);
    OutputImage(ImageOutput,"Output/Pig y Gradient.raw",1);

    Normalize(GF,ImageOutput);
    OutputImage(ImageOutput,"Output/Pig gradient.raw",1);

    Threshold(GF,ImageOutput,5);
    OutputImage(ImageOutput,"Output/PigEdge5.raw",1);


    FreeImage<unsigned char>(ImageData);
    FreeImage<unsigned char>(ImageDataY);
    FreeImage<unsigned char>(ImageOutput);
    FreeImage<double>(Gx);
    FreeImage<double>(Gy);
    FreeImage<double>(GF);

    return 0;
}

