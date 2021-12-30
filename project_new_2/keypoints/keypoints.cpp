#include "..\header\Header.h"


void find_keypoints(Mat input_image, Mat second_intput_image) {

	int pom = 0;

	vector<Point2f > myPoints_number;
	vector<Point2f > myPoints_letter;

	
	for (int i = 0; i < input_image.cols; i++) {

		for (int j = 0; j < input_image.rows; j++) {


			Vec3b &color_number = input_image.at<Vec3b>(Point(i, j));
			Vec3b &color_letter = second_intput_image.at<Vec3b>(Point(i, j));
			//if ((color[0] < 200 && color[1] < 200 && color[2] < 200) || (color[0] > 50 && color[1] > 50 && color[2] > 50 )) {
			pom++;
			//if ((color[0] < 240 && color[0] > 10 )  &&  (color[1] < 240 && color[1] > 10 ) && (color[2] < 240 && color[2] > 10) ) {
			if (pom % 13260 == 0) {

				color_number[0] = 0; // B
				color_number[1] = 255;  // G
				color_number[2] = 0; // R

				color_letter[0] = 0; // B
				color_letter[1] = 255;  // G
				color_letter[2] = 0; // R

				input_image.at<Vec3b>(Point2f(i, j)) = color_number;
				second_intput_image.at<Vec3b>(Point2f(i, j)) = color_letter;
				myPoints_number.push_back(Point2f(i, j));
				myPoints_letter.push_back(Point2f(i, j));


				//matches.push_back(myPoints_number);
				//matches_to_draw.push_back(myPoints_number[i][0]);

			}
		}

	}

	imshow("img_out_number", input_image); // Show our image inside the created window.
	imshow("img_out_letter", second_intput_image); // Show our image inside the created window.


	draw_keypoints( input_image,  second_intput_image, myPoints_number, myPoints_letter);

	//homography(input_image, second_intput_image, myPoints_number, myPoints_letter);

}

