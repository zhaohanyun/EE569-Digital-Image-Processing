//
// Created by Administrator on 2022/3/10.
//

#include <iostream>
#include "fileIO.h"
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>

void binarize(unsigned char***Imagedata,  int width, int height,int BytesPerPixel=1){
    int i,j;
    vector<unsigned char> list;
    for(i=0;i<height;i++){
        for(j=0;j<width;j++){
            list.push_back(Imagedata[i][j][0]);
        }
    }
    unsigned char max=*max_element(list.begin(),list.end());
    for(i=0;i<height;i++){
        for(j=0;j<width;j++){
            if(Imagedata[i][j][0]<max/2)Imagedata[i][j][0]=0;
            else Imagedata[i][j][0]=255;
        }
    }
}

unsigned char calculateNeighbour(unsigned char***Img,int i, int j,int k){
    //REQUIRE: should not be boundary points
    //cout<<(int)Img[i-1][j-1][k]<<endl;
    return (Img[i-1][j-1][k]>0)+(Img[i-1][j][k]>0)*2+(Img[i-1][j+1][k]>0)*4+
            (Img[i][j-1][k]>0)*8+(Img[i][j+1][k]>0)*16+
            (Img[i+1][j-1][k]>0)*32+(Img[i+1][j][k]>0)*64+(Img[i+1][j+1][k]>0)*128;
}
void thinning(unsigned char***Imagedata,  int width, int height){
    int i,j,k;
    int cnt=0;
    bool update= true;//record if any update happen in one iteration

    unsigned char hitbox;
    while(update){
        k=0;
        update=false;
        for(i=1;i<height-1;i++){
            for(j=1;j<width-1;j++){
                hitbox=calculateNeighbour(Imagedata,i,j,k);
                if(Imagedata[i][j][k]==255) {
//                    if (hitbox>0)
//                        cout<<(int)hitbox<<endl;
                    if (hitbox == 18 || hitbox == 10 || hitbox == 72 || hitbox == 80 || //TK
                        hitbox == 148 || hitbox == 7 || hitbox == 41 || hitbox == 224 ||//STK
                        hitbox == 19 || hitbox == 146 || hitbox == 14 || hitbox == 84 ||//ST
                        hitbox == 22 || hitbox == 11 || hitbox == 104 || hitbox == 208 ||//ST
                        hitbox == 147 || hitbox == 46 ||//ST
                        hitbox == 23 || hitbox == 150 || hitbox == 15 || hitbox == 43 || hitbox == 105 ||
                        hitbox == 232 || hitbox == 240 || hitbox == 21 || //STK
                        hitbox == 151 || hitbox == 47 || hitbox == 233 || hitbox == 244 ||//STK
                        hitbox == 214 || hitbox == 31 || hitbox == 107 || hitbox == 248 ||//STK
                        hitbox == 215 || hitbox == 246 || hitbox == 63 || hitbox == 159 || hitbox == 121 ||
                        hitbox == 235 || hitbox == 249 || hitbox == 252 || //STK
                        hitbox == 247 || hitbox == 191 || hitbox == 239 || hitbox == 253)//STK
                        //hitbox==254 ||hitbox==127 || hitbox==251 ||hitbox==223
                        Imagedata[i][j][1] = 1;
                    else  Imagedata[i][j][1]=0;
                }
                else  Imagedata[i][j][1]=0;
            }
        }

        k=1; //M matrix
        for(i=1;i<height-1;i++){
            for(j=1;j<width-1;j++){
                hitbox=calculateNeighbour(Imagedata,i,j,k);
                if (Imagedata[i][j][k]==1) {
                    //TODO
                    if(!(hitbox == 4 || hitbox == 2 || hitbox == 64 || hitbox == 16 ||
                       hitbox == 20 || hitbox == 5 || hitbox == 3 || hitbox == 9 ||
                       hitbox == 40 || hitbox == 96 || hitbox == 192 || hitbox == 144 ||
                       hitbox == 14 || hitbox == 19 || hitbox == 146 || hitbox == 84 ||
                       hitbox == 38 || hitbox == 137 ||
                       hitbox == 44 || hitbox == 193 || hitbox == 52 || hitbox == 131 || hitbox == 100 ||
                       hitbox == 145 || hitbox == 255 || hitbox == 59 ||
                       hitbox == 158 || hitbox == 220 || hitbox == 121 || hitbox == 79 ||
                       hitbox == 234 || hitbox == 242 || hitbox == 87 || hitbox == 179 ||
                       hitbox == 174 || hitbox == 205 || hitbox == 117 || hitbox == 38 || hitbox == 52 ||
                       hitbox == 54 || hitbox == 131 || hitbox == 137 ||
                       hitbox == 139 || hitbox == 44 || hitbox == 100 || hitbox == 108 ||
                       hitbox == 145 || hitbox == 193 || hitbox == 209 || hitbox == 11 ||
                       hitbox == 26 || hitbox == 59 || hitbox == 26 || hitbox == 158 ||
                       hitbox == 88 || hitbox == 220 || hitbox == 24 || hitbox == 57 ||
                       hitbox ==37 || hitbox==69 || hitbox==133 || hitbox==101 || hitbox==165 || hitbox==197 || hitbox==229 ||
                       hitbox ==49 || hitbox ==161 || hitbox==53 || hitbox==165 || hitbox==177 || hitbox==181 ||
                       hitbox ==161 || hitbox==162 || hitbox==164 || hitbox==165 || hitbox==163 || hitbox==166 || hitbox==167 ||
                       hitbox==133 || hitbox==140 || hitbox==164 || hitbox==141 || hitbox==173 ||
                       hitbox==223 || hitbox==191 || hitbox==127 || hitbox==159 || hitbox==95 || hitbox==63 ||
                       hitbox==251 || hitbox==239 || hitbox==235 || hitbox==123 ||hitbox==111 ||
                       hitbox==254 || hitbox==253 || hitbox==252 || hitbox==251 || hitbox==250 || hitbox==249 ||
                       hitbox==247 || hitbox==223 || hitbox==246 || hitbox==222 || hitbox==215 ||
                       hitbox==50 || hitbox==138 || hitbox==76|| hitbox==81 ||
                       hitbox==15 || hitbox==27 || hitbox==139 ||hitbox==75 ||hitbox==43 ||
                       hitbox==31 || hitbox==63 || hitbox==47 || hitbox==107 ||hitbox==111 || hitbox==123||
                       hitbox==27 || hitbox==58 || hitbox==30 || hitbox==154 ||
                       hitbox==114 ||hitbox==60 || hitbox==184 ||hitbox==57 ||hitbox==60 ||
                       hitbox==75 || hitbox==78 || hitbox==106 || hitbox==202 ||
                       hitbox==210 || hitbox==83 ||hitbox==86 )
                       //hitbox==22 || hitbox==208 ||hitbox==104
                       ) {
                        //what a fucking stupid problem
                        Imagedata[i][j][0] = 0;
                        update=true;
                    }
                }
            }
        }
        cnt++;
        if(cnt==20){
            OutputImage(Imagedata,"Output/thinspringInter.raw",1,width,height);
        }

    }
    cout<<cnt<<endl;

}

int main(int argc, char*argv[]) {
    int BytesPerPixel = 1;
    int width = stol(argv[3]);
    int height = stol(argv[3]);//a square image
    int i,j,k;
    string PathInput=argv[1];
    string PathOutput=argv[2];

    unsigned char***ImageData=AllocateMem<unsigned char>(3,width,height);
    unsigned char***ImageOutput=AllocateMem<unsigned char>(BytesPerPixel,width,height);
    LoadImage(ImageData,PathInput,BytesPerPixel,width,height);

    binarize(ImageData,width,height);
    thinning(ImageData,width,height);
    OutputImage(ImageData,PathOutput,BytesPerPixel,width,height);

    FreeImage<unsigned char>(ImageData,3,width,height);
    FreeImage<unsigned char>(ImageOutput,BytesPerPixel,width,height);
    return 0;
}
