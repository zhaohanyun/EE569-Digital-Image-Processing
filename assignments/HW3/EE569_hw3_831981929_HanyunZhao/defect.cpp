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

using namespace cv;

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
            if(Imagedata[i][j][0]<128)Imagedata[i][j][0]=0;
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

    vector<int>::iterator iter=islandsSize.begin();
    while(iter!=islandsSize.end()){
        if(*iter>50){
            islandsSize.erase(iter);
        }
        else iter++;
    }
    for(auto iter2:islandsSize) cout<<iter2<<endl;
    cout<<islandsSize.size()<<endl;
}

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
    int BytesPerPixel = 1;
    int width = 550;
    int height = 691;
    int i,j,k;
    string PathInput="raw_images/deer.raw";
    //string PathOutput=argv[2];

    unsigned char***ImageData=AllocateMem<unsigned char>(BytesPerPixel,width,height);
    unsigned char***ImageOutput=AllocateMem<unsigned char>(BytesPerPixel,width,height);
    LoadImage(ImageData,PathInput,BytesPerPixel,width,height);
    binarize(ImageData,width,height,BytesPerPixel);
    defectDetection(ImageData,width,height,BytesPerPixel);

    closing(ImageData,width,height,BytesPerPixel);
    OutputImage(ImageData,"Output/repairedDeer.raw",BytesPerPixel,width,height);
    cout<<"finished"<<endl;
    FreeImage<unsigned char>(ImageData,BytesPerPixel,width,height);
    FreeImage<unsigned char>(ImageOutput,BytesPerPixel,width,height);
    return 0;
}