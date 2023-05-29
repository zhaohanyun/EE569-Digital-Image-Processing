//
// Created by Administrator on 2022/1/30.
//
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cmath>
#include <random>
using namespace std;


int main(int argc, char*argv[]){
    ifstream file;
    int BytesPerPixel = 1;
    int width = 768;
    int height = 512;

    //FrostedGlassFilter input output color/gray N
    if(argc!=5){
        return -1;
    }
    BytesPerPixel=strtol(argv[3], nullptr,10);
    int N=strtol(argv[4], nullptr,10);

    // Allocate image data array
    file.open(argv[1],ios::in | ios::binary);
    unsigned char ***Imagedata;
    unsigned char ***ImagedataOut;
    Imagedata=new unsigned char **[height];
    int i,j,k;
    int cnt=0;
    for(i=0; i<height; i++)
    {
        Imagedata[i]=new unsigned char *[width];
        for(j=0; j<width; j++) {
            Imagedata[i][j] = new unsigned char[BytesPerPixel];
            for (k = 0; k < BytesPerPixel; k++) {
                file>>noskipws>>Imagedata[i][j][k];
            }
        }
    }
    file.close();

    ImagedataOut=new unsigned char **[height];
    for(i=0; i<height; i++)
    {
        ImagedataOut[i]=new unsigned char *[width];
        for(j=0; j<width; j++) {
            ImagedataOut[i][j] = new unsigned char[BytesPerPixel];
            for (k = 0; k < BytesPerPixel; k++) {
                ImagedataOut[i][j][k]=Imagedata[i][j][k];
            }
        }
    }



    /////////////////////////////////////
    //TODO:
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd());  //Standard mersenne_twister_engine seeded with rd()
    uniform_int_distribution<> myRandom(-(N-1)/2,(N-1)/2);
    int m,n;
    for(i=(N-1)/2;i<height-(N-1)/2;i++){
        for(j=(N-1)/2;j<width-(N-1)/2;j++) {
            for(k=0;k<BytesPerPixel;k++){
                ImagedataOut[i][j][k]=Imagedata[i+myRandom(gen)][j+myRandom(gen)][k];
            }
        }
    }

    ////////////////////////////////////////////////
    ofstream fileout;
    fileout.open(argv[2],ios::binary);
    for(i=0; i<height; i++) {
        for(j=0; j<width; j++) {
            for (k = 0; k < BytesPerPixel; k++) {
                fileout<<noskipws<<ImagedataOut[i][j][k];
            }
        }
    }
    fileout.close();
    /////////////////////////////////free the memory
    for(i=0; i<height; i++)
    {
        for(j=0; j<width; j++)
        {
            delete [] Imagedata[i][j];
            delete [] ImagedataOut[i][j];
        }
    }
    for(i=0; i<height; i++)
    {
        delete [] Imagedata[i];
        delete [] ImagedataOut[i];
    }
    delete [] Imagedata;
    delete [] ImagedataOut;
    ////////////////////////////////////////

    return 0;
}
