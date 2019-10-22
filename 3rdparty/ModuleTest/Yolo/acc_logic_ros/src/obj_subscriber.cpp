#include "ros/ros.h"
#include "ros/ros.h"
#include "darknet_ros_msgs/BoundingBoxes.h"
#include "darknet_ros_msgs/BoundingBox.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include "JHPWMPCA9685.h"
#include "JHPWMPCA9685.cpp"

using namespace std;

int servoMin = 120 ;
int servoMax = 720 ;

PCA9685 *pca9685 = new PCA9685() ;
int err;

int motorMap ( int x, int in_min, int in_max, int out_min, int out_max) 
{
    int toReturn =  (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min ;
    // For debugging:
    printf("MAPPED %d to: %d\n", x, toReturn);
    return toReturn ;
}

void msgCallback(const darknet_ros_msgs::BoundingBoxes::ConstPtr& msg)
{
    cout<<"Bouding Boxes (header):" << msg->header <<endl;
    cout<<"Bouding Boxes (image_header):" << msg->image_header <<endl;
    cout<<"Bouding Boxes (Class):" << msg->bounding_boxes[0].Class <<endl;
    //cout<<"Bouding Boxes (xmin):" << msg->bounding_boxes[0].xmin <<endl;
    //cout<<"Bouding Boxes (xmax):" << msg->bounding_boxes[0].xmax <<endl;
    //cout<<"Bouding Boxes (ymin):" << msg->bounding_boxes[0].ymin <<endl;
    //cout<<"Bouding Boxes (ymax):" << msg->bounding_boxes[0].ymax <<endl;
    cout << "\033[2J\033[1;1H";     // clear terminal
}

void carDetect(const darknet_ros_msgs::BoundingBoxes::ConstPtr& msg)
{
    //cout<<"Bouding Boxes (header):" << msg->header <<endl;
    //cout<<"Bouding Boxes (image_header):" << msg->image_header <<endl;
    //cout<<"Bouding Boxes (Class):" << msg->bounding_boxes[0].Class <<endl;
    //cout<<"Bouding Boxes (xmin):" << msg->bounding_boxes[0].xmin <<endl;
    //cout<<"Bouding Boxes (xmax):" << msg->bounding_boxes[0].xmax <<endl;
    //cout<<"Bouding Boxes (ymin):" << msg->bounding_boxes[0].ymin <<endl;
    //cout<<"Bouding Boxes (ymax):" << msg->bounding_boxes[0].ymax <<endl;
    if(msg->bounding_boxes[0].Class == "car")
    {
        cout << "stop" << endl;
        cout << "stop" << endl;
        cout << "stop" << endl;
        cout << "stop" << endl;
        cout << "stop" << endl;
        cout << "stop" << endl;
        cout << "stop" << endl;
        pca9685->setPWM(0,0,servoMin) ;
        //pca9685->setPWM(1,0,servoMin) ;

        sleep(2) ;
        pca9685->setPWM(0,0,servoMax);
        sleep(2) ; 
        pca9685->setPWM(0,0,motorMap(90,0,180,servoMin, servoMax));
        sleep(2) ;
    }
    cout << "\033[2J\033[1;1H";     // clear terminal
}

int main(int argc, char **argv)
{
    err = pca9685->openPCA9685();
    if (err < 0){
        printf("Error: %d", pca9685->error);
    }
    else
    {
        printf("PCA9685 Device Address: 0x%02X\n",pca9685->kI2CAddress) ;
        pca9685->setAllPWM(0,0) ;
        pca9685->reset() ;
        pca9685->setPWMFrequency(60) ;
    }
    
    ros::init(argc, argv, "obj_subscriber");
    ros::NodeHandle nh;
    //ros::Subscriber cood_sub = nh.subscribe("/darknet_ros/bounding_boxes",100,msgCallback);
    ros::Subscriber cood_sub2 = nh.subscribe("/darknet_ros/bounding_boxes",100,carDetect);
    
    ros::spin();

    return 0;
}

