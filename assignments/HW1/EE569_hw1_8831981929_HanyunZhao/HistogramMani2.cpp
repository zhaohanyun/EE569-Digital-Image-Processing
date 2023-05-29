//
// Created by Administrator on 2022/1/23.
//

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cmath>
#include <queue>
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
    int BytesPerPixel = 1;
    int width = 256;
    int height = 256;

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
    //Todo: mycode 1.b.3
    //generate the histogram data (output to a file, 256 lines, each line stores one intensity value)
    int i, j;
    priority_queue<pixel,vector<pixel>,pixelCmp> mypq;

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            pixel temp;
            temp.position=make_pair(i,j);
            temp.intensity=Imagedata[i][j][0];
            mypq.push(temp);
        }
    }

     ////////////////////////////output to file for py plot
    int data[256]={0};
    for(i=0;i<height;i++){
        for(j=0;j<width;j++){
            data[Imagedata[i][j][0]]+=1;
        }
    }
    for(i=1;i<256;i++) {
        data[i]=data[i]+data[i-1];
    }//now data stores the cumulative value

    ofstream fileout;
    fileout.open("HatCumHistoOri.txt");

    for(i=0;i<256;i++){
        fileout<<data[i]<<endl;
    }
    fileout.close();
    for(i=0;i<256;i++){
        data[i]=0;
    }
    ///////////////////////////////

    unsigned char ImageOutput2[height][width][BytesPerPixel];

    int buckets[256]={256};
    for(i=0;i<256;i++){
        buckets[i]=256;
    }
    int currBuck=0;int cnt=0;
    while(!mypq.empty()){
        pixel temp=mypq.top();
        mypq.pop();
        ImageOutput2[temp.position.first][temp.position.second][0]=(unsigned char)currBuck;
        buckets[currBuck]--;data[currBuck]++;
        if(buckets[currBuck]==0)currBuck++;
        cnt++;
    }


    FILE *b3;
    if (!(b3=fopen("output/MethodBEnhanced.raw","wb"))) {
        cout << "Cannot open file: " << "output/MethodBEnhanced.raw" << endl;
        exit(1);
    }
    fwrite(ImageOutput2, sizeof(unsigned char), width*height, b3);
    fclose(b3);


    ////////////////////////////output to file for py plot

    for(i=1;i<256;i++) {
        data[i]=data[i]+data[i-1];
    }//now data stores the cumulative value

    fileout.open("HatCumHistoEnh.txt");

    for(i=0;i<256;i++){
        fileout<<data[i]<<endl;
    }
    fileout.close();
    ///////////////////////////////

    return 0;
}