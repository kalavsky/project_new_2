#include "..\header\Header.h"
#include <stdlib.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>



struct userdata {
	Mat im;
	vector<Point2f> points;
};



void homography(Mat image1, Mat image2 , vector<Point2f > myPoints_one, vector<Point2f > myPoints_two) {

	Size size_image1 = image1.size();
	Size size_image2 = image2.size();

	vector<Point2f> pts_image1;
	pts_image1.push_back(Point2f(0, 0));
	pts_image1.push_back(Point2f(size_image1.width - 1, 0));
	pts_image1.push_back(Point2f(size_image1.width - 1, size_image1.height - 1));
	pts_image1.push_back(Point2f(0, size_image1.height - 1));

	vector<Point2f> pts_image2;
	pts_image2.push_back(Point2f(0, 0));
	pts_image2.push_back(Point2f(size_image1.width - 1, 0));
	pts_image2.push_back(Point2f(size_image1.width - 1, size_image1.height - 1));
	pts_image2.push_back(Point2f(0, size_image1.height - 1));


	Mat image2_temp = image2.clone();

	userdata data;
	data.im = image2_temp;
	//set the callback function for any mouse event
	//setMouseCallback("Image", mouseHandler, &data);

	//show the image
	//imshow("Image", image2_temp);
	//waitKey(0);

	//Mat tform = findHomography(pts_image1, pts_image2);
	Mat tform = findHomography(myPoints_one, myPoints_two);

	warpPerspective(image2, image1, tform, image1.size());

	imshow("im_temp", image1);
	//imshow("im_temp", image1);
}



