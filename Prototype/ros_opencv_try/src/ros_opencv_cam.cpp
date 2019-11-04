#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <ros/ros.h>
#include <opencv2/highgui/highgui.hpp>

#include "OpenCV_Functions.h"
#include "OpenCV_Functions.cpp"
#include "OpenCV_Utils.h"
#include "OpenCV_Utils.cpp"

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{

	ros::init(argc, argv, "opencv_test");	

	cv::VideoCapture vc(0);

	if (!vc.isOpened()) return -1; // 연결실패

	vc.set(CV_CAP_PROP_FRAME_WIDTH, 640);

	vc.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

	cv::Mat image, result;

	while(1){

		vc >> image;


		/********* Hough Transform **********/
		int height = image.rows;
		int width = image.cols;
		result = imageCopy(image);

		/* ROI */
		vector<Point> src_pts;
		Mat roi_active;
		src_pts.push_back(Point(int(width*0.45), int(height*0.65)));
		src_pts.push_back(Point(int(width*0.65), int(height*0.65)));
		src_pts.push_back(Point(int(width*1), int(height*1)));
		src_pts.push_back(Point(int(width*0), int(height*1)));
		polyROI(result, roi_active, src_pts);

		/* color detection */
		Mat white, yellow, roi_hls;
		convertColor(roi_active, roi_hls, COLOR_BGR2HLS);
		Scalar white_lower_hls(0,200,0);
		Scalar white_upper_hls(180,255,255);
		Scalar yellow_lower_hls(10, 100, 100);
		Scalar yellow_upper_hls(25, 180, 255);
		splitColor(roi_hls, white, white_lower_hls, white_upper_hls);
		splitColor(roi_hls, yellow, yellow_lower_hls, yellow_upper_hls);
		roi_hls = white + yellow;
		convertColor(roi_hls, result, COLOR_HLS2BGR);

		/* lane detection - hough transform */
		convertColor(roi_hls, roi_hls, COLOR_BGR2GRAY);
		imageMorphologicalGradient(roi_hls, result);
		cannyEdge(result, result, 100, 200);
		vector<Vec4i> lines;
		HoughLinesP(result, lines, 1, CV_PI/180, 100, 20, 100);
		drawHoughLinesP(result, lines, Scalar(0,0,255), 3);

		/* result */
		result = image + result;



		cv::imshow("cam",result);
		if(cv::waitKey(10)==27) break; //ESC

	}

	cv::destroyAllWindows();

	return 0;

}
