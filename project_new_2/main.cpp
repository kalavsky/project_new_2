
#include <stdlib.h>
#include <stdio.h>

#include  "header\Header.h"
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/xfeatures2d.hpp>
#include "opencv2/xfeatures2d.hpp"
#include <opencv2/xfeatures2d.hpp>
#include "opencv2/xfeatures2d/nonfree.hpp"
#include <opencv2/xfeatures2d/nonfree.hpp>

#include <opencv2/opencv.hpp>
#include "opencv2/highgui.hpp"
#include "opencv2/stitching/detail/matchers.hpp"

#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include <opencv2/core/types.hpp>


#include "opencv2/core.hpp"

#include "opencv2/highgui.hpp"
#include "opencv2/features2d.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include "opencv2/opencv_modules.hpp"


#include "opencv2/highgui.hpp"
#include "opencv2/stitching/detail/autocalib.hpp"
#include "opencv2/stitching/detail/blenders.hpp"

#include "opencv2/stitching/detail/camera.hpp"
#include "opencv2/stitching/detail/exposure_compensate.hpp"
#include "opencv2/stitching/detail/matchers.hpp"
#include "opencv2/stitching/detail/motion_estimators.hpp"
#include "opencv2/stitching/detail/seam_finders.hpp"
#include "opencv2/stitching/detail/warpers.hpp"
#include <opencv2/stitching/warpers.hpp>

using namespace std;
using namespace cv;

//


struct userdata {
	Mat im;
	
	vector<Point2f> points;	
	
};

struct userdata2 {

	Mat im2;
	
	vector<Point2f> points2;
};
void mouseHandler(int event, int x, int y, int flags, void* data_ptr)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		userdata *data = ((userdata *)data_ptr);
		circle(data->im, Point(x, y), 3, Scalar(0, 255, 255), 5, cv::LINE_AA);
		imshow("Image", data->im);
		if (data->points.size() < 4)
		{
			data->points.push_back(Point2f(x, y));
		}
	}
}

void mouseHandler2(int event2, int x2, int y2, int flags2, void* data_ptr2)
{
	if (event2 == EVENT_LBUTTONDOWN)
	{
		userdata2 *data2 = ((userdata2 *)data_ptr2);
		circle(data2->im2, Point(x2, y2), 3, Scalar(0, 255, 255), 5, cv::LINE_AA);
		imshow("Image2", data2->im2);
		if (data2->points2.size() < 4)
		{
			data2->points2.push_back(Point2f(x2, y2));
		}
	}
}

