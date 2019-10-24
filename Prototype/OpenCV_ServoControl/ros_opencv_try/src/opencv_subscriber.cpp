#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "ros_opencv_try/MsgACC.h"
#include <pthread.h>
#include "Opencv_funcs/OpenCV_Functions.h"
#include "Opencv_funcs/OpenCV_Functions.cpp"
#include "Opencv_funcs/OpenCV_Utils.h"
#include "Opencv_funcs/OpenCV_Utils.cpp"

ros_opencv_try::MsgACC msg;
ros::Publisher req_pub;
cv::Mat image, result;
int distance_result;

//////////////////////

void splitTwoSideLinesForPerspectiveImage(vector<Vec4i> &lines, vector<vector<float> > &lefts, vector<vector<float> > &rights, int middle_x, float slope_threshold)
{
    int i;
    lefts.clear();
    rights.clear();
    vector<float> temp;
    for( i = 0 ; i < lines.size() ; i++ )
    {
        temp.clear();
        Vec4i line = lines[i];
        int x1, y1, x2, y2;
        x1 = line[0];
        y1 = line[1];
        x2 = line[2];
        y2 = line[3];
        if(x1 < middle_x && x2 < middle_x) // left
        {
            float slope;
            if(x1 - x2 <= 0.001)
                slope = 999.;
            else
                slope = (float)(y2-y1)/(float)(x2-x1);
            if (abs(slope) < slope_threshold || y1 == y2)
                continue;
            temp.push_back(slope);
            temp.push_back(x1);
            temp.push_back(y1);
            temp.push_back(x2);
            temp.push_back(y2);
            lefts.push_back(temp);
        }
        else if (x1 > middle_x && x2 > middle_x) // right
        {
            float slope;
            if(x1 - x2 <= 0.001)
                slope = 999.;
            else
                slope = (float)(y2-y1)/(float)(x2-x1);
            if (abs(slope) < slope_threshold || y1 == y2)
                continue;
            temp.push_back(slope);
            temp.push_back(x1);
            temp.push_back(y1);
            temp.push_back(x2);
            temp.push_back(y2);
            rights.push_back(temp);
        }
    }
    return;
}

int lineFittingForPerspectiveImage(Mat &image, Mat &result, vector<Vec4i> &lines, Scalar color, int thickness, float slope_threshold)		// Â÷Œ± ÁßœÉ°ú ÀÌ¹ÌÁö ÁßœÉÀÇ °Åž®žŠ ž®ÅÏ°ªÀž·Î ³»ºž³»ÁÜ 
{
    result = imageCopy(image);
    int height = image.rows;
    int middle_x = int(0.5 * image.cols);
    int heading_x;
    vector<vector<float> > lefts, rights;
    splitTwoSideLinesForPerspectiveImage(lines, lefts, rights, middle_x, slope_threshold);
    vector<float> left, right;
    medianPoint(lefts, left);
    medianPoint(rights, right);
    int min_y = 0.0;
    int max_y = height;
    int min_x_left, max_x_left, min_x_right, max_x_right;
    if( !left.empty()) 
    {
        min_x_left = interpolate(left[1], left[2], left[3], left[4], min_y);
        max_x_left = interpolate(left[1], left[2], left[3], left[4], max_y);
        line(result, Point(min_x_left, min_y), Point(max_x_left, max_y), color, thickness);
    }
    if( !right.empty())
    {
        min_x_right = interpolate(right[1], right[2], right[3], right[4], min_y);
        max_x_right = interpolate(right[1], right[2], right[3], right[4], max_y);
        line(result, Point(min_x_right, min_y), Point(max_x_right, max_y), color, thickness);
    }
    if (!left.empty() && !right.empty())
    {   
        vector<Point> pts;
        pts.push_back(Point(min_x_left, min_y));
        pts.push_back(Point(min_x_right, min_y));
        pts.push_back(Point(max_x_right, max_y));
        pts.push_back(Point(max_x_left, max_y));
        vector<vector<Point> > fillContAll;
        fillContAll.push_back(pts);
        fillPoly(result, fillContAll, Scalar(0, 255, 0));
        line(result, Point(min_x_left, min_y), Point(max_x_left, max_y), color, thickness);
        line(result, Point(min_x_right, min_y), Point(max_x_right, max_y), color, thickness);
        heading_x = int(0.5 *(min_x_left + min_x_right));
    }
    line(result, Point(middle_x,0), Point(middle_x,height), Scalar(0, 0, 255), 5);
    int distance = middle_x - heading_x;
    if(distance != 0)
    {
        drawRect(result, result, Point(middle_x, 0), Point(heading_x, 50), Scalar(0, 0, 255), -1);
    }
    return distance;
}

void overlayToImage(Mat &backGroungImage, Mat &overlayImage, Mat &dstImage, double fx, double fy)
{
    Mat temp1, temp2;
    imageResize(overlayImage, temp1, Size(), fx, fy);
    int w2 = temp1.cols;
    temp2 = imageCopy(backGroungImage);
    PasteRectROI(temp1, temp2, Point(temp2.cols-w2, 0));
    dstImage = imageCopy(temp2);
    return;
}



//////////////////////

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
  try
  {
    //image = cv_bridge::toCvShare(msg, "bgr8")->image;
    VideoCapture videoCapture("/home/ubuntu/Desktop/challenge.mp4");
    
    if (!videoCapture.isOpened()){
			cout << "동영상 파일을 열수 없습니다. \n" << endl;
			char a;
			cin >> a;
			//return 1;
		}

    while(1){
      videoCapture.read(image);
      //image = cv_bridge::toCvShare(msg, "bgr8")->image;

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
      Scalar yellow_lower(15, 140, 70);
      Scalar yellow_upper(45, 255, 255);
      Scalar white_lower(0, 150, 0);
      Scalar white_upper(180, 255, 255);
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
      imageMorphologicalGradient(result, result);
      cannyEdge(result, result, 100, 200);
      imageHoughLinesP(result, lines, 1.0, 1.0 * PI / 180.0 , 50, 10, 20);
      Mat blackLineImage;
      //convertColor(result, blackLineImage, COLOR_GRAY2BGR);
      blackLineImage = makeBlackImage(result, true);
      
      distance_result = lineFittingForPerspectiveImage(blackLineImage, blackLineImage, lines, Scalar(0, 0, 255), 10, 60.0*PI/180.0);
      cout << distance_result << endl;
      imagePerspectiveTransformation(blackLineImage, result, dst_pts, src_pts, Size());
    //  result = result + image;
  //    overlayToImage(result, blackLineImage, result, 0.2, 0.2);
    

      // result //
      result = image + result;
/**/
  
      cv::imshow("view", result);
      cv::waitKey(30);
    }
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
    if(distance_result < 0 )
      msg.acc_cmd  = 2;   // right
    if(distance_result > 0 )
      msg.acc_cmd  = 2;   // left
                       

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
  cv::startWindowThread();
  image_transport::ImageTransport it(nh);
//  image_transport::Subscriber sub = it.subscribe("/usb_cam/image_raw", 1, imageCallback);	// subscribe(topic name)
  image_transport::Subscriber sub = it.subscribe("/camera/image", 1, imageCallback);	// subscribe(topic name)

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
