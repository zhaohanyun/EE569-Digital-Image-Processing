//
// Created by Administrator on 2022/2/20.
//
#include <iostream>
#include "fileIO.h"
#include <cmath>
#include <random>

unsigned char bit_interleave(unsigned char a, unsigned char b){
    unsigned char result=0;
    result+=(a<<4) & 0b10000000;
    result+=(b<<3) & 0b01000000;
    result+=(a<<3) & 0b00100000;
    result+=(b<<2) & 0b00010000;
    result+=(a<<2) & 0b00001000;
    result+=(b<<1) & 0b00000100;
    result+=(a<<1) & 0b00000010;
    result+=(b<<0) & 0b00000001;
    return result;
}

unsigned char bitwise_xor(unsigned char a, unsigned char b){
    return a^b;
}

unsigned char bit_reverse(unsigned char a){
    a = (unsigned char) ((a & 0b11110000) >> 4 | (a & 0b00001111) << 4);
    a = (unsigned char) ((a & 0b11001100) >> 2 | (a & 0b00110011) << 2);
    a = (unsigned char) ((a & 0b10101010) >> 1 | (a & 0b01010101) << 1);
    return a;
}
//
//static unsigned char lookup[16] = {
//        0x0, 0x8, 0x4, 0xc, 0x2, 0xa, 0x6, 0xe,
//        0x1, 0x9, 0x5, 0xd, 0x3, 0xb, 0x7, 0xf, };
//
//unsigned char bit_reverse(unsigned char n) {
//    // Reverse the top and bottom nibble then swap them.
//    return (lookup[n&0b1111] << 4) | lookup[n>>4];
//}

void Dithering(unsigned char***Imagedata, unsigned char*** ImageOut, int matrixSize, int width=600, int height=400){
    //matrixSize=2,8,32
    int i,j,k,l;
    unsigned char I2n[matrixSize][matrixSize];
    for(i=0;i<matrixSize;i++){
        for(j=0;j<matrixSize;j++){
            I2n[i][j]=bit_reverse(bit_interleave((unsigned char) j,bitwise_xor((unsigned char)j, (unsigned char)i)));
            //cout<< int(I2n[i][j])<<" ";
        }
        //cout<<endl;
    }

    for(i=0;i<matrixSize;i++){
        for(j=0;j<matrixSize;j++){
            cout<< int(I2n[i][j]+0.5/pow(matrixSize,2)*255)<<" ";
            //cout<< int(I2n[i][j])<<" ";
        }
        cout<<endl;
    }

    unsigned char ***ThresholdMarix = AllocateMem<unsigned char>(1,width,height);
    for(i=0;i<height;i+=matrixSize){
        for(j=0;j<width;j+=matrixSize){
            //(i,j) is the corner of current matrix
            for(k=i;k<i+matrixSize && k<height;k++){
                for(l=j;l<j+matrixSize && l<width;l++){
                    //ThresholdMarix[k][l][0]=(unsigned char)((I2n[k-i][l-j]+0.5)/pow(matrixSize,2)*255);
                    ThresholdMarix[k][l][0]=(unsigned char)(I2n[k-i][l-j]+0.5/pow(matrixSize,2)*255);
                }
            }
        }
    }
    for(i=0;i<height;i++){
        for(j=0;j<width;j++){
            ImageOut[i][j][0]=(unsigned char)(Imagedata[i][j][0]<ThresholdMarix[i][j][0]?0:255);
        }
    }
    FreeImage<unsigned char>(ThresholdMarix,1,width,height);

}

int main(int argc, char*argv[]) {
    int BytesPerPixel = 3;
    int width = 600;
    int height = 400;
    int i, j, k;
    int matrixSize=stoi(argv[1]);

    string PathInput = "HW2_images/Bridge.raw";
    string PathOutput=argv[2];
    //string PathOutput=argv[2];

    unsigned char ***ImageData = AllocateMem<unsigned char>(1,width,height);//original image
    unsigned char ***ImageOutput = AllocateMem<unsigned char>(1,width,height);
    LoadImage(ImageData,PathInput,1,width,height);

    Dithering(ImageData,ImageOutput,matrixSize);
    OutputImage(ImageOutput,PathOutput,1,width,height);


    FreeImage<unsigned char>(ImageData,1,width,height);
    FreeImage<unsigned char>(ImageOutput,1,width,height);
    cout<<"here"<<endl;
    return 0;

}