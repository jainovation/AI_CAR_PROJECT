#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void convertColor(Mat &image, Mat &result, int flag)
{
    cvtColor(image, result, flag);
    return;
}

Mat imageCopy(Mat &image)
{
    Mat result;
    image.copyTo(result);
    return result;
}

void drawLine(Mat &image, Mat &result, Point pt1, Point pt2, Scalar color, int thickness) 
{
    result = imageCopy(image);
    line(result, pt1, pt2, color, thickness);
    return;
}

void imageHoughCircles(Mat &image, vector<Vec3f> &circles, int method, double dp, double minDist, double canny, double threshold, double minRadius, double maxRadius)
{
    cv::HoughCircles(image, circles, method, dp, minDist, canny, threshold, minRadius, maxRadius);
    return;
}
void drawHoughCircles(Mat &image, Mat &result, vector<Vec3f> &circles)
{
    result = imageCopy(image);
    if (circles.size() == 0)
        return;
    for (size_t i = 0 ; i < circles.size(); i++)
    {
        Vec3i c = circles[i];
        Point center = Point(c[0], c[1]);
        int radius = c[2];
        cv::circle(result, center, 2, Scalar(0, 0, 255), -1);
        cv::circle(result, center, radius, Scalar(0, 255, 0), 2);
    } 
    return;
}

int main(int argc, char** argv)
{
	cv::Mat image, image_gray, result;
	image = imread("/home/nvidia/Desktop/traffic_light.png",IMREAD_COLOR);	

	cvtColor(image, image_gray, CV_BGR2GRAY ); 
	/* find circle */
	vector<Vec3f> circles;
	cv::HoughCircles(image_gray, circles, CV_HOUGH_GRADIENT, 1, 20, 50, 35, 30, 100); 
	drawHoughCircles(image, image, circles);

	Scalar red_lower(25, 0, 150); // BGR
	Scalar red_upper(80, 80, 255);
	
	Scalar green_lower(10, 100, 10);
	Scalar green_upper(110, 254, 90);

	for(int i=0; i<circles.size(); i++){

		vector<Point> src_pts, dst_pts;

		src_pts.push_back(Point(circles[i][0]-circles[i][2], circles[i][1]-circles[i][2]));
		src_pts.push_back(Point(circles[i][0]+circles[i][2], circles[i][1]-circles[i][2]));
		src_pts.push_back(Point(circles[i][0]-circles[i][2], circles[i][1]+circles[i][2]));
		src_pts.push_back(Point(circles[i][0]+circles[i][2], circles[i][1]+circles[i][2]));

		/*Point pt1 = src_pts[0];
		Point pt2 = src_pts[1];
		Point pt3 = src_pts[2];
		Point pt4 = src_pts[3];
		Scalar Color(255,0,0);
		drawLine(image, image, pt1, pt2, Color, 5);
		drawLine(image, image, pt2, pt4, Color, 5);
		drawLine(image, image, pt3, pt4, Color, 5);
		drawLine(image, image, pt1, pt3, Color, 5);
		*/
		Mat mask2;
		//convertColor(image, mask2, COLOR_BGR2HLS);
		
		//white_image = imageCopy(mask2);
		//cv::imshow("Image",image);
	
	}
	inRange(image, red_lower, red_upper, result);
	//inRange(image, green_lower, green_upper, image);
	cv::imshow("Image",result);

	int iWhitePixel = 0;
	for (int x = 0; x < result.rows; x++){
		for (int y = 0; y < result.cols; y++){
			if (result.at<int>(x, y) == 255)     // white : 255
				iWhitePixel++;
		}
	}
	cout<<"pixel : "<<iWhitePixel<<endl;
	float circle = circles[1][2]*circles[1][2]*3.14;
	cout<<"circle : "<< circle << endl;	

	waitKey(0);


	return 0;

}
