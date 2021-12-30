#include "..\header\Header.h"

void joined_images(Mat input_image, Mat second_intput_image, vector<Point2f > myPoints_one, vector<Point2f > myPoints_two) {

	
	/*---------------------------------------*/
	Rect myRoi(0, 0, (myPoints_one[9].x - 1), input_image.cols);
	Mat croppedImage = input_image(myRoi);
	imshow("croppedImage", croppedImage);

	Rect myRoi2(myPoints_two[9].x, 0, second_intput_image.rows - myPoints_two[9].x, second_intput_image.cols);
	Mat croppedImage2 = second_intput_image(myRoi2);
	imshow("croppedImage2", croppedImage2);

	Mat3b final2(600, 600, Vec3b(0, 0, 0));
	//croppedImage2.convertTo(croppedImage2, -1, 1, 25);
	croppedImage.copyTo(final2(Rect(0, 0, croppedImage.cols, croppedImage.rows)));
	croppedImage2.copyTo(final2(Rect(croppedImage.cols, 0, croppedImage2.cols, croppedImage2.rows)));

	imshow("final2", final2);

	/*---------------------------------------*/


	int rows = input_image.rows + 400;
	int cols = input_image.cols + 800;

	// Create a black image
	Mat3b final(rows, cols, Vec3b(0, 0, 0));
	second_intput_image.convertTo(second_intput_image, -1, 1, 25);
	// Copy images in correct position

	second_intput_image.copyTo(final(Rect(((myPoints_one[7].x - myPoints_two[9].x) + 200), (200 - (myPoints_two[9].y - myPoints_one[7].y)), second_intput_image.cols, second_intput_image.rows)));

	input_image.copyTo(final(Rect(200, 200, input_image.cols, input_image.rows)));
	//second_intput_image.copyTo(final(Rect(480, 180, second_intput_image.cols, second_intput_image.rows)));

	//second_intput_image.copyTo(final(Rect(((myPoints_number[9].x - myPoints_letter[10].x) + 400), (400 - (myPoints_letter[10].y - myPoints_number[9].y)), second_intput_image.cols, second_intput_image.rows)));

	imshow("final", final);

}