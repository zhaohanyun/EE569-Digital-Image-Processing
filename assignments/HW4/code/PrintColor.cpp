#include <fstream>
#include <iostream>
#include "fileIO.h"
#include <stdio.h>
using namespace std;

int main(){
    int width=512;
    int height=512;
    int BytesPerPixel=3;
    unsigned char***imgOut=AllocateMem<unsigned char>(BytesPerPixel,width,height);
    int i,j,k;
    ifstream file;
    file.open("color35.txt",ios::in);
    if(!file.is_open()) cout<<"fail to open file"<<endl;

    for(i=0;i<height;i++){
        for(j=0;j<width;j++){
            char buf;
            file>>buf;
            if(buf=='0'){
                imgOut[i][j][0]=107;
                imgOut[i][j][1]=143;
                imgOut[i][j][2]=159;
            }
            else if(buf=='1'){
                imgOut[i][j][0]=114;
                imgOut[i][j][1]=99;
                imgOut[i][j][2]=107;
            }
            else if(buf=='2'){
                imgOut[i][j][0]=175;
                imgOut[i][j][1]=128;
                imgOut[i][j][2]=74;
            }
            else if(buf=='3'){
                imgOut[i][j][0]=167;
                imgOut[i][j][1]=57;
                imgOut[i][j][2]=32;
            }
            else if(buf=='4'){
                imgOut[i][j][0]=144;
                imgOut[i][j][1]=147;
                imgOut[i][j][2]=104;
            }
            else if(buf=='5'){
                imgOut[i][j][0]=157;
                imgOut[i][j][1]=189;
                imgOut[i][j][2]=204;
            }
        }
    }
    OutputImage(imgOut,"Output/TexSeg35.raw",BytesPerPixel,width,height);
    FreeImage(imgOut,BytesPerPixel,width,height);
}

