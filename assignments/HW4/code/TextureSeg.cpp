#include <iostream>
#include <vector>
#include "fileIO.h"
#include <algorithm>
#include <math.h>
#include <typeinfo>
#include <opencv2/core.hpp>
#include <fstream>
using namespace std;
using namespace cv;

int kernel[5][5]={
        {1,4,6,4,1},//Level
        {-1,-2,0,2,1}, //Edge
        {-1,0,2,0,-1}, //Spot
        {-1,2,0,-2,1}, //Wave
        {1,-4,6,-4,1}  //Ripple
};

vector<int**> genLawFilters(){
    int i,j,k;
    vector<int**> filters;
    for(i=0;i<5;i++){
        for(j=0;j<5;j++){
            if(i==0 && j==0) continue;
            int** temp=new int*[5];
            for(k=0;k<5;k++) {
                temp[k] = new int[5];
                temp[k][0]=kernel[i][k] * kernel[j][0];
                temp[k][1]=kernel[i][k] * kernel[j][1];
                temp[k][2]=kernel[i][k] * kernel[j][2];
                temp[k][3]=kernel[i][k] * kernel[j][3];
                temp[k][4]=kernel[i][k] * kernel[j][4];
            }
            //push
            filters.push_back(temp);
        }
    }
    if(filters.size()!=24){
        cout<<"wrong Law filters generation"<<endl;
        exit(-1);
    }
    return filters;
}

void deletefilters(vector<int**> filters){
    int i,j,k;
    for(i=0;i<24;i++){
        for(j=0;j<5;j++){
            delete(filters[i][j]);
        }
    }
    for(i=0;i<24;i++){
        delete(filters[i]);
    }
}

vector<vector<double>> filterResponse(unsigned char***img, vector<int**> filters, int BytesPerPixel=1, int width=128, int height=128){
    int i,j,k,f,p,q;
    vector<vector<double>> FVforallPixels(width*height);
    int windowSize=35;
    ofstream file;
    file.open("Filter Response35.txt",ios::out);

    for (p = 0; p < height; p++) {
        for (q = 0; q < width; q++) {
            vector<double> featureV(24);
            for (f = 0; f < 24; f++) {
                double totalEnergy = 0;
                for (i = p-(windowSize-1)/2; i < p+(windowSize)/2; i++) {
                    for (j = q-(windowSize-1)/2; j <q+(windowSize)/2; j++) {
                        for (k = 0; k < BytesPerPixel; k++) {
                            int m, n;
                            double temp = 0;
                            for (m = -2; m < 3; m++) {
                                for (n = -2; n < 3; n++) {
                                    //cout<<(int)img[abs(i+m)>=height?abs(i-m):abs(i+m)][abs(j+n)>=width?abs(j-n):abs(j+n)][k]<<endl;
                                    temp += (double) filters[f][m + 2][n + 2] *
                                            img[abs(i + m) >= height ? abs(2*height- i - m-1) : abs(i + m)][abs(j + n) >= width
                                                                                                ? abs(
                                                            2*width-j - n-1) : abs(j + n)][k] / 255.0;//normalize
                                }
                            }

                            totalEnergy += pow(temp, 2);
                        }
                    }
                }
                //featureV[f] = totalEnergy /pow(windowSize,2);
                file<<totalEnergy /pow(windowSize,2)<<' ';
            }
            //FVforallPixels.push_back(featureV);
            file<<endl;
        }
        cout<<p<<endl;
    }
    file.close();
    return FVforallPixels;
}



Mat vector2Mat(vector<vector<double>> V){
    int row=V.size(); //if (row!=36) cout<<"wrong rows size"<<endl;
    int col=V[0].size(); //if(col!=25) cout<<"wrong col size"<<endl;
    Mat M=Mat(row,col,CV_64FC1);
    int i,j;
    for(i=0;i<row;i++){
        for(j=0;j<col;j++){
            M.at<double>(i,j)=V[i][j];
        }
    }
    return M;
}

Mat myPCA(Mat M){
    //M: 36:25, we need to compress it to 36*3 and plot
    cv::PCA pca(M,cv::Mat(),PCA::DATA_AS_ROW ,3);
    //cout<<pca.eigenvectors<<endl;
    Mat final=pca.eigenvectors*M.t();
    cout<<final<<endl;
    return pca.eigenvectors;
}

int main() {
    int width=512;
    int height=512;
    int BytesPerPixel=1;
    vector<int**>filters=genLawFilters();
    unsigned char***img=AllocateMem<unsigned char>(BytesPerPixel,width,height);
    unsigned char***imgOut=AllocateMem<unsigned char>(3,width,height);
    LoadImage(img,"images/Mosaic.raw",BytesPerPixel,width,height);
    vector<vector<double>> featureVectors=filterResponse(img,filters,BytesPerPixel,width,height);

    cout<<featureVectors.size()<<endl;
    cout<<featureVectors[0].size()<<endl;

    Mat M=vector2Mat(featureVectors);//should be 512*25
    FreeImage(img,BytesPerPixel,width,height);
    FreeImage(imgOut,3,width,height);
}


