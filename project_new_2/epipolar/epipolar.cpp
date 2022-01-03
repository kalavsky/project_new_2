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

void find_epipolar(Mat descriptor1, Mat descriptor2, vector<cv::KeyPoint> keypoints1, vector<cv::KeyPoint>  keypoints2, Mat input_image, Mat second_intput_image , vector<Point2f> points1, vector<Point2f> points2) {


	Mat output_array;
	vector<uchar> inliers;
	vector < vector<DMatch>> match;
	Mat good_match;
	vector<DMatch> ;
	vector< vector<DMatch> > good_matches2;
	Mat	f = findFundamentalMat(points1, points2, output_array, FM_RANSAC);

	//uint8_t *myData = output_array.data;
	std::cout << "output_array" << output_array  << std::endl;
	std::cout << " output_array.rows" << output_array.rows << std::endl;
	std::cout << " output_array.cols " << output_array.cols << std::endl;

	std::cout << " &myData " << &output_array.u << std::endl;



	for (int i = 0; i < output_array.rows ; i++) {
	
		Vec3b &value = output_array.at<Vec3b>(Point(0, i));

		std::cout << " output_array " << value << std::endl;
	}


	
	// We select only inlier points
	//points1 = points1[output_array = 1];
	//points2 = points2[inliers.ravel() == 1];
	
	
	
}