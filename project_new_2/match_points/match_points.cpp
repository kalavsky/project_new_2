#include "..\header\Header.h"

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
//#include <opencv2/xfeatures2d.hpp>
//#include "opencv2/xfeatures2d.hpp"
//#include <opencv2/xfeatures2d.hpp>
//#include "opencv2/xfeatures2d/nonfree.hpp"
#include <opencv2/xfeatures2d/nonfree.hpp>
//#include <opencv2/xfeatures2d/nonfree.hpp>
#include <iostream>
#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp" 
#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/features2d/features2d.hpp>

#include "opencv2/xfeatures2d.hpp"
#include "opencv2/features2d.hpp"

using namespace std;
using namespace cv;

void match_points(Mat descriptors_1, Mat descriptors_2, vector<cv::KeyPoint> keypoints1, vector<cv::KeyPoint>  keypoints2 , Mat input_image, Mat second_intput_image) {


	FlannBasedMatcher matcher3(new cv::flann::LshIndexParams(5, 24, 2));
	vector< vector<DMatch> > knn_matches;
	matcher3.knnMatch(descriptors_1, descriptors_2, knn_matches, 2);
	const float ratio_thresh = 0.7f;
	std::vector<DMatch> good_matches2;
	for (size_t i = 0; i < knn_matches.size(); i++)
	{
		if (knn_matches[i].size() > 1) {

			std::cout << "knn_matches[i].size()" << knn_matches[i].size() << std::endl;

			std::cout << "knn_matches[i][0].distance " << knn_matches[i][0].distance << " ratio_thresh * knn_matches[i][1].distance " << ratio_thresh * knn_matches[i][1].distance << std::endl;

			if (knn_matches[i][0].distance < ratio_thresh * knn_matches[i][1].distance)
			{


				good_matches2.push_back(knn_matches[i][0]);
			}
		}
	}
	//imshow("matches.jpg", matches);
	Mat matched3;
	drawMatches(input_image, keypoints1, second_intput_image, keypoints2, good_matches2, matched3, Scalar::all(-1), Scalar::all(-1), std::vector<char>(), DrawMatchesFlags::DEFAULT);
	//cv::line(matched, myPoints_number[0], myPoints_letter[0], cv::Scalar(0, 0, 255), 2);
	imshow("matched3", matched3);

	/*
	// Sort matches by score
	std::sort(good_matches2.begin(), good_matches2.end());
	// Remove not so good matches
	const int numGoodMatches = good_matches2.size() * 0.2f;
	good_matches2.erase(good_matches2.begin() + numGoodMatches, good_matches2.end());

	Mat matched4;
	drawMatches(input_image, keypoints1, second_intput_image, keypoints2, good_matches2, matched4, Scalar::all(-1), Scalar::all(-1), std::vector<char>(), DrawMatchesFlags::DEFAULT);
	//cv::line(matched, myPoints_number[0], myPoints_letter[0], cv::Scalar(0, 0, 255), 2);
	imshow("matched4", matched4);

	*/
	// Extract location of good matches
	std::vector<Point2f> points1, points2;

	for (size_t i = 0; i < good_matches2.size(); i++)

	{

		points1.push_back(keypoints1[good_matches2[i].queryIdx].pt);

		points2.push_back(keypoints2[good_matches2[i].trainIdx].pt);

	}



	// Find homography

	Mat	h = findHomography(points1, points2, RANSAC);

	

	Mat im1Reg, im2Reg;

	// Use homography to warp image

	warpPerspective(input_image, im1Reg, h, second_intput_image.size());

	imshow("ORB_WARP1", im1Reg);

	warpPerspective(second_intput_image, im2Reg, h, input_image.size());
	imshow("ORB_WARP2", im2Reg);

	//extract_points(points1, points2);
	find_keypoints_SIFT(im1Reg , im2Reg);
}


