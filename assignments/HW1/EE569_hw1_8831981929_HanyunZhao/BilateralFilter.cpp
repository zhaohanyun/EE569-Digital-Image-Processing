//
// Created by Administrator on 2022/1/29.
//
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <fstream>
#include <cmath>
#include <queue>
using namespace std;

void applyFilter(unsigned char*** (&Imagedata), unsigned char*** (&ImagedataOut),int size) {
    //size 3*3 or 5*5, use both to compare results
    double sigmaC=2;
    double sigmaS=50;
    //8,0.1     https://people.csail.mit.edu/sparis/bf_course/course_notes.pdf
    int i,j,k,l;
    double w;
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


    unsigned char ImageOridata[512][768][1];//the size of House.raw
    FILE *file;
    // Read image (filename specified by first argument) into image data matrix
    if (!(file = fopen("images/Flower_gray.raw", "rb"))) {
        cout << "Cannot open file: " << "images/Flower_gray.raw" << endl;
        exit(1);
    }
    fread(ImageOridata, sizeof(unsigned char),512*768*1, file);
    fclose(file);

    double MSE=0;
    for(i=0;i<512;i++){
        for(j=0;j<768;j++){
            MSE+=pow((ImagedataOut[i][j][0]-ImageOridata[i][j][0]),2)/(768*512);
        }
    }
    double PSNR=10*log10(255*255/MSE);
    cout<<PSNR<<endl;
}

int main(int argc, char *argv[]) {
    // Define file pointer and variables
    ifstream file;
    int BytesPerPixel = 1;
    int width = 768;
    int height = 512;

    if(argc<4){
        return -1;
    }

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
    //////////////////////////////////
    //TODO:
    int size=atoi(argv[3]);
    applyFilter(Imagedata,ImagedataOut,size);

    //////////////////////////////////////

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

