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
		////
		FlannBasedMatcher matcher3;
		vector< vector<DMatch> > knn_matches;
		matcher3.knnMatch(descriptors_1, descriptors_2, knn_matches, 2);
		const float ratio_thresh = 0.8f;
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

		cv::Mat output1, output2;
		cv::drawKeypoints(input_image, keypoints1, output1);
		cv::drawKeypoints(second_intput_image, keypoints2, output2);
		//cv::imwrite("sift_result.jpg", output1);
		imshow("sift_result.jpg", output1);
		imshow("sift_result2.jpg", output2);


}