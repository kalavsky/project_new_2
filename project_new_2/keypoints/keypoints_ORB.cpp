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

void find_keypoints_ORB(Mat input_image, Mat second_intput_image) {

	//cvtColor(input_image, input_image, COLOR_RGB2GRAY);
	//Ptr<xfeatures2d::SIFT> siftPtr = xfeatures2d::SIFT::create();

	int 	nfeatures = 0;
	int 	nOctaveLayers = 3;
	double 	contrastThreshold = 0.04;
	double 	edgeThreshold = 10;
	double 	sigma = 1.6;

	cv::Ptr<Feature2D> OrbPtr = ORB::create();
	//cv::Ptr<Feature2D> OrbPtr = FastFeatureDetector::create();
	//cv::Ptr<Feature2D> siftPtr = xfeatures2d::SIFT::create();
	std::vector<cv::KeyPoint> keypoints1, keypoints2, keyppoints3, keyppoints4;

	vector<Point2f > keyppoints5;
	//OrbPtr->detect(input_image, keypoints1);
	//OrbPtr->detect(second_intput_image, keypoints2);
	//keyppoints3.resize(5);

	//imwrite("keypoints1.txt", keypoints1.data);

	Mat descriptors_1, descriptors_2;
	//OrbPtr->detectAndCompute(input_image, noArray(), keypoints1, descriptors_1);
	//OrbPtr->detectAndCompute(second_intput_image, noArray(), keypoints2, descriptors_2);

	OrbPtr->detectAndCompute(input_image, noArray(), keypoints1, descriptors_1);
	OrbPtr->detectAndCompute(second_intput_image, noArray(), keypoints2, descriptors_2);

	// Add results to image and save.
	cv::Mat output1, output2;
	cv::drawKeypoints(input_image, keypoints1, output1);
	cv::drawKeypoints(second_intput_image, keypoints2, output2);
	//cv::imwrite("sift_result.jpg", output1);
	imshow("ORB_result.jpg", output1);
	imshow("ORB_result2.jpg", output2);


	vector<Point2f> kp1Local, kp2Local;
	KeyPoint::convert(keypoints1, kp1Local);
	KeyPoint::convert(keypoints2, kp2Local);

	for (int k = 0; k < keypoints1.size(); k++) {

		if (keypoints1[k].size == keypoints2[k].size) {
			//keyppoints3.insert(keypoints1[k]);
			std::cout << "keypoints1[i]." << k << "size: " << keypoints1[k].size << std::endl;
			std::cout << "keypoints2[i]." << k << "size: " << keypoints2[k].size << std::endl;
			keyppoints3.resize(k + 1);
			keyppoints4.resize(k + 1);
			keyppoints3[k] = (keypoints1[k]);
			keyppoints4[k] = (keypoints2[k]);
		}
	}

	cv::Mat output3, output4;
	cv::drawKeypoints(input_image, keypoints1, output3);
	cv::drawKeypoints(second_intput_image, keypoints2, output4);

	imshow("output3.jpg", output3);
	imshow("output4.jpg", output4);



	for (int i = 0; i < keypoints1.size(); i++) {

		std::cout << "keypoints1[i]." << i << "pt.x: " << keypoints1[i].pt.x << std::endl;
		std::cout << "keypoints1[i]." << i << "pt.y: " << keypoints1[i].pt.y << std::endl;
		std::cout << "keypoints1[i]." << i << "response: " << keypoints1[i].response << std::endl;
		std::cout << "keypoints1[i]." << i << "angle: " << keypoints1[i].angle << std::endl;
		std::cout << "keypoints1[i]." << i << "size: " << keypoints1[i].size << std::endl;
		std::cout << "keypoints1[i]." << i << "octave: " << keypoints1[i].octave << std::endl;
		std::cout << "keypoints1[i]." << i << "class_id: " << keypoints1[i].class_id << std::endl;

		std::cout << " " << std::endl;

		std::cout << "keypoints2[i]." << i << "pt.x: " << keypoints2[i].pt.x << std::endl;
		std::cout << "keypoints2[i]." << i << "pt.y: " << keypoints2[i].pt.y << std::endl;
		std::cout << "keypoints2[i]." << i << "response: " << keypoints2[i].response << std::endl;
		std::cout << "keypoints2[i]." << i << "angle: " << keypoints2[i].angle << std::endl;
		std::cout << "keypoints2[i]." << i << "size: " << keypoints2[i].size << std::endl;
		std::cout << "keypoints2[i]." << i << "octave: " << keypoints2[i].octave << std::endl;
		std::cout << "keypoints2[i]." << i << "class_id: " << keypoints2[i].class_id << std::endl;

		std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;

		/*
	imshow("sift_result.txt", keypoints1[i].pt.x);
	imshow("sift_result.txt", keypoints1[i].pt.y);
	imshow("sift_result.txt", keypoints1[i].response);
	imshow("sift_result.txt", keypoints1[i].angle);
	imshow("sift_result.txt", keypoints1[i].size);
	imshow("sift_result.txt", keypoints1[i].octave);
	imshow("sift_result.txt", keypoints1[i].class_id);

	*/
	}
	BFMatcher matcher;
	std::vector< DMatch > matches;
	matcher.match(descriptors_1, descriptors_2, matches);


	Mat matched;
	drawMatches(input_image, keypoints1, second_intput_image, keypoints2, matches, matched, Scalar::all(-1), Scalar::all(-1), std::vector<char>(), DrawMatchesFlags::DEFAULT);
	//cv::line(matched, myPoints_number[0], myPoints_letter[0], cv::Scalar(0, 0, 255), 2);
	imshow("matched", matched);


	FlannBasedMatcher matcher2(new cv::flann::LshIndexParams(5, 24, 2));
	//FlannBasedMatcher matcher2(new cv::flann::LshIndexParams(20, 10, 2));
	//FlannBasedMatcher matcher(new flann::LshIndexParams(20,10,2));
	std::vector<DMatch> good_matches;
	matcher2.match(descriptors_1, descriptors_2, good_matches);
	Mat matched2;
	drawMatches(input_image, keypoints1, second_intput_image, keypoints2, good_matches, matched2, Scalar::all(-1), Scalar::all(-1), std::vector<char>(), DrawMatchesFlags::DEFAULT);
	//cv::line(matched, myPoints_number[0], myPoints_letter[0], cv::Scalar(0, 0, 255), 2);
	imshow("matched2", matched2);




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
	Ptr<DescriptorMatcher> matcher2 = DescriptorMatcher::create(DescriptorMatcher::FLANNBASED);
	vector< vector<DMatch> > knn_matches;
	matcher2->knnMatch(descriptors_1, descriptors_2, knn_matches,2);
	const float ratio_thresh = 0.7f;
	std::vector<DMatch> good_matches;
	for (size_t i = 0; i < knn_matches.size(); i++)
	{
		if (knn_matches[i][0].distance < ratio_thresh * knn_matches[i][1].distance)
		{
			good_matches.push_back(knn_matches[i][0]);
		}
	}
	//imshow("matches.jpg", matches);
	Mat matched2;
	drawMatches(input_image, keypoints1, second_intput_image, keypoints2, good_matches, matched2, Scalar::all(-1), Scalar::all(-1), std::vector<char>(), DrawMatchesFlags::DEFAULT);
	//cv::line(matched, myPoints_number[0], myPoints_letter[0], cv::Scalar(0, 0, 255), 2);
	imshow("matched2", matched2);


	*/
	

	match_points(descriptors_1, descriptors_2, keypoints1, keypoints2, input_image, second_intput_image);
}