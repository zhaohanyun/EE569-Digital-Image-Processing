#include <iostream>
#include <vector>
#include "fileIO.h"
#include <algorithm>
#include <math.h>
#include <typeinfo>
#include <opencv2/core.hpp>

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
    if(filters.size()!=25){
        cout<<"wrong Law filters generation"<<endl;
        exit(-1);
    }
    return filters;
}

void deletefilters(vector<int**> filters){
    int i,j,k;
    for(i=0;i<25;i++){
        for(j=0;j<5;j++){
            delete(filters[i][j]);
        }
    }
    for(i=0;i<25;i++){
        delete(filters[i]);
    }
}

vector<double> filterResponse(unsigned char***img, vector<int**> filters, int BytesPerPixel=1, int width=128, int height=128){
    int i,j,k,f;
    vector<double> featureV(25);
    for(f=0;f<25;f++) {
        double totalEnergy=0;

//        if(f==0){
//            for (i = 0; i < height; i++) {
//                for (j = 0; j < width; j++) {
//                    for (k = 0; k < BytesPerPixel; k++) {
//                        int m, n;
//                        double temp = 0;
//                        for (m = -2; m < 3; m++) {
//                            for (n = -2; n < 3; n++) {
//                                //cout<<(int)img[abs(i+m)>=height?abs(i-m):abs(i+m)][abs(j+n)>=width?abs(j-n):abs(j+n)][k]<<endl;
//                                L5L5sum += filters[f][m + 2][n + 2] *
//                                        img[abs(i + m) >= height ? abs(i - m) : abs(i + m)][abs(j + n) >= width ? abs(
//                                                j - n) : abs(j + n)][k] / 255;//normalize
//                            }
//                        }
//                    }
//                }
//            }
//        }
        for (i = 0; i < height; i++) {
            for (j = 0; j < width; j++) {
                for (k = 0; k < BytesPerPixel; k++) {
                    int m, n;
                    double temp = 0;
                    double L5L5sum=0;
                    if(f==0){
                        for (m = -2; m < 3; m++) {
                            for (n = -2; n < 3; n++) {
                                //cout<<(int)img[abs(i+m)>=height?abs(i-m):abs(i+m)][abs(j+n)>=width?abs(j-n):abs(j+n)][k]<<endl;
                                L5L5sum += img[abs(i + m) >= height ? abs(i - m) : abs(i + m)][abs(j + n) >= width ? abs(
                                                j - n) : abs(j + n)][k] / 255.0;//normalize

                            }
                        }
                    }
                    for (m = -2; m < 3; m++) {
                        for (n = -2; n < 3; n++) {
                            //cout<<(int)img[abs(i+m)>=height?abs(i-m):abs(i+m)][abs(j+n)>=width?abs(j-n):abs(j+n)][k]<<endl;
                            if(f==0) {
                                temp += (double)filters[f][m + 2][n + 2] *
                                        (img[abs(i + m) >= height ? abs(i - m) : abs(i + m)][abs(j + n) >= width ? abs(
                                                j - n) : abs(j + n)][k]/ 255.0-L5L5sum/25.0);//normalize
                            }
                            else {
                                temp += (double)filters[f][m + 2][n + 2] *
                                        img[abs(i + m) >= height ? abs(i - m) : abs(i + m)][abs(j + n) >= width ? abs(
                                                j - n) : abs(j + n)][k] / 255.0;//normalize
                            }

                        }
                    }

                    totalEnergy += pow(temp, 2);
                }
            }
        }
        featureV[f] = totalEnergy / (height * width);

    }
    return featureV;
}

vector<vector<double>> allFilterResponse(vector<unsigned char***> imgs,vector<int**> filters){
    vector<vector<double>> featureVectors;
    featureVectors.reserve(imgs.size());
    for(auto& it : imgs){
        featureVectors.push_back(filterResponse(it,filters));
    }
//    int i;
//    for(i =0;i<imgs.size();i++){
//        cout<< typeid(imgs[i]).name()<<endl;
//        featureVectors.push_back(filterResponse(imgs[i],filters));
//
//    }
    return featureVectors;
}

