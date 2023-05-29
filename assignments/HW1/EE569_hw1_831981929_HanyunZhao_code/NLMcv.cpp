//
// Created by Administrator on 2022/1/29.
//

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cmath>
#include <opencv2/opencv.hpp>
#include <opencv2/photo.hpp>

//This file has new version of file input (dynamic memory, file stream. fread will fail, maybe because
//the memory is not continue any more.
using namespace std;
using namespace cv;

//int main(int argc, char *argv[]){
int main(){
    //FILE *file;
    ifstream file;
    int BytesPerPixel = 1;
    int width = 768;
    int height = 512;

    string argv[3];
    argv[0]="";
    argv[1]="images/Flower_gray_noisy.raw";
    argv[2]="output/Flower_gray_NLM.raw";


    // Allocate image data array
    file.open(argv[1],ios::in | ios::binary);
    unsigned char ***Imagedata;
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

    unsigned char cvImg[width*height];

    for(i=0; i<height; i++) {
        for(j=0; j<width; j++) {
            cvImg[i*width+j]=Imagedata[i][j][0];
        }
    }

    Mat img(height, width, CV_8UC1, cvImg);
    Mat newimg;
////////////////////////////////////
    //TODO:
    cv::fastNlMeansDenoising(img,newimg,10,3,21);
    for(i=0; i<height; i++) {
        for(j=0; j<width; j++) {
            Imagedata[i][j][0]=newimg.at<uchar>(i,j);
        }
    }

    unsigned char ImageOridata[512][768][1];//the size of House.raw
    FILE *file1;
    // Read image (filename specified by first argument) into image data matrix
    if (!(file1 = fopen("images/Flower_gray.raw", "rb"))) {
        cout << "Cannot open file: " << "images/Flower_gray.raw" << endl;
        exit(1);
    }
    fread(ImageOridata, sizeof(unsigned char),512*768*1, file1);
    fclose(file1);

    double MSE=0;
    for(i=0;i<512;i++){
        for(j=0;j<768;j++){
            MSE+=pow((Imagedata[i][j][0]-ImageOridata[i][j][0]),2)/(768*512);
        }
    }
    double PSNR=10*log10(255*255/MSE);
    cout<<PSNR<<endl;

//    while(1) {
//        cv::imshow("Opencv CLAHE", img);
//        if ( (char)27 == (char) waitKey(1) ) break;
//    }


    ofstream fileout;
    fileout.open(argv[2],ios::binary);
    for(i=0; i<height; i++) {
        for(j=0; j<width; j++) {
            for (k = 0; k < BytesPerPixel; k++) {
                fileout<<noskipws<<Imagedata[i][j][k];
            }
        }
    }
    fileout.close();

//    ofstream fileout;
//    fileout.open(argv[2],ios::binary);
//    for(i=0; i<height; i++) {
//        for(j=0; j<width; j++) {
//            for (k = 0; k < BytesPerPixel; k++) {
//                fileout<<Imagedata[i][j][k];
//            }
//        }
//    }
//    fileout.close();
    ////////////////////////////////////


    /////////////////////////////////free the memory
    for(i=0; i<height; i++)
    {
        for(j=0; j<width; j++)
        {
            delete [] Imagedata[i][j];
        }
    }
    for(i=0; i<height; i++)
    {
        delete [] Imagedata[i];
    }
    delete [] Imagedata;
    ////////////////////////////////////////
    return 0;
}
