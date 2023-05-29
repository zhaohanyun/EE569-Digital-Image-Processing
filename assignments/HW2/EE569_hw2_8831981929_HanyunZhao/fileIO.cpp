//
// Created by Administrator on 2022/2/14.
//
#include "fileIO.h"

using namespace std;

//unsigned char *** AllocateMem(int BytesPerPixel, int width, int height){
//    // Allocate image data array
//    unsigned char ***Imagedata;
//    Imagedata=new unsigned char **[height];
//    int i,j,k;
//    int cnt=0;
//    for(i=0; i<height; i++)
//    {
//        Imagedata[i]=new unsigned char *[width];
//        for(j=0; j<width; j++) {
//            Imagedata[i][j] = new unsigned char[BytesPerPixel];
//        }
//    }
//    return Imagedata;
//}
//
//double *** AllocateMemDouble(int BytesPerPixel, int width, int height){
//    // Allocate image data array
//    double ***Imagedata;
//    Imagedata=new double **[height];
//    int i,j,k;
//    int cnt=0;
//    for(i=0; i<height; i++)
//    {
//        Imagedata[i]=new double *[width];
//        for(j=0; j<width; j++) {
//            Imagedata[i][j] = new double[BytesPerPixel];
//        }
//    }
//    return Imagedata;
//}

//void LoadImage(unsigned char ***Imagedata, int BytesPerPixel, string FilePath, int width, int height){
//    ifstream file;
//    file.open(FilePath,ios::in | ios::binary);
//    int i,j,k;
//    for(i=0; i<height; i++) {
//        for(j=0; j<width; j++) {
//            for (k = 0; k < BytesPerPixel; k++) {
//                file>>noskipws>>Imagedata[i][j][k];
//            }
//        }
//    }
//    file.close();
//}

void ImageOutput(unsigned char ***ImagedataOut, int BytesPerPixel, string FilePath, int width, int height){
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

//template<typename T> void FreeImage(T ***Imagedata, int BytesPerPixel, int width, int height){
//    int i,j,k;
//    for(i=0; i<height; i++) {
//        for(j=0; j<width; j++){
//            delete [] Imagedata[i][j];
//        }
//    }
//    for(i=0; i<height; i++) {
//        delete [] Imagedata[i];
//    }
//    delete [] Imagedata;
//}