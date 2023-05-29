//
// Created by Administrator on 2022/1/25.
//

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cmath>
#include <queue>
//This file has new version of file input (dynamic memory, file stream. fread will fail, maybe because
//the memory is not continue any more.
using namespace std;

typedef struct Pixel{
    pair<int,int> position;
    int intensity;
}pixel;
//bool pixelCmp(pixel a, pixel b){
//    return a.intensity>b.intensity;
//}
struct pixelCmp{
    bool operator()(pixel a,pixel b) {
        return a.intensity > b.intensity;
    }
};

void RGB2YUV(unsigned char (*&RGB)){
    unsigned char YUV[3];
    YUV[0]=(unsigned char)floor(0.257*RGB[0]+0.504*RGB[1]+0.098*RGB[2]+16);
    YUV[1]=(unsigned char)floor(-0.148*RGB[0]-0.291*RGB[1]+0.439*RGB[2]+128);
    YUV[2]=(unsigned char)floor(0.439*RGB[0]-0.368*RGB[1]-0.071*RGB[2]+128);
    for(int i=0;i<3;i++) RGB[i]=YUV[i];
    //now the RGB[3] actually stores the YUV value
}

void YUV2RGB(unsigned char(*&YUV)){
    unsigned char RGB[3];
    int a=(int)floor(1.164*(YUV[0]-16)+1.596*(YUV[2]-128));
    a= (a<0 || a>255)?255*(a>0):a;
    RGB[0]=(unsigned char)a;
    int b=(int)floor(1.164*(YUV[0]-16)-0.813*(YUV[2]-128)-0.391*(YUV[1]-128));
    b= (b<0 || b>255)?255*(b>0):b;
    RGB[1]=(unsigned char)b;
    int c=(int)floor(1.164*(YUV[0]-16)+2.018*(YUV[1]-128));
    c= (c<0 || c>255)?255*(c>0):c;
    RGB[2]=(unsigned char)c;
    for(int i=0;i<3;i++) YUV[i]=RGB[i];
    //now stores the RGB values
}

int main(int argc, char *argv[]){
    //FILE *file;
//    FILE *file1;
    int BytesPerPixel = 3;
    int width = 600;
    int height = 400;
//    unsigned char Imagedata1[height][width][BytesPerPixel];//the size of House.raw
//
//    // Read image (filename specified by first argument) into image data matrix
//    if (!(file1 = fopen(argv[1], "rb"))) {
//        cout << "Cannot open file: " << argv[1] << endl;
//        exit(1);
//    }
//    fread(Imagedata1, sizeof(unsigned char), width * height * BytesPerPixel, file1);
//    fclose(file1);


    ifstream file;
    // Allocate image data array
    file.open(argv[1],ios::in | ios::binary );
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



////////////////////////////////////
    //TODO: three steps
    priority_queue<pixel,vector<pixel>,pixelCmp> mypq;
    //1.RGB 2 YUV
    for(i=0; i<height; i++) {
        for(j=0; j<width; j++) {
            RGB2YUV(Imagedata[i][j]);
            pixel temp;
            temp.position=make_pair(i,j);
            temp.intensity=Imagedata[i][j][0];//push in Y value
            mypq.push(temp);
        }
    }


//    for(i=0;i<255;i++) cout<<data[i]<<endl;
    //2. HE1

    int buckets[256];

    for(i=0;i<256;i++){
        buckets[i]=(int)(floor(width*height/256.0*(i+1))-floor(width*height/256.0*i));
    }
    int currBuck=0;
    //while(!mypq.empty()){
    for(i=0;i<width*height;i++){
        pixel temp=mypq.top();
        mypq.pop();
        Imagedata[temp.position.first][temp.position.second][0]=(unsigned char)currBuck;
        buckets[currBuck]--;
        if(buckets[currBuck]==0)currBuck++;
        cnt++;
    }
    ofstream fileout;
    fileout.open(argv[2],ios::binary);
    for(i=0; i<height; i++) {
        for(j=0; j<width; j++) {
            YUV2RGB(Imagedata[i][j]);
            //3.YUV 2 RGB
            for (k = 0; k < BytesPerPixel; k++) {
                fileout<<noskipws<<Imagedata[i][j][k];
            }
        }
    }
    fileout.close();


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
