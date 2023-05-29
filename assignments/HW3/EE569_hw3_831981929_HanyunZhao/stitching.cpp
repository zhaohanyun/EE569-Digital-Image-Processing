//
// Created by Administrator on 2022/3/9.
//
#include <iostream>
#include "fileIO.h"
#include <string>
#include <cmath>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/stitching.hpp"

using namespace std;
using namespace cv;

//Mat loadRaw(string pathString, int width=576, int height=432, int BytesPerPixel=3){
//    FILE *fp;
//    const char* path=pathString.c_str();
//    fp = fopen(path,"rb+");
//    char*data =(char*)malloc(width*height*BytesPerPixel* sizeof(char));
//    //fread(data, sizeof(float),width*height,fp);
//    fread(data,width*height*BytesPerPixel*sizeof(char),1,fp);
//    Mat image;
//    image.create(height,width,CV_8UC3);
//    memcpy(image.data,data,width*height*BytesPerPixel*sizeof(char));
//    return image;
//}

Mat loadRaw(string pathString, int width=576, int height=432, int BytesPerPixel=3){
    FILE *fp;
    const char* path=pathString.c_str();
    fp = fopen(path,"rb+");
    Mat image;
    image.create(Size(width,height),CV_8UC3);
    //char*data =(char*)malloc(width*height*BytesPerPixel* sizeof(char));
    //fread(data, sizeof(float),width*height,fp);
    fread(image.data,width*height*BytesPerPixel*sizeof(char),1,fp);
    return image;
}

Mat keypointDetector(Mat image1,Mat image2) {
    //https://cpp.hotexamples.com/zh/examples/-/BFMatcher/knnMatch/cpp-bfmatcher-knnmatch-method-examples.html
    //cv::SiftFeatureDetector detector;
    Ptr<SiftFeatureDetector> ptrDetector=SiftFeatureDetector::create();
    std::vector<cv::KeyPoint> keypoints1,keypoints2;
    ptrDetector->detect(image1, keypoints1);
    ptrDetector->detect(image2, keypoints2);
    cout<<keypoints1.size()<<endl;

    Mat descriptor1,descriptor2;
    Ptr<DescriptorExtractor> extractor=ORB::create();
//    extractor->compute(image1, keypoints1, descriptor1);
//    extractor->compute(image2, keypoints2, descriptor2);
    extractor->detectAndCompute(image1, noArray(),keypoints1, descriptor1);
    extractor->detectAndCompute(image2, noArray(),keypoints2, descriptor2);
    cout<<"here2"<<endl;

    BFMatcher matcher;
    std::vector<vector< DMatch >> matches;
    matcher.knnMatch(descriptor1,descriptor2,matches,2);
    cout<<matches.size()<<endl;
    cout<<"here3"<<endl;
    std::vector< DMatch > good_matches;
    int i;
    for(i=0;i<matches.size();i++){
        if(matches[i][0].distance<0.5*matches[i][1].distance){//adjust the ratio
            good_matches.push_back(matches[i][0]);
        }
    }
    cout<<good_matches.size()<<endl;

    Mat img_matches;
    drawMatches( image1, keypoints1, image2, keypoints2, good_matches, img_matches, Scalar::all(-1),
                 Scalar::all(-1), std::vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );
    //imshow("good matches",img_matches);
    //waitKey(0);

    std::vector<Point2f> left;
    std::vector<Point2f> middle;
    for(i=0;i<good_matches.size();i++){
        left.push_back(keypoints1[good_matches[i].queryIdx].pt);
        middle.push_back(keypoints2[good_matches[i].trainIdx].pt);
        cout<<keypoints1[good_matches[i].queryIdx].pt<<endl;
        cout<<keypoints2[good_matches[i].trainIdx].pt<<endl;
        cout<<endl;
    }

    Mat H = findHomography(left, middle,RANSAC);

    return H;
}

