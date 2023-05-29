//
// Created by Administrator on 2022/2/20.
//
#include <iostream>
#include "fileIO.h"
#include <cmath>
#include <string>

void RGBCMY(unsigned char*** Imagedata,int BytesPerPixel=3,int width=500,int height=375){
    int i,j,k;
    for(i=0;i<height;i++){
        for(j=0;j<width;j++){
            for(k=0;k<BytesPerPixel;k++){
                Imagedata[i][j][k]=(unsigned char)(255-Imagedata[i][j][k]);
            }
        }
    }
}

string MBVQ(unsigned char C, unsigned char M, unsigned char Y){
    unsigned char R=(unsigned char)(255-C);
    unsigned char G=(unsigned char)(255-M);
    unsigned char B=(unsigned char)(255-Y);
    if(R+G>255){
        if(G+B>255){
            if((R+G+B)>510) return "CMYW";
            else return "MYGC";
        }
        else return"RGMY";
    }
    else{
        if(G + B <= 255){
            if(R + B + G <= 255) return "KRGB";
            else return "RGBM";
        }
        else return "CMGB";
    }
}

string getNearestVertex(string mbvq,double C,double M,double Y){
    double R=255-C;
    double G=255-M;
    double B=255-Y;
    string vertex="fuck";
    // No.1 for CMYW
    if (mbvq == "CMYW") {
        vertex = "white";
        if (B < 0.5)
            if (B <= R)
                if (B <= G)
                    vertex = "yellow";

        if (G < 0.5)
            if (G <= B)
                if (G <= R)
                    vertex = "magenta";

        if (R < 0.5)
            if (R <= B)
                if (R <= G)
                    vertex = "cyan";
    }


    // No.2 for MYGC
    if (mbvq == "MYGC") {
        vertex = "magenta";
        if (G >= B)
            if (R >= B)
                vertex = R >= 0.5 ? "yellow" : "green";


        if (G >= R)
            if (B >= R)
                vertex = B >= 0.5 ? "cyan" : "green";
    }

    // No.3 for RGMY
    if (mbvq == "RGMY") {
        if (B > 0.5) {
            if (R > 0.5)
                if (B >= G)
                    vertex = "magenta";
                else
                    vertex = "yellow";

            else {
                if (G > B + R)
                    vertex = "green";
                else
                    vertex = "magenta";
            }
        } else {
            if (R >= 0.5)
                if (G >= 0.5)
                    vertex = "yellow";
                else
                    vertex = "red";

            else if (R >= G)
                vertex = "red";
            else
                vertex = "green";
        }
    }

    // No.4 for KRGB
    if (mbvq == "KRGB") {
        vertex = "black";
        if (B > 0.5)
            if (B >= R)
                if (B >= G)
                    vertex = "blue";

        if (G > 0.5)
            if (G >= B)
                if (G >= R)
                    vertex = "green";

        if (R > 0.5)
            if (R >= B)
                if (R >= G)
                    vertex = "red";
    }

    // No.5 for RGBM
    if (mbvq == "RGBM") {
        vertex = "green";
        if (R > G)
            if (R >= B)
                vertex = B < 0.5 ? "red" : "magenta";


        if (B > G)
            if (B >= R)
                vertex = R < 0.5 ? "blue" : "magenta";
    }


    // No.6 for CMGB
    if (mbvq == "CMGB") {
        if (B > 0.5)
            if (R > 0.5)
                if (G >= R)
                    vertex = "cyan";
                else
                    vertex = "magenta";

            else if (G > 0.5)
                vertex = "cyan";
            else
                vertex = "blue";


        else if (R > 0.5)
            if (R - G + B >= 0.5)
                vertex = "magenta";
            else
                vertex = "green";

        else if (G >= B)
            vertex = "green";
        else
            vertex = "blue";
    }
    return vertex;
}