void match_points_SIFT(Mat output1, Mat descriptors_1, Mat descriptors_2, vector<cv::KeyPoint> keypoints1, vector<cv::KeyPoint>  keypoints2, Mat input_image, Mat second_intput_image) {


	FlannBasedMatcher matcher3;
	vector< vector<DMatch> > knn_matches;
	matcher3.knnMatch(descriptors_1, descriptors_2, knn_matches, 2);
	const float ratio_thresh = 0.7f;
	std::vector<DMatch> good_matches2;
	for (size_t i = 0; i < knn_matches.size(); i++)
	{
		if (knn_matches[i].size() > 1) {

			std::cout << "knn_matches[i].size()" << knn_matches[i].size() << std::endl;

			std::cout << "knn_matches[i][0].distance " << knn_matches[i][0].distance << " ratio_thresh * knn_matches[i][1].distance " << ratio_thresh * knn_matches[i][1].distance << std::endl;

			if (knn_matches[i][0].distance < ratio_thresh * knn_matches[i][1].distance)
			{


				good_matches2.push_back(knn_matches[i][0]);
			}
		}
	}
	//imshow("matches.jpg", matches);
	Mat matched3;
	drawMatches(input_image, keypoints1, second_intput_image, keypoints2, good_matches2, matched3, Scalar::all(-1), Scalar::all(-1), std::vector<char>(), DrawMatchesFlags::DEFAULT);
	//cv::line(matched, myPoints_number[0], myPoints_letter[0], cv::Scalar(0, 0, 255), 2);
	imshow("matched3", matched3);





	
	/*
	// Sort matches by score
	std::sort(good_matches2.begin(), good_matches2.end());
	// Remove not so good matches
	const int numGoodMatches = good_matches2.size() * 0.2f;
	good_matches2.erase(good_matches2.begin() + numGoodMatches, good_matches2.end());

	Mat matched4;
	drawMatches(input_image, keypoints1, second_intput_image, keypoints2, good_matches2, matched4, Scalar::all(-1), Scalar::all(-1), std::vector<char>(), DrawMatchesFlags::DEFAULT);
	//cv::line(matched, myPoints_number[0], myPoints_letter[0], cv::Scalar(0, 0, 255), 2);
	imshow("matched4", matched4);
	
	*/
	// Extract location of good matches
	std::vector<Point2f> points1, points2;

	for (size_t i = 0; i < good_matches2.size(); i++)

	{

		points1.push_back(keypoints1[good_matches2[i].queryIdx].pt);

		points2.push_back(keypoints2[good_matches2[i].trainIdx].pt);

	}

	//cLine(drawing, cvPoint(center1.x, center1.y), 	cvPoint(center2.x, center2.y), 	Scalar(255, 255, 255), 1, 8, CV_AA);
	/*
	for (int i = 0; i < points1.size(); i++) {
		if (i + 1 == points1.size()) {
			line(input_image, points1[i], points1[0], cv::Scalar(0, 0, 255), 2);
		}
		else line(input_image, points1[i], points1[i + 1], cv::Scalar(0, 0, 255), 2);
	}

	//line(input_image, points1[0], points1[1], cv::Scalar(0, 0, 255), 2);
	//line(input_image, points1[1], points1[2], cv::Scalar(0, 0, 255), 2);
	imshow("Result", input_image);


	for (int i = 0; i < points2.size(); i++) {
		if (i + 1 == points2.size()) {
			line(second_intput_image, points2[i], points2[0], cv::Scalar(0, 0, 255), 2);
		}
		else line(second_intput_image, points2[i], points2[i + 1], cv::Scalar(0, 0, 255), 2);
	}

	//line(input_image, points1[0], points1[1], cv::Scalar(0, 0, 255), 2);
	//line(input_image, points1[1], points1[2], cv::Scalar(0, 0, 255), 2);
	imshow("Result2", second_intput_image);
	*/
	// Find homography

	Mat	h = findHomography(points1, points2, RANSAC);

	Mat im1Reg, im2Reg , affineW;

	// Use homography to warp image

	warpPerspective(input_image, im1Reg, h, second_intput_image.size());

	imshow("SIFT_WARP1", im1Reg);



	warpPerspective(second_intput_image, im2Reg, h, input_image.size());
	imshow("SIFT_WARP2", im2Reg);

	imwrite("D:/Diplomovka/project_new_2/project_new_2/img1_aligned.jpg", im1Reg);
	imwrite("D:/Diplomovka/project_new_2/project_new_2/img2_aligned.jpg", im2Reg);

	/*

	Mat f = findFundamentalMat(points1, points2, FM_RANSAC);
	Mat im1Reg_F, im2Reg_F;

	// Use homography to warp image

	warpPerspective(input_image, im1Reg_F, f, second_intput_image.size());

	imshow("SIFT_WARP1_F", im1Reg_F);

	warpPerspective(second_intput_image, im2Reg_F, f, input_image.size());
	imshow("SIFT_WARP2_F", im2Reg_F);
	*/
	/*
	cv::Mat result;
	result = im1Reg.clone();
	warpPerspective(im1Reg, result, h, cv::Size(im1Reg.cols + im2Reg.cols, im1Reg.rows));
	cv::Mat half(result, cv::Rect(0, 0, im2Reg.cols, im2Reg.rows));
	im2Reg.copyTo(half);
	//imwrite("/home/ishita/img_stitch/result.jpg", result);
	imshow("Result", result);

	*/
	//extract_points(points1, points2);

	find_epipolar( descriptors_1,  descriptors_2, keypoints1, keypoints2,  input_image,  second_intput_image , points1 , points2);

}