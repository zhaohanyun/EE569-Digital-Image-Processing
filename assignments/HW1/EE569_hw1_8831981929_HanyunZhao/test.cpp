//
// Created by Administrator on 2022/1/12.
//

#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;
int main()

{
    // Define file pointer and variables
    FILE *file;
    int BytesPerPixel=1;
    //int Size = 256;
    int width=768;
    int height=512;

    // Allocate image data array
    unsigned char Imagedata[width][height][BytesPerPixel];//the size of House.raw

    // Read image (filename specified by first argument) into image data matrix
    if (!(file=fopen("shit.txt","rb"))) {
        cout << "Cannot open file: " << "shit.txt"<<endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), width*height*BytesPerPixel, file);
    fclose(file);

    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
    //TODO:my code
    FILE *file2;
    FILE *fileout;
    unsigned char ImageOri[width][height][3];
    unsigned char ImageOutput[width][height][3];
    int i=0;int j=0;
    cout<<"here"<<endl;
    if (!(file2=fopen("images/House_ori.raw","rb"))) {
        cout << "Cannot open file: " << "images/House_ori.raw" <<endl;
        exit(1);
    }

    fread(ImageOri, sizeof(unsigned char), width*height*3, file2);
    fclose(file2);

    for(i=0;i<width;i++){
        for(j=0;j<height;j++){
            if(i==0 || i==width-1 || j==0 || j==height-1){//edge or corner
                if((j - i) % 2 == 0) {//green pixel
                    ImageOutput[i][j][1] = Imagedata[i][j][0];
                    ImageOutput[i][j][0] = 0;
                    ImageOutput[i][j][2] = 0;
                }
                else if(i%2==0){//red pixel
                    ImageOutput[i][j][0] = Imagedata[i][j][0];
                    ImageOutput[i][j][1] = 0;
                    ImageOutput[i][j][2] = 0;
                }
                else{//blue pixel
                    ImageOutput[i][j][2] = Imagedata[i][j][0];
                    ImageOutput[i][j][0] = 0;
                    ImageOutput[i][j][1] = 0;
                }
            }
            else {
                if((j - i) % 2 == 0) {//green pixel
                    ImageOutput[i][j][1] = Imagedata[i][j][0];
                    if(i%2==0) {
                        ImageOutput[i][j][0] = ((Imagedata[i-1][j][0] + Imagedata[i+1][j][0]) / 2);
                        ImageOutput[i][j][2] = ((Imagedata[i][j-1][0] + Imagedata[i][j+1][0]) / 2);
                    }
                    else{
                        ImageOutput[i][j][0] = ((Imagedata[i][j-1][0] + Imagedata[i][j+1][0]) / 2);
                        ImageOutput[i][j][2] = ((Imagedata[i-1][j][0] + Imagedata[i+1][j][0]) / 2);
                    }
                }
                else if(i%2==1){//red pixel
                    ImageOutput[i][j][0] = Imagedata[i][j][0];
                    ImageOutput[i][j][1] = ((Imagedata[i-1][j][0]+Imagedata[i][j-1][0]+Imagedata[i][j+1][0]+Imagedata[i+1][j][0])/4);
                    ImageOutput[i][j][2] = ((Imagedata[i-1][j-1][0]+Imagedata[i+1][j-1][0]+Imagedata[i-1][j+1][0]+Imagedata[i+1][j+1][0])/4);
                }
                else{//blue pixel
                    ImageOutput[i][j][2] = Imagedata[i][j][0];
                    ImageOutput[i][j][1] = ((Imagedata[i-1][j][0]+Imagedata[i][j-1][0]+Imagedata[i][j+1][0]+Imagedata[i+1][j][0])/4);
                    ImageOutput[i][j][0] = ((Imagedata[i-1][j-1][0]+Imagedata[i+1][j-1][0]+Imagedata[i-1][j+1][0]+Imagedata[i+1][j+1][0])/4);
                }
            }
        }
    }
    cout<<(int)Imagedata[701][300][0]<<endl;
    cout<<(int)ImageOutput[701][300][0]<<" "<<(int)ImageOutput[701][300][1]<<" "<<(int)ImageOutput[701][300][2]<<endl;
    cout<<(int)ImageOri[701][300][0]<<" "<<(int)ImageOri[701][300][1]<<" "<<(int)ImageOri[701][300][2]<<endl;

    ////////////////////////////////////////////////////////////////////////////////////
    // Write image data (filename specified by second argument) from image data matrix

    if (!(fileout=fopen("output/House_output.raw","wb"))) {
        cout << "Cannot open file: " << "output/House_output.raw" << endl;
        exit(1);
    }
    fwrite(ImageOutput, sizeof(unsigned char), width*height*3, fileout);
    fclose(fileout);
    cout<<"finished"<<endl;
    return 0;
}
