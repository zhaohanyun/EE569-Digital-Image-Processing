//
// Created by Administrator on 2022/2/14.
//

#ifndef EE569_HW2_8831981929_HANYUNZHAO_FILEIO_H
#define EE569_HW2_8831981929_HANYUNZHAO_FILEIO_H
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <fstream>
#include <string>
using namespace std;

//unsigned char *** AllocateMem(int=3, int=481, int=321);
//
//double *** AllocateMemDouble(int=3, int=481, int height=321);
template<typename T> T *** AllocateMem(int BytesPerPixel=3, int width=481, int height=321){
    // Allocate image data array
    T ***Imagedata;
    Imagedata=new T **[height];
    int i,j,k;
    int cnt=0;
    for(i=0; i<height; i++)
    {
        Imagedata[i]=new T *[width];
        for(j=0; j<width; j++) {
            Imagedata[i][j] = new T[BytesPerPixel];
            for(k=0;k<BytesPerPixel;k++){
                Imagedata[i][j][k]=0;
            }
        }
    }
    return Imagedata;
}


//void LoadImage(unsigned char ***, string, int=3, int=481, int=321);
void LoadImage(unsigned char ***Imagedata, string FilePath,int BytesPerPixel=3,  int width=481, int height=321){
    ifstream file;
    file.open(FilePath,ios::in | ios::binary);
    int i,j,k;
    for(i=0; i<height; i++) {
        for(j=0; j<width; j++) {
            for (k = 0; k < BytesPerPixel; k++) {
                file>>noskipws>>Imagedata[i][j][k];
            }
        }
    }
    file.close();
}

//void ImageOutput(unsigned char ***, string, int=3 , int=481, int=321);
void OutputImage(unsigned char ***ImagedataOut,string FilePath, int BytesPerPixel=3,  int width=481, int height=321){
    ofstream fileout;
    int i,j,k;
    fileout.open(FilePath,ios::binary);
    for(i=0; i<height; i++) {
        for(j=0; j<width; j++) {
            for (k = 0; k < BytesPerPixel; k++) {
                fileout<<noskipws<<ImagedataOut[i][j][k];
            }
        }
    }
    fileout.close();
}

//template<typename T> void FreeImage(T ***, int=3, int=481, int=321);
template<typename T> void FreeImage(T ***Imagedata, int BytesPerPixel=3, int width=481, int height=321){
    int i,j,k;
    for(i=0; i<height; i++) {
        for(j=0; j<width; j++){
            delete [] Imagedata[i][j];
        }
    }
    for(i=0; i<height; i++) {
        delete [] Imagedata[i];
    }
    delete [] Imagedata;
}

#endif //EE569_HW2_8831981929_HANYUNZHAO_FILEIO_H
