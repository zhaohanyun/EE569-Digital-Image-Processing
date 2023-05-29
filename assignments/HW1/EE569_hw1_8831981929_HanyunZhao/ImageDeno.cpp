//
// Created by Administrator on 2022/1/28.
//
//calculate the difference between source and noisy image, and output noise distribution to txt

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <fstream>
#include <cmath>
#include <queue>
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

int main() {
    // Define file pointer and variables
    FILE *file;
    int BytesPerPixel = 1;
    int width = 768;
    int height = 512;


    // Allocate image data array
    unsigned char ImagedataNoisy[height][width][BytesPerPixel];//the size of House.raw

    // Read image (filename specified by first argument) into image data matrix
    if (!(file = fopen("images/Flower_gray_noisy.raw", "rb"))) {//don't know why argv[1] doesn't work
        cout << "Cannot open file: " << "images/Flower_gray_noisy.raw" << endl;
        exit(1);
    }
    fread(ImagedataNoisy, sizeof(unsigned char), width * height * BytesPerPixel, file);
    fclose(file);

    unsigned char ImagedataSrc[height][width][BytesPerPixel];//the size of House.raw

    // Read image (filename specified by first argument) into image data matrix
    if (!(file = fopen("images/Flower_gray.raw", "rb"))) {//don't know why argv[1] doesn't work
        cout << "Cannot open file: " << "images/Flower_gray.raw" << endl;
        exit(1);
    }
    fread(ImagedataSrc, sizeof(unsigned char), width * height * BytesPerPixel, file);
    fclose(file);

    ////////////////////////////output to file for py plot
    int i,j;
    int data[256] = {0};
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            data[ImagedataNoisy[i][j][0]-ImagedataSrc[i][j][0]+120] += 1;
        }
    }

    ofstream fileout;
    fileout.open("Flower_gray_noise_Histo.txt");

    for (i = 0; i < 256; i++) {
        fileout << data[i] << endl;
    }
    fileout.close();



}

int main(){
    generateHistoData();
    return 0;
}