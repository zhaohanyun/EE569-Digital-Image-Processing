//
// Created by Administrator on 2022/1/25.
//

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cmath>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
//This file has new version of file input (dynamic memory, file stream. fread will fail, maybe because
//the memory is not continue any more.
using namespace std;
using namespace cv;
void RGB2YUV(unsigned char (*&RGB)){
    unsigned char YUV[3];
    YUV[0]=(unsigned char)(0.257*RGB[0]+0.504*RGB[1]+0.098*RGB[2]+16);
    YUV[1]=(unsigned char)(-0.148*RGB[0]-0.291*RGB[1]+0.439*RGB[2]+128);
    YUV[2]=(unsigned char)(0.439*RGB[0]-0.368*RGB[1]-0.071*RGB[2]+128);
    for(int i=0;i<3;i++) RGB[i]=YUV[i];
    //now the RGB[3] actually stores the YUV value
}

void YUV2RGB(unsigned char(*&YUV)){
    unsigned char RGB[3];
    RGB[0]=(unsigned char)(1.164*(YUV[0]-16)+1.596*(YUV[2]-128));
    RGB[1]=(unsigned char)(1.164*(YUV[0]-16)-0.813*(YUV[2]-128)-0.391*(YUV[1]-128));
    RGB[2]=(unsigned char)(1.164*(YUV[0]-16)+2.018*(YUV[1]-128));
    for(int i=0;i<3;i++) YUV[i]=RGB[i];
    //now stores the RGB values
}

//int main(int argc, char *argv[]){
int main(){
    //FILE *file;
    ifstream file;
    int BytesPerPixel = 3;
    int width = 600;
    int height = 400;

    string argv[3];
    argv[0]="";
    argv[1]="images/Taj_Mahal.raw";
    argv[2]="output/TajCLAHE.raw";


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

    unsigned char Ychannel[width*height];
    unsigned char newYchannel[width*height];


    for(i=0; i<height; i++) {
        for(j=0; j<width; j++) {
            RGB2YUV(Imagedata[i][j]);
            Ychannel[i*width+j]=Imagedata[i][j][0];
        }
    }

    Mat img(height, width, CV_8UC1, Ychannel);
    Mat newimg;
////////////////////////////////////
    //TODO: Opencv CLAHE
    cv::Ptr<cv::CLAHE> myCLAHE=cv::createCLAHE();
    myCLAHE->setClipLimit(2.5);//TODO: tune
    myCLAHE->setTilesGridSize(Size(8,8));//TODO: tune
    myCLAHE->apply(img,newimg);

    for(i=0; i<height; i++) {
        for(j=0; j<width; j++) {
            newYchannel[i*width+j]=newimg.at<uchar>(i,j);
        }
    }

//    while(1) {
//        cv::imshow("Opencv CLAHE", img);
//        if ( (char)27 == (char) waitKey(1) ) break;
//    }


    ofstream fileout;
    fileout.open(argv[2],ios::binary);
    for(i=0; i<height; i++) {
        for(j=0; j<width; j++) {
            Imagedata[i][j][0]=newYchannel[i*width+j];
            //if(newYchannel[i*width+j]>250) cout<<i<<" "<<j<<endl;
            YUV2RGB(Imagedata[i][j]);
            //3.YUV 2 RGB
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
