#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <ros/ros.h>
#include <opencv2/highgui/highgui.hpp>

int main(int argc, char** argv)
{

	ros::init(argc, argv, "opencv_test");	

	cv::VideoCapture vc(0);

	if (!vc.isOpened()) return -1; // 연결실패

	vc.set(CV_CAP_PROP_FRAME_WIDTH, 640);

	vc.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

	cv::Mat img;

	while(1){

		vc >> img;

		cv::imshow("cam",img);

		if(cv::waitKey(10)==27) break; //ESC

	}

	cv::destroyAllWindows();

	return 0;

}
