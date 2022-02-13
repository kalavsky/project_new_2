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
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>



using namespace std;
using namespace cv;


int drawlines(Mat input_image , Mat second_intput_image , vector<Point2f> points1_inliners1, vector<Point2f> points2_inliners , vector<cv::Point3f> lines) {

	cvtColor(input_image, input_image, COLOR_RGB2GRAY);
	cvtColor(second_intput_image, second_intput_image, COLOR_RGB2GRAY);
	/*
	r, c = img1.shape
		second_intput_image = cv.cvtColor(second_intput_image, cv.COLOR_GRAY2BGR)
		img2 = cv.cvtColor(img2, cv.COLOR_GRAY2BGR)
		for r, pt1, pt2 in zip(lines, pts1, pts2) :
			color = tuple(np.random.randint(0, 255, 3).tolist())
			x0, y0 = map(int, [0, -r[2] / r[1]])
			x1, y1 = map(int, [c, -(r[2] + r[0] * c) / r[1]])
			img1 = cv.line(img1, (x0, y0), (x1, y1), color, 1)
			img1 = cv.circle(img1, tuple(pt1), 5, color, -1)
			img2 = cv.circle(img2, tuple(pt2), 5, color, -1)
			return img1, img2
*/
	return 0;
}




void find_epipolar( Mat descriptor1, Mat descriptor2, vector<cv::KeyPoint> keypoints1, vector<cv::KeyPoint>  keypoints2, Mat input_image, Mat second_intput_image , vector<Point2f> points1, vector<Point2f> points2) {


	Mat output_array;
	vector<uchar> inliers;
	vector < vector<DMatch>> match;
	Mat good_match;
	vector<DMatch> ;
	vector< vector<DMatch> > good_matches2;
	Mat	f = findFundamentalMat(points1, points2, output_array, FM_RANSAC);

	std::vector<Point2f> points1_inliners, points2_inliners;


	//Mat	f = findFundamentalMat(points1, points2, output_array, FM_RANSAC);

	//uint8_t *myData = output_array.data;
	std::cout << "output_array" << output_array  << std::endl;
	std::cout << " output_array.rows" << output_array.rows << std::endl;
	std::cout << " output_array.cols " << output_array.cols << std::endl;

	std::cout << " &myData " << &output_array.u << std::endl;

	int a = output_array.data[0];
	int b = output_array.data[15];

	std::cout << "  %d " << a << std::endl;
	std::cout << "  %d " << b << std::endl;

	std::vector<DMatch> matched3;

	Mat row_inliners;

	for (int i = 0; i < output_array.rows ; i++) {

		if (output_array.data[i] == 1) {

		row_inliners.push_back(output_array.data[i]);
		points1_inliners.push_back(points1[i]);
		points2_inliners.push_back(points2[i]);
		
		}
		//std::cout << "  %d " << i << std::endl;
	
		//Vec3b &value = output_array.at<Vec3b>(Point(0, i));

		//std::cout << " output_array " << value << std::endl;
	}

	std::cout << "points " << row_inliners << std::endl;

	//vector<cv::Vec3d> leftLines, rightLines;

	vector<cv::Point3f> leftLines, rightLines;

	Mat output_array2;
	Mat	f2 = findFundamentalMat(points1_inliners, points2_inliners, output_array2 , FM_8POINT);

	vector<Mat>result_array_with_keypoints;
	result_array_with_keypoints = draw_keypoints1(input_image, second_intput_image, points1_inliners, points2_inliners);

	// imshow("Image1", output1[0]);
	 //imshow("Image2", output2);

	//cvtColor(input_image, input_image, COLOR_RGB2GRAY);
	//cvtColor(second_intput_image, second_intput_image, COLOR_RGB2GRAY);

	computeCorrespondEpilines(points1_inliners, 1, f2, rightLines);
	computeCorrespondEpilines(points2_inliners, 2, f2, leftLines);

	/*
	CV_Assert(points1.size() == points2.size() &&
		points2.size() == rightLines.size() &&
		rightLines.size() == leftLines.size());
		*/

	Mat imagePointLeftCameraMatrix = cv::Mat_<double>(3, 1);
	Mat output1, output2;

	for (std::size_t i = 0; i < rightLines.size(); i = i + 1)
	{
		cv::Point3f l = rightLines.at(i);
	
		double a = l.x;
		double b = l.y;
		double c = l.z;
		std::cout << "------------------------a,b,c Using OpenCV (ax+by+c=0)------------------------------" << std::endl;
		std::cout << a << ", " << b << ", " << c << std::endl;
		std::cout << "------------------------calculating a,b,c (ax+by+c=0) ------------------------------" << std::endl;

		imagePointLeftCameraMatrix.at<double>(0, 0) = points1_inliners[i].x;
		imagePointLeftCameraMatrix.at<double>(1, 0) = points1_inliners[i].y;
		imagePointLeftCameraMatrix.at<double>(2, 0) = 1;
		cv::Mat rightLineMatrix = f2 * imagePointLeftCameraMatrix;

		std::cout << rightLineMatrix.at<double>(0, 0) << std::endl;
		std::cout << rightLineMatrix.at<double>(1, 0) << std::endl;
		std::cout << rightLineMatrix.at<double>(2, 0) << std::endl;

		/////////////////////////////////drawing the line on the image/////////////////////////////////
		/*ax+by+c=0*/
		/*
		double x0, y0, x1, y1;
		x0 = 0;
		y0 = (-c - a * x0) / b;
		x1 = output1.cols;
		y1 = (-c - a * x1) / b;
		*/

		
		
		double x01, y01, x11, y11;
		x01 = 0;
		y01 = (-rightLines.at(i).z - rightLines.at(i).x * x01) / rightLines.at(i).y;
		x11 = result_array_with_keypoints[1].cols;
		y11 = (-rightLines.at(i).z - rightLines.at(i).x * x11) / rightLines.at(i).y;
		


		double x02, y02, x12, y12;
		x02 = 0;
		y02 = (-leftLines.at(i).z - leftLines.at(i).x * x02) / leftLines.at(i).y;
		x12 = result_array_with_keypoints[0].cols;
		y12 = (-leftLines.at(i).z - leftLines.at(i).x * x12) / leftLines.at(i).y;

		std::cout << "error: " << a * points2_inliners.at(i).x + b * points2_inliners.at(i).y + c << std::endl;
		cv::line(result_array_with_keypoints[1], Point(x01, y01), Point(x11, y11), Scalar(0, 255, 0), 1);
		cv::line(result_array_with_keypoints[0], Point(x02, y02), Point(x12, y12), Scalar(0, 255, 0), 1);
		
	}
	
	imshow("Image1", result_array_with_keypoints[0]);
	imshow("Image2", result_array_with_keypoints[1]);


	Mat	h = findHomography(points1_inliners, points2_inliners, RANSAC);

	Mat im1Reg, im2Reg, affineW;

	// Use homography to warp image
	imshow("input_image", input_image);
	warpPerspective(input_image, im1Reg, h, second_intput_image.size());

	imshow("SIFT_WARP1_inliners", im1Reg);


	imshow("second_intput_image", second_intput_image);
	warpPerspective(second_intput_image, im2Reg, h, input_image.size());
	imshow("SIFT_WARP2_ininers", im2Reg);
	//Mat imagePointLeftCameraMatrix = Mat_<double>(3, 1);


	/*
	lines1 = cv.computeCorrespondEpilines(pts2.reshape(-1, 1, 2), 2, F);
		lines1 = lines1.reshape(-1, 3)
		img5, img6 = drawlines(img1, img2, lines1, pts1, pts2)
*/
	
	// We select only inlier points
	//points1 = points1[output_array = 1];
	//points2 = points2[inliers.ravel() == 1];
	
	
	
}