int main()
{
	
	Mat input_image = imread("chess_number.jpg");
	//Mat input_image = imread("picture1.jpg");
	resize(input_image, input_image, cv::Size(500, 500));
	imshow("img_in_number", input_image); // Show our image inside the created window.

	Mat second_intput_image = imread("half_chess_NL.jpg");
	//Mat second_intput_image = imread("picture2.jpg");
	resize(second_intput_image, second_intput_image, cv::Size(500, 500));
	imshow("img_in_letter", second_intput_image); // Show our image inside the created window.
	

	

	//***********************find_keypoints(input_image, second_intput_image);


	Mat src, gray, gray2, bw, dst, bodiky;
	vector<vector<Point>> contours , contours2;
	vector<vector<Point>> Resultscontours;
	Mat approx;
	Mat canny_output,canny_output2;
	vector<Vec4i> hierarchy, hierarchy2;
	RotatedRect rect2;

	//Mat image_in = imread("picture01.jpg");
	//Mat image_in2 = imread("picture02.jpg");
	Mat image_in = imread("picture1.jpg");
	Mat image_in2 = imread("picture2.jpg");



	resize(image_in, image_in, cv::Size(1024, 768), 0, 0, INTER_LINEAR);
	resize(image_in2, image_in2, cv::Size(1024, 768), 0, 0, INTER_LINEAR);

	//resize(image_in, image_in, cv::Size(200, 100), 0, 0, INTER_LINEAR);
	//resize(image_in2, image_in2, cv::Size(200, 100), 0, 0, INTER_LINEAR);

		find_keypoints_SIFT(image_in, image_in2);

		//find_keypoints_ORB(image_in, image_in2);

	//find_keypoints(image_in, image_in2);
	//homography(image_in, image_in2);

	//	find_contours(image_in, image_in2);


	/*

	cvtColor(image_in, gray, COLOR_RGB2GRAY);
	cvtColor(image_in2, gray2, COLOR_RGB2GRAY);
	
	//blur(gray, gray, Size(3, 3));
	//blur(gray2, gray2, Size(3, 3));

	imshow("gray", gray);
	imshow("gray2", gray2);
	Canny(gray, canny_output, 200, 300, 3);
	Canny(gray2, canny_output2, 200, 300, 3);

	// Find contours
	findContours(canny_output, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	findContours(canny_output2, contours2, hierarchy2, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	imshow("canny_output", canny_output);
	imshow("canny_output2", canny_output2);
	//imshow("contours", contours);

	
	/*
	double ans = 0;

	for (int i = 0; i < contours2.size(); i++)
	{
		for (int j = 0; j < contours.size(); j++) {
		ans = matchShapes(contours2[i], contours[j], 1, 0.0);
		if (ans <= 0.0001) {
		std::cout << i <<" i " << j << " j " << ans << std::endl;
		}
		}
	}
	*/
	/*
	
	// Read in the image.
	Mat im_src = imread("picture1.jpg");
	resize(im_src, im_src, cv::Size(1024, 768), 0, 0, INTER_LINEAR);
	
	Size size = im_src.size();

	// Create a vector of points.
	vector<Point2f> pts_src;
	pts_src.push_back(Point2f(0, 0));
	pts_src.push_back(Point2f(size.width - 1, 0));
	pts_src.push_back(Point2f(size.width - 1, size.height - 1));
	pts_src.push_back(Point2f(0, size.height - 1));

	//pts_src.push_back(Point2f(0, 0));
	//pts_src.push_back(Point2f(600, 0));
	//pts_src.push_back(Point2f(600, 600));
	//pts_src.push_back(Point2f(0, 500));

	// Destination image
	Mat im_dst = imread("picture2.jpg");
	resize(im_dst, im_dst, cv::Size(1024, 768), 0, 0, INTER_LINEAR);
	//Create a window
	namedWindow("Image", 1);
	//namedWindow("Image2", 1);

	Mat im_temp = im_dst.clone();
	//Mat im_temp2 = im_src.clone();

	userdata data;
	//userdata2 data2;
	data.im = im_temp;
	//data2.im2 = im_temp2;

	//imshow("Image", im_temp2);

	//show the image
	
	//set the callback function for any mouse event
	setMouseCallback("Image", mouseHandler, &data);
	//setMouseCallback("Image2", mouseHandler2, &data2);
	imshow("Image", im_temp);
	waitKey(0);
	
	

	Mat tform = findHomography(pts_src,data.points);

	Mat imageeeees;

	std::cout << "tform :" << tform << std::endl;
	std::cout << "tform :" << im_dst.size() << std::endl;
	std::cout << "tform :" << im_src.size() << std::endl;

	warpPerspective(im_src, im_temp, tform, im_dst.size());



	imshow("im_temp", im_temp);


	std::cout << "tform :" << tform << std::endl;

	/*
	Point pts_dst[4];
	for (int i = 0; i < 4; i++)
	{
		pts_dst[i] = data.points[i];
	}

	fillConvexPoly(im_dst, pts_dst, 4, Scalar(0), cv::LINE_AA);

	im_dst = im_dst + im_temp;

	imshow("Image", im_dst);
	waitKey(0);

	*/
	std::cout << "TADAAA" << std::endl;

	
	
	while (1) {
		if (waitKey(100) == 27) break;
	}

}