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

//

void find_keypoints_SIFT(Mat input_image, Mat second_intput_image) {

	
		cv::Ptr<Feature2D> siftPtr = xfeatures2d::SIFT::create();
		std::vector<cv::KeyPoint> keypoints1 , keypoints2 , keyppoints3 , keyppoints4;

		vector<Point2f > keyppoints5;
		Mat descriptors_1, descriptors_2;
	

		siftPtr->detectAndCompute(input_image, noArray(), keypoints1, descriptors_1);
		siftPtr->detectAndCompute(second_intput_image, noArray(), keypoints2, descriptors_2);

		cv::Mat output1, output2;
		cv::drawKeypoints(input_image, keypoints1, output1);
		cv::drawKeypoints(second_intput_image, keypoints2, output2);
		//cv::imwrite("sift_result.jpg", output1);
		imshow("sift_result.jpg", output1);
		imshow("sift_result2.jpg", output2);
		
		
		match_points_SIFT(descriptors_1 , descriptors_2, keypoints1, keypoints2, input_image, second_intput_image);

		
}