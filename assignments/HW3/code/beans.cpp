//
// Created by Administrator on 2022/3/10.
//
#include <iostream>
#include "fileIO.h"
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <queue>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

void binarize(unsigned char***Imagedata,  int width, int height){
    int i,j;
    for(i=0;i<height;i++){
        for(j=0;j<width;j++){
            Imagedata[i][j][0]=(unsigned char)((Imagedata[i][j][0]+Imagedata[i][j][1]+Imagedata[i][j][2])/3);
        }
    }

    for(i=0;i<height;i++){
        for(j=0;j<width;j++){
            if(Imagedata[i][j][0]<240)Imagedata[i][j][0]=0;
            else Imagedata[i][j][0]=255;
        }
    }
}

void defectDetection(unsigned char***img,  int width, int height,int BytesPerPixel=1){

    bool searched[height][width];
    vector<int> islandsSize;

    int i,j;
    for(i=0;i<height;i++){
        for(j=0;j<width;j++){
            searched[i][j]= false;
        }
    }

    queue<pair<int,int>> q;
    int cnt;//count the size of each island

    for(j=0;j<width;j++){//from left to right instead of up to down. To facilitate counting beans
        for(i=0;i<height;i++){
            if(!searched[i][j]){
                if(img[i][j][0]==0) {
                    q.push(make_pair(i, j));
                    cnt=1;
                    while(!q.empty()){
                        int m=q.front().first;
                        int n=q.front().second;
                        q.pop();
                        if(m-1>=0 && !searched[m-1][n] && img[m-1][n][0]==0){//unserached connected black
                            q.push(make_pair(m-1,n));
                            searched[m-1][n]=true;
                            cnt++;
                        }
                        if(n-1>=0 && !searched[m][n-1] && img[m][n-1][0]==0){//unserached connected black
                            q.push(make_pair(m,n-1));
                            searched[m][n-1]=true;
                            cnt++;
                        }
                        if(m+1<height && !searched[m+1][n] && img[m+1][n][0]==0){//unserached connected black
                            q.push(make_pair(m+1,n));
                            searched[m+1][n]=true;
                            cnt++;
                        }
                        if(n+1<width && !searched[m][n+1] && img[m][n+1][0]==0){//unserached connected black
                            q.push(make_pair(m,n+1));
                            searched[m][n+1]=true;
                            cnt++;
                        }
                    }
                    islandsSize.push_back(cnt);
                }
                else{
                    searched[i][j]=true;
                }
            }
        }
    }

    for(auto i : islandsSize){
        cout<<i<<endl;
    }
    cout<<islandsSize.size()<<endl;
}

//void toGrey(unsigned char***src, unsigned char***dst, int width=494,int height=82){
//    int i,j,k;
//    for(i=0;i<height;i++){
//        for(j=0;j<width;j++){
//            dst[i][j][0]=(unsigned char)((src[i][j][0]+src[i][j][1]+src[i][j][2])/3);
//        }
//    }
//}

void closing(unsigned char***img,  int width, int height,int BytesPerPixel=1){
    Mat imgMat=Mat(height,width,CV_8UC1);
    int i,j;
    for(i=0;i<height;i++){
        for(j=0;j<width;j++){
            imgMat.at<unsigned char>(i,j)=img[i][j][0];
        }
    }
    int morph_size=2;
    Mat element = getStructuringElement(
            MORPH_RECT,
            Size(2 * morph_size + 1,
                 2 * morph_size + 1),
            Point(morph_size, morph_size));
    Mat output;
    morphologyEx(imgMat, output,
                 MORPH_CLOSE, element,
                 Point(-1, -1), 2);
//    imshow("closing",output);
//    waitKey(0);
    for(i=0;i<height;i++){
        for(j=0;j<width;j++){
            img[i][j][0]=output.at<unsigned char>(i,j);
        }
    }
}

int main(){
    int BytesPerPixel = 3;
    int width = 494;
    int height = 82;
    int i,j,k;
    string PathInput="raw_images/beans.raw";
    //string PathOutput=argv[2];

    unsigned char***ImageData=AllocateMem<unsigned char>(BytesPerPixel,width,height);
    unsigned char***ImageGray=AllocateMem<unsigned char>(1,width,height);
    unsigned char***ImageOutput=AllocateMem<unsigned char>(BytesPerPixel,width,height);
    LoadImage(ImageData,PathInput,BytesPerPixel,width,height);
    binarize(ImageData,width,height);//now it still has three channel, the first one is gray, the other two are wasted

    //OutputImage(ImageData,"Output/beantest.raw",1,width,height);
    closing(ImageData,width,height);
    defectDetection(ImageData,width,height,BytesPerPixel);

    cout<<"finished"<<endl;
    FreeImage<unsigned char>(ImageData,BytesPerPixel,width,height);
    FreeImage<unsigned char>(ImageOutput,BytesPerPixel,width,height);
    FreeImage<unsigned char>(ImageGray,1,width,height);
    return 0;
}