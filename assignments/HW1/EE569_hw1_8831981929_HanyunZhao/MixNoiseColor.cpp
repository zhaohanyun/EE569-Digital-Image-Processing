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
#include <opencv2/photo/cuda.hpp>
//This file has new version of file input (dynamic memory, file stream. fread will fail, maybe because
//the memory is not continue any more.
using namespace std;
using namespace cv;

int BytesPerPixel = 3;
int width = 768;
int height = 512;
string argv[3];


void analyzeNoise(unsigned char ***Imagedata, unsigned char ***ImagedataSrc){
    ////////////////////////////output to file for py plot
    int i,j;
    int dataR[256*2];
    int dataG[256*2];
    int dataB[256*2];
    for(i=0;i<256*2;i++) {dataR[i]=0;dataG[i]=0;dataB[i]=0;}
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
           // cout<<(int)(Imagedata[i][j][0]-ImagedataSrc[i][j][0])<<endl;
            dataR[Imagedata[i][j][0]-ImagedataSrc[i][j][0]+255] += 1;
            dataG[Imagedata[i][j][1]-ImagedataSrc[i][j][1]+255] += 1;
            dataB[Imagedata[i][j][2]-ImagedataSrc[i][j][2]+255] += 1;
        }

    }

    ofstream fileout;
    fileout.open("Flower_R_noise_Histo.txt");

    for (i = 0; i < 256*2; i++) {
        fileout << dataR[i] << endl;
    }
    fileout.close();

    fileout.open("Flower_G_noise_Histo.txt");

    for (i = 0; i < 256*2; i++) {
        fileout << dataG[i] << endl;
    }
    fileout.close();

    fileout.open("Flower_B_noise_Histo.txt");

    for (i = 0; i < 256*2; i++) {
        fileout << dataB[i] << endl;
    }
    fileout.close();
}


void Denoise(unsigned char ***Imagedata, unsigned char ***ImagedataSrc, unsigned char ***ImagedataOut){
    ////////////////////////////////////////median filter
    int i,j,k,l;
    int m,n;
    int cnt;
    for(i=2;i<height-2;i++){
        for(j=2;j<width-2;j++){
            for(k=0;k<BytesPerPixel;k++){
                if(abs(Imagedata[i][j][k]-ImagedataSrc[i][j][k])>10){
                    //apply median filter of 5*5
                    vector<unsigned char> array={};
                    cnt=0;
                    for(m=-2;m<=2;m++){
                        for(n=-2;n<=2;n++){
                            if(abs(Imagedata[i+m][j+n][k]-ImagedataSrc[i+m][j+n][k])<20)
                                array.push_back(Imagedata[i+m][j+n][k]);
                        }
                    }
                    if(!array.empty()){
                        sort(array.begin(),array.end());
                        unsigned char median = array[floor(array.size() / 2)];
                        ImagedataOut[i][j][k] = median;
                    }
                }
            }
        }
    }

    Mat img(height,width,CV_8UC3);

    for(i=0;i<height;i++) {
        for (j = 0; j < width; j++) {
            for (k = 0; k < BytesPerPixel; k++) {
                Imagedata[i][j][k]=ImagedataOut[i][j][k];
                img.at<Vec3b>(i,j)[k]=Imagedata[i][j][k];
            }
        }
    }
    /////////////////////////////////////Gaussian, but do not have significant impact
    /*
    double sigmaC=4;
    double sigmaS=100;
    //8,0.1     https://people.csail.mit.edu/sparis/bf_course/course_notes.pdf
    double w;
    int size=9;
    double numerator,denominator;
    for(i=(size-1)/2;i<512-(size-1)/2;i++){
        for(j=(size-1)/2;j<768-(size-1)/2;j++){
            w=0;numerator=0;denominator=0;
            for(k=i-(size-1)/2;k<=i+(size-1)/2;k++){
                for(l=j-(size-1)/2;l<=j+(size-1)/2;l++){
                    //if (k==i && l==j) continue;
                    w=exp(-(pow(i-k,2)+pow(j-l,2))/(2*pow(sigmaC,2)) - pow(Imagedata[i][j][0]-Imagedata[k][l][0],2)/(2*pow(sigmaS,2)));
                    denominator+=w;
                    numerator+=Imagedata[k][l][0]*w;
                }
            }
            ImagedataOut[i][j][0]=(unsigned char)floor(numerator/denominator);

        }
    }

    for(i=0;i<height;i++) {
        for (j = 0; j < width; j++) {
            for (k = 0; k < BytesPerPixel; k++) {
                Imagedata[i][j][k]=ImagedataOut[i][j][k];
                img.at<Vec3b>(i,j)[k]=Imagedata[i][j][k];
            }
        }
    }
    *//////////////////////////////////////// NLM

    Mat newimg;
    fastNlMeansDenoisingColored(img,newimg,10,10,3,21); //warning: different with opencv document

    for(i=1;i<height-1;i++) {
        for (j = 1; j < width - 1; j++) {
            for (k = 0; k < BytesPerPixel; k++) {
                ImagedataOut[i][j][k]=img.at<Vec3b>(i,j)[k];
            }
        }
    }

////////////////////////////////////
}



int main(){
    // Allocate image data array
    argv[0]="";
    argv[1]="images/Flower_noisy.raw";
    argv[2]="output/Flower_denoise.raw";

    ifstream filenoisy,filesrc;
    filenoisy.open("images/Flower_noisy.raw",ios::in | ios::binary);
    filesrc.open("images/Flower.raw",ios::in | ios::binary);
    unsigned char ***Imagedata;
    unsigned char ***ImagedataSrc;
    unsigned char ***ImagedataOut;
    Imagedata=new unsigned char **[height];
    ImagedataSrc=new unsigned char **[height];
    ImagedataOut=new unsigned char **[height];
    int i,j,k;
    int cnt=0;
    for(i=0; i<height; i++)
    {
        Imagedata[i]=new unsigned char *[width];
        ImagedataSrc[i]=new unsigned char *[width];
        ImagedataOut[i]=new unsigned char *[width];
        for(j=0; j<width; j++) {
            Imagedata[i][j] = new unsigned char[BytesPerPixel];
            ImagedataSrc[i][j] = new unsigned char[BytesPerPixel];
            ImagedataOut[i][j] = new unsigned char[BytesPerPixel];
            for (k = 0; k < BytesPerPixel; k++) {
                filenoisy>>noskipws>>Imagedata[i][j][k];
                filesrc>>noskipws>>ImagedataSrc[i][j][k];
                ImagedataOut[i][j][k]=Imagedata[i][j][k];
            }
        }
    }
    filenoisy.close();
    filesrc.close();

    ///////////////////////
    //d.1
    //analyzeNoise(Imagedata,ImagedataSrc);

    //d.2
    Denoise(Imagedata,ImagedataSrc,ImagedataOut);
    ///////////////////////

    ofstream fileout;
    fileout.open("output/Flower_color_Denoise.raw",ios::binary);
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
            delete [] ImagedataSrc[i][j];
            delete [] ImagedataOut[i][j];
        }
    }
    for(i=0; i<height; i++)
    {
        delete [] Imagedata[i];
        delete [] ImagedataSrc[i];
        delete [] ImagedataOut[i];
    }
    delete [] Imagedata;
    delete [] ImagedataSrc;
    delete [] ImagedataOut;
    ////////////////////////////////////////
}