void discriminantPower(vector<vector<double>> FV){
    //FV is 36*25, which has 25 dim of features, each feature has 4 class and 9 observations
    vector<double> DPV;
    int i,j,k,d;
    for(d=0;d<25;d++){//the dth dim
        double overallAverage=0;
        for(k=0;k<36;k++){
            overallAverage+=FV[k][d]/36.0;
        }

        //j=9  i=4
        double class_i_average[4]={0,0,0,0};
        for(i=0;i<4;i++){
            //calculate the average with in class i
            for(j=0;j<9;j++){
                class_i_average[i]+=FV[i*9+j][d]/9.0;
            }
        }

        double intra=0;
        double inter=0;
        for(i=0;i<4;i++){
            for(j=0;j<9;j++){
                intra+=pow(FV[i*9+j][d]-class_i_average[i],2);
                inter+=pow(class_i_average[i]-overallAverage,2);
            }
        }
        double DP=intra/inter;
        DPV.push_back(DP);
        cout<<DP<<", ";
    }

    vector<double>::iterator max=max_element(DPV.begin(),DPV.end());
    vector<double>::iterator min=min_element(DPV.begin(),DPV.end());
    cout<<"strongest: "<<distance(DPV.begin(),max)<<endl;
    cout<<"weakest: "<<distance(DPV.begin(),min)<<endl;
}

vector<unsigned char***> loadTrain(){
    string folderPath="images/train/";
    string texClass[4]={"blanket","brick","grass","stones"};
    vector<unsigned char***> imgs;
    int width=128;
    int height=128;
    int BytesPerPixel=1;
    int i,j,k;
    for(i=0;i<4;i++){//four classes
        for(j=0;j<9;j++){//each class has 9 sources
            string filePath=folderPath+texClass[i]+'_'+to_string(j+1)+".raw";
            unsigned char***img=AllocateMem<unsigned char>(BytesPerPixel,width,height);
            LoadImage(img,filePath,BytesPerPixel,width,height);
            imgs.push_back(img);
        }
    }
    return imgs;
}

vector<unsigned char***> loadTest(){
    string folderPath="images/test/";
    vector<unsigned char***> imgs;
    int width=128;
    int height=128;
    int BytesPerPixel=1;
    int i,j,k;
    for(i=0;i<12;i++){
        string filePath=folderPath+to_string(i+1)+".raw";
        unsigned char***img=AllocateMem<unsigned char>(BytesPerPixel,width,height);
        LoadImage(img,filePath,BytesPerPixel,width,height);
        imgs.push_back(img);
    }
    return imgs;
}

void freeTrain(vector<unsigned char***> imgs){
    int width=128;
    int height=128;
    int BytesPerPixel=1;
    for(auto& it: imgs ){
        FreeImage<unsigned char>(it,BytesPerPixel,width,height);
    }
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

//
//int main() {
//    //**************train
//    vector<int**>filters=genLawFilters();
//    vector<unsigned char***> imgs=loadTrain();
//    vector<vector<double>> featureVectors=allFilterResponse(imgs,filters);//this is the matrix
//    discriminantPower(featureVectors);
//    Mat M=vector2Mat(featureVectors);
//    Mat eigenvectors=myPCA(M);
//
//    //*****************test
//    vector<unsigned char***> testImgs=loadTest();
//    vector<vector<double>> testFV=allFilterResponse(testImgs,filters);
//    Mat testM=vector2Mat(testFV);
//    //cout<<testM<<endl;
//    Mat fuck=eigenvectors*testM.t();
//    //cout<<fuck.t()<<endl;
//
//    deletefilters(filters);
//    freeTrain(imgs);
//    cout<<"success"<<endl;
//    return 0;
//}
//
