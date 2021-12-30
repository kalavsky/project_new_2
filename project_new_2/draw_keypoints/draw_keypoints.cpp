#include "..\header\Header.h"

void draw_keypoints(Mat input_image , Mat second_intput_image, vector<Point2f > myPoints_one, vector<Point2f > myPoints_two) {



	Mat matched;

	vector<KeyPoint > myKeypoints_number;
	vector<KeyPoint > myKeypoints_letter;

	vector<DMatch> matches_right(myPoints_one.size());
	vector<DMatch> matches_left(myPoints_one.size());

	for (int i = 0; i < myPoints_one.size(); i++) {
		matches_right[i] = DMatch(i, i, 0);
		matches_left[i] = DMatch(i, i, 0);

		myKeypoints_number.push_back(KeyPoint(myPoints_one[i], 1.f));
		myKeypoints_letter.push_back(KeyPoint(myPoints_two[i], 1.f));

	}

	double res = cv::norm(myPoints_one[0] - myPoints_two[0]);
	vector< DMatch > matches;

	Point2f point1 = myKeypoints_number[matches_right[0].queryIdx].pt;
	Point2f point2 = myKeypoints_letter[matches_left[0].trainIdx].pt;

	drawMatches(input_image, myKeypoints_number, second_intput_image, myKeypoints_letter, matches_right, matched, Scalar::all(-1), Scalar::all(-1), std::vector<char>(), DrawMatchesFlags::DEFAULT);
	//cv::line(matched, myPoints_number[0], myPoints_letter[0], cv::Scalar(0, 0, 255), 2);
	imshow("matched", matched); 
	


	joined_images(input_image, second_intput_image, myPoints_one, myPoints_two);


}