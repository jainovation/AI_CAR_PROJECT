#include "OpenCV_Functions.h"
#include <string>
/*void imageProcessing(Mat &image, Mat &result)
{
    result = imageCopy(image);
    return;
}
*/

void imageProcessing(Mat &image, Mat &result)
{
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

    //result = imageCopy(result2);
    return;
}


string path_to_images(void)
{   
    string road_image_01 = "/home/opencv-mds/OpenCV_in_Ubuntu/Data/Lane_Detection_Images/solidWhiteCurve.jpg";
    string road_image_02 = "/home/opencv-mds/OpenCV_in_Ubuntu/Data/Lane_Detection_Images/solidWhiteRight.jpg";
    string road_image_03 = "/home/opencv-mds/OpenCV_in_Ubuntu/Data/Lane_Detection_Images/solidYellowCurve.jpg";
    string road_image_04 = "/home/opencv-mds/OpenCV_in_Ubuntu/Data/Lane_Detection_Images/solidYellowCurve2.jpg";
    string road_image_05 = "/home/opencv-mds/OpenCV_in_Ubuntu/Data/Lane_Detection_Images/solidYellowLeft.jpg";
    string road_image_06 = "/home/opencv-mds/OpenCV_in_Ubuntu/Data/Lane_Detection_Images/whiteCarLaneSwitch.jpg";

    string traffic_image_01 = "/home/opencv-mds/OpenCV_in_Ubuntu/Data/TrafficLight_Detection/green_light_01.png";
    string traffic_image_02 = "/home/opencv-mds/OpenCV_in_Ubuntu/Data/TrafficLight_Detection/green_light_02.png";
    string traffic_image_03 = "/home/opencv-mds/OpenCV_in_Ubuntu/Data/TrafficLight_Detection/red_light_01.png";
    string traffic_image_04 = "/home/opencv-mds/OpenCV_in_Ubuntu/Data/TrafficLight_Detection/red_light_02.png";
    string traffic_image_05 = "/home/opencv-mds/OpenCV_in_Ubuntu/Data/TrafficLight_Detection/yellow_light_01.png";
    string traffic_image_06 = "/home/opencv-mds/OpenCV_in_Ubuntu/Data/TrafficLight_Detection/yellow_light_02.png";
    return road_image_01;
}
void processingSingleImage(string imagePath, string outputPath)
{
    Mat image = imageRead(imagePath);
    imageShow("Opened Image", image);
    Mat result;
    imageProcessing(image, result);
    cout << "test" << endl;
    imageShow("Result Image", result);
    imageWrite(outputPath, result);
    return;
}
vector<string> imageList_LaneDetection(void)
{
    string path_to_project = "/home/opencv-mds/OpenCV_in_Ubuntu/";
    string path_to_data = path_to_project + "Data/";
    string path_to_road_image = path_to_data + "Lane_Detection_Images/";

    string road_image_01 = path_to_road_image + "solidWhiteCurve.jpg";
    string road_image_02 = path_to_road_image + "solidWhiteRight.jpg";
    string road_image_03 = path_to_road_image + "solidYellowCurve.jpg";
    string road_image_04 = path_to_road_image + "solidYellowCurve2.jpg";
    string road_image_05 = path_to_road_image + "solidYellowLeft.jpg";
    string road_image_06 = path_to_road_image + "whiteCarLaneSwitch.jpg";

    vector<string> images;
    images.push_back(road_image_01);
    images.push_back(road_image_02);
    images.push_back(road_image_03);
    images.push_back(road_image_04);
    images.push_back(road_image_05);
    images.push_back(road_image_06);
    return images;
}
vector<string> imageList_TrafficLightDetection(void)
{
    string path_to_project = "/home/opencv-mds/OpenCV_in_Ubuntu/";
    string path_to_data = path_to_project + "Data/";
    string path_to_road_image = path_to_data + "TrafficLight_Detection/";

    string image_01 = path_to_road_image + "green_light_01.png";
    string image_02 = path_to_road_image + "green_light_02.png";
    string image_03 = path_to_road_image + "red_light_01.png";
    string image_04 = path_to_road_image + "red_light_02.png";
    string image_05 = path_to_road_image + "yellow_light_01.png";
    string image_06 = path_to_road_image + "yellow_light_02.png";

    vector<string> images;
    images.push_back(image_01);
    images.push_back(image_02);
    images.push_back(image_03);
    images.push_back(image_04);
    images.push_back(image_05);
    images.push_back(image_06);
    return images;
}
/*
void processingMultipleImages(vector<string> list_of_images)
{
    int idx=0;
    for (string path : list_of_images)
    {
        Mat image = imageRead(path);
        imageShow("Image index is " + to_string(idx), image);
        Mat result;
        imageProcessing(image, result);
        imageShow("Result of index " + to_string(idx), result);
        imageWrite("Result_" + to_string(idx) + ".jpg", result);
        idx++;
    }
    return;
}
*/
string path_to_videos(void)
{
    string road_video_01 = "/home/opencv-mds/OpenCV_in_Ubuntu/Data/Lane_Detection_Videos/solidWhiteRight.mp4";
    string road_video_02 = "/home/opencv-mds/OpenCV_in_Ubuntu/Data/Lane_Detection_Videos/solidYellowLeft.mp4";
    return road_video_01;
}
void processingSingleVideo(string videoPath, string outputPath)
{
    Video(videoPath, outputPath);
    return;
}
vector<string> videoList_LaneDetection(void)
{
    string path_to_project = "/home/opencv-mds/OpenCV_in_Ubuntu/";
    string path_to_data = path_to_project + "Data/";
    string path_to_road_video = path_to_data + "Lane_Detection_Videos/";
    string road_video_01 = path_to_road_video + "solidWhiteRight.mp4";
    string road_video_02 = path_to_road_video + "solidYellowLeft.mp4";

    vector<string> videos;
    videos.push_back(road_video_01);
    videos.push_back(road_video_02);
    return videos;
}
/*
void processingMultipleVideos(vector<string> list_of_videos)
{
    int idx=0;
    for (string path : list_of_videos)
    {
        Video(path, "output_" + to_string(idx) + ".mp4");
        idx++;
    }
    return;
}
*/