void parseVstring(const string &V_string, unsigned char*PixelOutput){
    if(V_string=="blue"){
        PixelOutput[0]=255;
        PixelOutput[1]=255;
        PixelOutput[2]=0;
    }
    else if(V_string=="green"){
        PixelOutput[0]=255;
        PixelOutput[1]=0;
        PixelOutput[2]=255;
    }
    else if(V_string=="magenta"){
        PixelOutput[0]=0;
        PixelOutput[1]=255;
        PixelOutput[2]=0;
    }
    else if(V_string=="cyan"){
        PixelOutput[0]=255;
        PixelOutput[1]=0;
        PixelOutput[2]=0;
    }
    else if(V_string=="red"){
        PixelOutput[0]=0;
        PixelOutput[1]=255;
        PixelOutput[2]=255;
    }
    else if(V_string=="black"){
        PixelOutput[0]=255;
        PixelOutput[1]=255;
        PixelOutput[2]=255;
    }
    else if(V_string=="yellow"){
        PixelOutput[0]=0;
        PixelOutput[1]=0;
        PixelOutput[2]=255;
    }
    else if(V_string=="white"){
        PixelOutput[0]=0;
        PixelOutput[1]=0;
        PixelOutput[2]=0;
    }
    else exit(-1);

}
void MBVQED(unsigned char***Imagedata, unsigned char*** ImageOutput,int BytesPerPixel=3,int width=500, int height=375){
    int i,j,k;
    double***Error=AllocateMem<double>(BytesPerPixel,width,height);
    for(i=1;i<height-1;i++){
        for(j=1;j<width-1;j++){
            string mbvq=MBVQ(Imagedata[i][j][0],Imagedata[i][j][1],Imagedata[i][j][2]);
            double C_new=Imagedata[i][j][0]+Error[i][j][0];
            double M_new=Imagedata[i][j][1]+Error[i][j][1];
            double Y_new=Imagedata[i][j][2]+Error[i][j][2];
            double newCMY[3]={C_new,M_new,Y_new};
            string V_string=getNearestVertex(mbvq,C_new,M_new,Y_new);
            parseVstring(V_string,ImageOutput[i][j]);
            for(k=0;k<BytesPerPixel;k++){
                Error[i][j + 1][k] -= 7 / 16.0 * (ImageOutput[i][j][k]-newCMY[k]);
                Error[i + 1][j - 1][k] -= 3 / 16.0 * (ImageOutput[i][j][k]-newCMY[k]);
                Error[i + 1][j][k] -= 5 / 16.0 * (ImageOutput[i][j][k]-newCMY[k]);
                Error[i + 1][j + 1][k] -= 1 / 16.0 * (ImageOutput[i][j][k]-newCMY[k]);
            }
        }
    }
    FreeImage(Error,BytesPerPixel,width,height);
}
int main(int argc, char*argv[]) {
    int BytesPerPixel = 3;
    int width = 500;
    int height = 375;
    int i, j, k;

    unsigned char***ImageData=AllocateMem<unsigned char>(BytesPerPixel,width,height);//original image

    unsigned char***ImageOutput=AllocateMem<unsigned char>(BytesPerPixel,width,height);

    string PathInput = "HW2_images/Bird.raw";
    string PathOutput="Output/MBVQ.raw";
    LoadImage(ImageData,PathInput,BytesPerPixel,width,height);
    // cout<<(int)ImageData[20][350][0]<<" "<<(int)ImageData[20][350][1]<<" "<<(int)ImageData[20][350][2]<<l;
    RGBCMY(ImageData);
    MBVQED(ImageData,ImageOutput,BytesPerPixel);
    RGBCMY(ImageOutput);
    OutputImage(ImageOutput,PathOutput,BytesPerPixel,width,height);


    FreeImage<unsigned char>(ImageData,BytesPerPixel,width,height);
    FreeImage<unsigned char>(ImageOutput,BytesPerPixel,width,height);
    cout<<"here"<<endl;
    return 0;
}