unsigned char colorMapping(unsigned char***SourceImage, Mat H,int j, int k, int channel,
                           int BytesPerPixel=3,  int width=576, int height=432){
    //EFFECT: give the position in the output wrapped image, return what vlue it should be
    //(j,k) output image
    //(x,y) output cart
    //(u,v) input cart
    //(p,q) input image

//    if(j<0 || j>height || k<0 || k>width){
//        cout<<"wrong output image coordinate"<<endl;
//        exit(-1);
//    }
    double x,y;
    x=k+0.5;
    y=height-j-0.5;

    x=k;
    y=j;

    double u=0,v=0;
    //TODO:
    //double w2=H.at<double>(2,0)*x+H.at<double>(2,1)*y+H.at<double>(2,2);
    Mat Hinv=H.inv();
    double w2=1/(Hinv.at<double>(2,0)*x+Hinv.at<double>(2,1)*y+Hinv.at<double>(2,2));
    u=Hinv.at<double>(0,0)*x*w2+Hinv.at<double>(0,1)*y*w2+Hinv.at<double>(0,2)*w2;
    v=Hinv.at<double>(1,0)*x*w2+Hinv.at<double>(1,1)*y*w2+Hinv.at<double>(1,2)*w2;

    double p,q;
    p=height-v-0.5;
    q=u-0.5;
    p=v;
    q=u;
    if(p<0 ||p>height-1 || q<0 || q>width-1){
        return 0;
//        cout<<"wrong mapping to input image"<<endl;
//        exit(-1);
    }

    //interpolation
    int topleftI=floor(p);
    int topleftJ=floor(q);
    int mappedColor=floor(SourceImage[topleftI][topleftJ][channel]*(1-p+topleftI)*(1-q+topleftJ)+
                          (topleftI<p? SourceImage[topleftI+1][topleftJ][channel]*(p-topleftI)*(1-q+topleftJ) : 0)+
                          (topleftJ<q? SourceImage[topleftI][topleftJ+1][channel]*(1-p+topleftI)*(q-topleftJ) : 0)+
                          ((topleftI<p && topleftJ<q)? SourceImage[topleftI+1][topleftJ+1][channel]*(p-topleftI)*(q-topleftJ) : 0));

    return (unsigned char)mappedColor;
}

void warpping(unsigned char***Imagedata, unsigned char***ImageOutput, Mat H, int BytesPerPixel=3,  int width=328, int height=328){
    int i,j,k;
    cout<<H<<endl;
//    for(i=0; i<height; i++) {
//        for(j=0; j<width; j++) {
//            for (k = 0; k < BytesPerPixel; k++) {
//                ImageOutput[i][j][k]=colorMapping(Imagedata,H,i,j,k);
//            }
//        }
//    }
    for(i=0; i<height; i++) {
        for(j=0; j<width; j++) {
            for (k = 0; k < BytesPerPixel; k++) {
                ImageOutput[i][j][k]=colorMapping(Imagedata,H,i+100,j+100,k);
            }
        }
    }
    cout<<"finish warping"<<endl;
}

void stitching(vector<Mat> imgs){
    Mat out;
    Ptr<Stitcher> stitcher = Stitcher::create(Stitcher::PANORAMA);
    Stitcher::Status status = stitcher->stitch(imgs, out);
    imshow("stitching",out);
    waitKey(0);
}
int main(){
    string leftPath="raw_images/left.raw";
    string middlePath="raw_images/middle.raw";
    string rightPath="raw_images/right.raw";
    string OutputPath="Output/lefttest.raw";

    //laod raw with opencv cause color distortion
    Mat leftImage=imread("raw_images/left.jpg");
    Mat middleImage=imread("raw_images/middle.jpg");
    Mat rightImage=imread("raw_images/right.jpg");
    //cout<<leftImage<<endl;
    //Mat H=keypointDetector(leftImage,middleImage);
    Mat H=keypointDetector(rightImage,middleImage);


    int BytesPerPixel = 3;
    int width = 576;
    int height = 432;
    int i,j,k;
    unsigned char***ImageData=AllocateMem<unsigned char>(BytesPerPixel,width,height);
    unsigned char***ImageOutput=AllocateMem<unsigned char>(BytesPerPixel,width,height);
    LoadImage(ImageData,middlePath,BytesPerPixel,width,height);
    //warpping(ImageData,ImageOutput,H);
    Mat ImgOut;


    //warp left image
//    warpPerspective(leftImage, ImgOut, H, leftImage.size(), INTER_NEAREST);
//    imshow("out",ImgOut);
//    waitKey(0);

    //warp right image
    warpPerspective(rightImage, ImgOut, H, rightImage.size(), INTER_NEAREST);
    imshow("out",ImgOut);
    waitKey(0);

    //output my cdoe
//    OutputImage(ImageOutput,OutputPath,BytesPerPixel,width,height);

//opencv stithing
//    vector<Mat> imgs;
//    imgs.push_back(leftImage);
//    imgs.push_back(middleImage);
//    imgs.push_back(rightImage);
//    stitching(imgs);

    cout<<"here"<<endl;
    FreeImage<unsigned char>(ImageData,BytesPerPixel,width,height);
    FreeImage<unsigned char>(ImageOutput,BytesPerPixel,width,height);
    return 0;
}

//reference
//https://docs.opencv.org/3.4/d7/dff/tutorial_feature_homography.html
//https://towardsdatascience.com/image-stitching-using-opencv-817779c86a83