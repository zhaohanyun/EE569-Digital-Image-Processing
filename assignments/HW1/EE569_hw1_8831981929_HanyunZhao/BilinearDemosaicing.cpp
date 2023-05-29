// EE569 Homework Assignment #1
///Created on: Jan 11, 2022
// Name: Hanyun Zhao
// ID: 8831981929
// email: hanyunzh@usc.edu
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;
int main(int argc, char *argv[])

{
    // Define file pointer and variables
    FILE *file;
    int BytesPerPixel;
    //int Size = 256;
    int width=768;
    int height=512;

    // Check for proper syntax
    if (argc < 3){
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;
        return 0;
    }

    // Check if image is grayscale or color
    if (argc < 4){
        BytesPerPixel = 1; // default is grey image
    }
    else {
        BytesPerPixel = atoi(argv[3]);
        // Check if size is specified
//        if (argc >= 5){
//            Size = atoi(argv[4]);
//        }
    }

    // Allocate image data array
    unsigned char Imagedata[height][width][BytesPerPixel];//the size of House.raw

    // Read image (filename specified by first argument) into image data matrix
    if (!(file=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), width*height*BytesPerPixel, file);
    fclose(file);

    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
    //TODO:my code
    FILE *fileout;
    //unsigned char ImageOri[width][height][3];//file2
    unsigned char ImageOutput[height][width][3];//fileout

    /*
    ////////////initialize House_Ori.raw container
    unsigned char ***ImageOri;
    ImageOri=new unsigned char **[768];
    int i,j,k;
    for(i=0; i<768; i++)
    {
        ImageOri[i]=new unsigned char *[512];
        for(j=0; j<512; j++)
            ImageOri[i][j]=new unsigned char[3];
    }
    ////////////////
    */
    int i,j;
    for(i=0;i<height;i++){
        for(j=0;j<width;j++){
            if(i==0 || i==height-1 || j==0 || j==width-1){//edge or corner
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
                        ImageOutput[i][j][2] = ((Imagedata[i-1][j][0] + Imagedata[i+1][j][0]) / 2);
                        ImageOutput[i][j][0] = ((Imagedata[i][j-1][0] + Imagedata[i][j+1][0]) / 2);
                    }
                    else{
                        ImageOutput[i][j][2] = ((Imagedata[i][j-1][0] + Imagedata[i][j+1][0]) / 2);
                        ImageOutput[i][j][0] = ((Imagedata[i-1][j][0] + Imagedata[i+1][j][0]) / 2);
                    }
                }
                else if(i%2==0){//red pixel
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
//    cout<<(int)Imagedata[1][2][0]<<endl;
//    //cout<<(int)ImageOutput[1][2][0]<<" "<<(int)ImageOutput[1][2][1]<<" "<<(int)ImageOutput[1][2][2]<<endl;
//    //cout<<(int)ImageOri[1][1][0]<<" "<<(int)ImageOri[1][1][1]<<" "<<(int)ImageOri[1][1][2]<<endl;
//    for(i=0;i<8;i++){
//        for(j=0;j<8;j++){
//            cout<<(int)Imagedata[i][j][0]<<" ";
//        }
//        cout<<endl;
//    }
    ////////////////////////////////////////////////////////////////////////////////////
    // Write image data (filename specified by second argument) from image data matrix

    if (!(fileout=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(ImageOutput, sizeof(unsigned char), width*height*3, fileout);
    fclose(fileout);

    /*
    //////////////////deleted House_Ori.raw container
    for(i=0; i<768; i++)
    {
        for(j=0; j<512; j++)
        {
            delete [] ImageOri[i][j];
        }
    }
    for(i=0; i<768; i++)
    {
        delete [] ImageOri[i];
    }
    delete [] ImageOri;
    ////////////////////////
    */

    return 0;
}

