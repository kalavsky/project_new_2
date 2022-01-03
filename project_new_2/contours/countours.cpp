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

void find_contours(Mat image_in, Mat image_in2) {

	Mat src, gray, gray2, bw, dst, bodiky;
	vector<vector<Point>> contours, contours2;
	vector<vector<Point>> Resultscontours;
	Mat approx;
	Mat canny_output, canny_output2;
	vector<Vec4i> hierarchy, hierarchy2;
	RotatedRect rect2;

	//cvtColor(image_in, gray, COLOR_RGB2GRAY);
	//cvtColor(image_in2, gray2, COLOR_RGB2GRAY);

	gray = image_in.clone();
	gray2 = image_in.clone();

	//blur(gray, gray, Size(3, 3));
	//blur(gray2, gray2, Size(3, 3));

	imshow("gray", gray);
	imshow("gray2", gray2);
	Canny(gray, canny_output, 20, 100, 3);
	Canny(gray2, canny_output2, 20, 100, 3);

	// Find contours
	findContours(canny_output, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	findContours(canny_output2, contours2, hierarchy2, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	imshow("canny_output", canny_output);
	imshow("canny_output2", canny_output2);
	//imshow("contours", contours);

	//find_keypoints_SIFT(gray, gray2);

	Mat image1, image2; 
		image1 = image_in.clone();
		image2 = image_in2.clone();

	drawContours(image_in, contours, -1, (255, 0, 0), 3);
	imshow("image_in", image_in);

	drawContours(image2, contours, -1, (0, 0, 255), 3);
	imshow("image2", image2);

	drawContours(image_in2, contours2, -1, (0,0,255), 3);
	imshow("image_in2", image_in2);

	drawContours(image1, contours2, -1, (255, 0, 0), 3);
	imshow("image1", image1);
	/*
	BFMatcher matcher;
	std::vector< DMatch > matches;
	matcher.match(contours, contours2, matches);


	Mat matched;
	//drawMatches(image_in, contours, image_in, contours2, matches, matched, Scalar::all(-1), Scalar::all(-1), std::vector<char>(), DrawMatchesFlags::DEFAULT);
	//cv::line(matched, myPoints_number[0], myPoints_letter[0], cv::Scalar(0, 0, 255), 2);
	imshow("matched", matched);
	*/
}