#include <iostream>
#include "fileIO.h"
#include <string>
#include <cmath>


unsigned char colorMapping(unsigned char***SourceImage, int j, int k, int channel,
                  int BytesPerPixel=3,  int width=328, int height=328){
    //EFFECT: give the position in the output wrapped image, return what vlue it should be
    //(j,k) output image
    //(x,y) output cart
    //(u,v) input cart
    //(p,q) input image

    if(j<0 || j>height || k<0 || k>width){
        cout<<"wrong output image coordinate"<<endl;
        exit(-1);
    }
    double x,y;
    x=k+0.5;
    y=height-j-0.5;

    double u=0,v=0;
    if(y<=x && x+y<=328){//the bottom triangle
        u=x;
        v=-2.12035*x+3.12035*y+0.00646448*pow(x,2)-0.00646448*pow(y,2);
    }
    //TODO:
    else if(y>=x && x+y<=328){
        u=3.12872*x-2.12872*y-0.00652951*pow(x,2)+0.00648994*pow(y,2);
        v=y;
    }
    else if(x<=y && x+y>=328){
        u=x;
        v=2.12035*x-1.12035*y-0.00646448*pow(x,2)+0.00646448*pow(y,2);
    }
    else if(x>=y && x+y>=328){
        u=-1.12035*x+2.12035*y+0.00646448*pow(x,2)-0.00646448*pow(y,2);
        v=y;
    }
    else{
        u=x;
        v=y;
    }

    double p,q;
    p=height-v-0.5;
    q=u-0.5;
    if(p<0 ||p>height-1 || q<0 || q>width-1){
        return 0;
//        cout<<"wrong mapping to input image"<<endl;
//        exit(-1);
    }

    //interpolation
    int topleftI=floor(p);
    int topleftJ=floor(q);
    int mappedColor=floor(SourceImage[topleftI][topleftJ][channel]*(1-p+topleftI)*(1-q+topleftJ)+
            (topleftI<p? SourceImage[topleftI+1][topleftJ][channel]*(p-topleftI)*(1-q+topleftJ) : 0)+
            (topleftJ<q? SourceImage[topleftI][topleftJ+1][channel]*(1-p+topleftI)*(q-topleftJ) : 0)+
            ((topleftI<p && topleftJ<q)? SourceImage[topleftI+1][topleftJ+1][channel]*(p-topleftI)*(q-topleftJ) : 0));

    return (unsigned char)mappedColor;
}

void warpping(unsigned char***Imagedata, unsigned char***ImageOutput, int BytesPerPixel=3,  int width=328, int height=328){
    int i,j,k;
    for(i=0; i<height; i++) {
        for(j=0; j<width; j++) {
            for (k = 0; k < BytesPerPixel; k++) {
                ImageOutput[i][j][k]=colorMapping(Imagedata,i,j,k);
            }
        }
    }
    cout<<"finish warping"<<endl;
}

int main(int argc, char*argv[]) {
    int BytesPerPixel = 3;
    int width = 328;
    int height = 328;
    int i,j,k;
    string PathInput=argv[1];
    string PathOutput=argv[2];

    unsigned char***ImageData=AllocateMem<unsigned char>(BytesPerPixel,width,height);
    unsigned char***ImageOutput=AllocateMem<unsigned char>(BytesPerPixel,width,height);
    LoadImage(ImageData,PathInput,BytesPerPixel,width,height);
    warpping(ImageData,ImageOutput);

    OutputImage(ImageOutput,PathOutput,BytesPerPixel,width,height);

    FreeImage<unsigned char>(ImageData,BytesPerPixel,width,height);cout<<"here"<<endl;
    FreeImage<unsigned char>(ImageOutput,BytesPerPixel,width,height);
    return 0;
}
