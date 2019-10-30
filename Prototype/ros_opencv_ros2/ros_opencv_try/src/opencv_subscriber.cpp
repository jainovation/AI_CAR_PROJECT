#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "ros_opencv_try/MsgACC.h"
#include <pthread.h>
#include "OpenCV_Functions.h"
#include "OpenCV_Functions.cpp"
#include "OpenCV_Utils.h"
#include "OpenCV_Utils.cpp"


ros_opencv_try::MsgACC msg;
ros::Publisher req_pub;
cv::Mat image, result;
int distance_result;
int pre_acc_cmd;
float Kp=-0.1;



void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
  try
  {
    image = cv_bridge::toCvShare(msg, "bgr8")->image;
//    VideoCapture videoCapture("/home/nvidia/Desktop/challenge.mp4");

//      VideoCapture videoCapture("/home/ubuntu/Desktop/challenge.mp4");
//    VideoCapture videoCapture("/home/ubuntu/Desktop/1.mp4");
    
/*    if (!videoCapture.isOpened()){
			cout << "can't open video. \n" << endl;
			char a;
			cin >> a;
			//return 1;
		}
*/
//    while(1){		// video 틀려면 while문 필요
      //videoCapture.read(image);			/* select video/cam */
      image = cv_bridge::toCvShare(msg, "bgr8")->image;

      result = imageCopy(image);
      int width = result.cols;
      int height = result.rows;
      vector<Point> src_pts, dst_pts;
      vector<Vec4i> lines;

      src_pts.push_back(Point(width*0.40, height*0.65));
      src_pts.push_back(Point(width*0.6, height*0.65));
      src_pts.push_back(Point(width*0.9, height*0.9));
      src_pts.push_back(Point(width*0.1, height*0.9));

      dst_pts.push_back(Point(width*0.1, height*0.0));
      dst_pts.push_back(Point(width*0.9, height*0.0));
      dst_pts.push_back(Point(width*0.9, height*1.0));
      dst_pts.push_back(Point(width*0.1, height*1.0));
      imagePerspectiveTransformation(result, result, src_pts, dst_pts, Size());

/*	// color detection with hls
      Scalar yellow_lower(200, 200, 200);
      Scalar yellow_upper(255, 255, 255);
      Scalar white_lower(10, 150, 100);
      Scalar white_upper(360, 255, 255);


      Mat yellow_image, white_image;
      //rangeColor(result, yellow_image, yellow_lower, yellow_upper, COLOR_BGR2HLS);
      Mat mask;
      convertColor(result, mask, COLOR_BGR2HLS);
      inRange(mask, yellow_lower, yellow_upper, mask);
      yellow_image = imageCopy(mask);


      //rangeColor(result, white_image, white_lower, white_upper, COLOR_BGR2HLS);
      Mat mask2;
      convertColor(result, mask2, COLOR_BGR2HLS);
      inRange(mask2, white_lower, white_upper, mask2);
      white_image = imageCopy(mask2);

      result = yellow_image + white_image;
*/

      Scalar white_lower(200, 200, 200);
      Scalar white_upper(255, 255, 255);
      inRange(result, white_lower, white_upper, result); // using RGB

cv::imshow("whiteyellow", result);
      imageMorphologicalGradient(result, result);
      cannyEdge(result, result, 100, 200);
      imageHoughLinesP(result, lines, 1.0, 1.0 * PI / 180.0 , 50, 100, 100);
      Mat blackLineImage;
      //convertColor(result, blackLineImage, COLOR_GRAY2BGR);
      blackLineImage = makeBlackImage(result, true);
      
      distance_result = lineFittingForPerspectiveImage(blackLineImage, blackLineImage, lines, Scalar(0, 0, 255), 10, 60.0*PI/180.0);
  //    cout << distance_result << endl;
      imagePerspectiveTransformation(blackLineImage, result, dst_pts, src_pts, Size());
      //result = result + image;
      //overlayToImage(result, blackLineImage, result, 0.2, 0.2);
    

      // result //
      result = image + result;

//
	Point pt1(width*0.4, height*0.65);
	Point pt2(width*0.6, height*0.65);
	Point pt3(width*0.9, height*0.9);
	Point pt4(width*0.1, height*0.9);
	Scalar Color(255,0,0);
	drawLine(result, result, pt1, pt2, Color, 5);
	drawLine(result, result, pt2, pt3, Color, 5);
	drawLine(result, result, pt3, pt4, Color, 5);
	drawLine(result, result, pt1, pt4, Color, 5);
//
  
      cv::imshow("view", result);
      cv::waitKey(30);
//    }
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  }
}

void *test(void *data)
{
    ros::Rate loop_rate(30);
  while (ros::ok())
  {
                       
    if(abs(distance_result) < 25)  // ignore distance_result under 25
        //msg.acc_cmd = pre_acc_cmd;
        msg.acc_cmd = 90;
    else{
        msg.acc_cmd = distance_result * Kp + 90;  // PID control term
        if( msg.acc_cmd > 135 )	// Neutral point : 90 degrees
            msg.acc_cmd = 135;
        else if( msg.acc_cmd < 45 )
            msg.acc_cmd = 45;
        pre_acc_cmd = msg.acc_cmd;	// TODO 여기서 각도커맨드 주는거 + saturation 짜야함
    }

    cout<<msg.acc_cmd<<endl;
    req_pub.publish(msg);

    loop_rate.sleep();                  

  }
}


int main(int argc, char **argv)
{
  pthread_t thread_t;
  int req_stop = 0;
  int status;

  ros::init(argc, argv, "opencv_subscriber");
  ros::NodeHandle nh;

  cv::namedWindow("view");
  cv::namedWindow("whiteyellow");

  cv::startWindowThread();
  image_transport::ImageTransport it(nh);
  image_transport::Subscriber sub = it.subscribe("/usb_cam/image_raw", 1, imageCallback);	// subscribe(topic name)
//  image_transport::Subscriber sub = it.subscribe("/camera/image", 1, imageCallback);	// subscribe(topic name)

  req_pub = nh.advertise<ros_opencv_try::MsgACC>("logic_msg", 100);
  
  if (pthread_create(&thread_t, NULL, test, 0) < 0)
    {
        printf("thread create error:");
        exit(0);
    }

  
  ros::spin();
  cv::destroyWindow("view");

  pthread_join(thread_t, (void **)&status);
  printf("Thread End %d\n", status);
}
