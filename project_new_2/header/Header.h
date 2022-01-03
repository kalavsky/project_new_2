#pragma once
// HEADER_H.h: This is a precompiled header file.

#include <stdlib.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "opencv2/xfeatures2d.hpp"
#include <opencv2/xfeatures2d.hpp>
#include "opencv2/xfeatures2d/nonfree.hpp"
#include <opencv2/xfeatures2d/nonfree.hpp>


#ifndef HEADER_H
#define HEADER_H
using namespace std;
using namespace cv;

void find_keypoints(Mat image1, Mat image2);
void draw_keypoints(Mat image1, Mat image2,vector<Point2f > myPoints_one , vector<Point2f > myPoints_two);
void joined_images(Mat image1, Mat image2, vector<Point2f > myPoints_one, vector<Point2f > myPoints_two);
void homography(Mat image1, Mat image2, vector<Point2f > myPoints_one, vector<Point2f > myPoints_two);


void find_keypoints_SIFT(Mat image1, Mat image2);
void find_keypoints_ORB(Mat image1, Mat image2);

void match_points(Mat descriptor1 , Mat descriptor2, vector<cv::KeyPoint> keypoints1 , vector<cv::KeyPoint>  keypoints2, Mat input_image, Mat second_intput_image );
void match_points_SIFT(Mat descriptor1, Mat descriptor2, vector<cv::KeyPoint> keypoints1, vector<cv::KeyPoint>  keypoints2, Mat input_image, Mat second_intput_image);

//void extract_points(vector<Point2f> points1, vector<Point2f> points2);


void find_contours(Mat image1, Mat image2);

void find_epipolar(Mat descriptor1, Mat descriptor2, vector<cv::KeyPoint> keypoints1, vector<cv::KeyPoint>  keypoints2, Mat input_image, Mat second_intput_image , vector<Point2f> points1, vector<Point2f> points2);
#endif
