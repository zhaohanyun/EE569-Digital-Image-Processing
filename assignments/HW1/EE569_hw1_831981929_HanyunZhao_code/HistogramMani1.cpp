//
// Created by Administrator on 2022/1/22.
//
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cmath>
using namespace std;
void FOutputHistoData(int data[256], string str){
    ofstream fileout;
    fileout.open(str);
    int i;
    for(i=0;i<256;i++){
        fileout<<data[i]<<endl;
    }
    fileout.close();
}

int main(int argc, char *argv[]) {
    // Define file pointer and variables
    FILE *file;
    int BytesPerPixel=1;
    int width = 256;
    int height = 256;

    // Check for proper syntax
//    if (argc < 3) {
//        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
//        cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;
//        return 0;
//    }

    // Check if image is grayscale or color
//    if (argc < 4) {
//        BytesPerPixel = 1; // default is grey image
//    } else {
//        BytesPerPixel = atoi(argv[3]);
//    }

    // Allocate image data array
    unsigned char Imagedata[height][width][BytesPerPixel];//the size of House.raw

    // Read image (filename specified by first argument) into image data matrix
    if (!(file = fopen(argv[1], "rb"))) {
        cout << "Cannot open file: " << argv[1] << endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), width * height * BytesPerPixel, file);
    fclose(file);

    ///////////////////////////////////////////////////////
    //Todo: mycode 1.b.1&2
    //generate the histogram data (output to a file, 256 lines, each line stores one intensity value)
    int data[256]={0};
    int i,j;
    for(i=0;i<height;i++){
        for(j=0;j<width;j++){
            data[Imagedata[i][j][0]]+=1;
        }
    }
    /*  ////////////////////////////output to file for py plot
    ofstream fileout;
    fileout.open("HatHistogram.txt");

    for(i=0;i<256;i++){
        fileout<<data[i]<<endl;
    }
    fileout.close();
    *////////////////////////////////
    double cumdata[256]={0};
    cumdata[0]=data[0]/65536.0;
    for(i=1;i<256;i++){
        cumdata[i]=(data[i])/65536.0+cumdata[i-1];
    }

    int newCumData[256]={0};
    for(i=0;i<256;i++){
        newCumData[i]=(int)floor(cumdata[i]*255);
    }

    /*///////////////////////////////plot the transfer function
    FOutputHistoData(newCumData,"TransferFuncHisto.txt");
    *//////////////////////////////////

    //////////generate new picture of Transfer function based manipulation

    unsigned char ImageOutput1[height][width][BytesPerPixel];
    for(i=0;i<height;i++){
        for(j=0;j<width;j++){
            ImageOutput1[i][j][0]=(unsigned char)newCumData[Imagedata[i][j][0]];
        }
    }

    FILE *b2;
    if (!(b2=fopen("output/MethodAEnhanced.raw","wb"))) {
        cout << "Cannot open file: " << "output/MethodAEnhanced.raw" << endl;
        exit(1);
    }
    fwrite(ImageOutput1, sizeof(unsigned char), width*height, b2);
    fclose(b2);

    /////////////////////////////////////////////////////////
    return 0;
}
