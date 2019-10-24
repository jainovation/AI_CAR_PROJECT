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

#define THROTTLE_FULL_REVERSE 204 // 1ms/20ms * 4096
#define THROTTLE_NEUTRAL 307      // 1.5ms/20ms * 4096
#define THROTTLE_FULL_FORWARD 409 // 2ms/20ms * 4096

// The ESC is plugged into the following PWM channel
#define ESC_CHANNEL 1

// The Steering Servo is plugged into the follow PWM channel
#define STEERING_CHANNEL 0

using namespace std;

int servoMid = 307 ;
int servoMin = 220 ; //left
int servoMax = 400 ; //right

PCA9685 *pca9685 = new PCA9685() ;
int err;

int getkey() {
    int character;
    struct termios orig_term_attr;
    struct termios new_term_attr;

    /* set the terminal to raw mode */
    tcgetattr(fileno(stdin), &orig_term_attr);
    memcpy(&new_term_attr, &orig_term_attr, sizeof(struct termios));
    new_term_attr.c_lflag &= ~(ECHO|ICANON);
    new_term_attr.c_cc[VTIME] = 0;
    new_term_attr.c_cc[VMIN] = 0;
    tcsetattr(fileno(stdin), TCSANOW, &new_term_attr);

    /* read a character from the stdin stream without blocking */
    /*   returns EOF (-1) if no character is available */
    character = fgetc(stdin);

    /* restore the original terminal attributes */
    tcsetattr(fileno(stdin), TCSANOW, &orig_term_attr);

    return character;
}

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
    cout<<"Bouding Boxes (xmin):" << msg->bounding_boxes[0].xmin <<endl;
    cout<<"Bouding Boxes (xmax):" << msg->bounding_boxes[0].xmax <<endl;
    cout<<"Bouding Boxes (ymin):" << msg->bounding_boxes[0].ymin <<endl;
    cout<<"Bouding Boxes (ymax):" << msg->bounding_boxes[0].ymax <<endl;
    cout << "\033[2J\033[1;1H";     // clear terminal
}

void carDetect(const darknet_ros_msgs::BoundingBoxes::ConstPtr& msg)
{
    
    
#if 0
//servo
    if(msg->bounding_boxes[0].Class == "car")
    {
        cout << "stop" << endl;
        cout << "stop" << endl;
        cout << "stop" << endl;
        cout << "stop" << endl;
        cout << "stop" << endl;
        cout << "stop" << endl;
        cout << "stop" << endl;
        pca9685->setPWM(0,0,motorMap(0,0,180,servoMin, servoMax)) ;
        sleep(2) ;
        pca9685->setPWM(0,0,motorMap(180,0,180,servoMin, servoMax));
        sleep(2) ; 
        pca9685->setPWM(0,0,motorMap(90,0,180,servoMin, servoMax));
        sleep(2) ;
    }
#endif
//dc
#if 1
    if(msg->bounding_boxes[0].Class == "car")
    {
        cout << "stop" << endl;
        cout << "stop" << endl;
        cout << "stop" << endl;
        cout << "stop" << endl;
        cout << "stop" << endl;
        cout << "stop" << endl;
        cout << "stop" << endl;
        pca9685->setPWM(ESC_CHANNEL,0,THROTTLE_NEUTRAL);
        sleep(2);
    }
#endif
    cout << "\033[2J\033[1;1H";     // clear terminal
}

void manualMode(const darknet_ros_msgs::BoundingBoxes::ConstPtr& msg)
{
    
    int iKeyValue = getkey();
    switch(iKeyValue)
    {
        case 119://forward
                pca9685->setPWM(1,0,280) ;
                break;
        case 115://backward
                pca9685->setPWM(1,0,307) ;
                break;
        case 100:
                pca9685->setPWM(0,0,servoMax) ;
                break;
        case 97:
                pca9685->setPWM(0,0,servoMin) ;
                break;
        case 120:
                pca9685->setPWM(0,0,motorMap(90,0,180,servoMin, servoMax)) ;
                break;
    }
    cout << "\033[2J\033[1;1H";     // clear terminal
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "obj_subscriber");
    ros::NodeHandle nh;
    
    err = pca9685->openPCA9685();
    if (err < 0){
        printf("Error: %d", pca9685->error);
    }
    else
    {
        printf("PCA9685 Device Address: 0x%02X\n",pca9685->kI2CAddress) ;
        pca9685->setAllPWM(0,0) ;
        pca9685->reset() ;
        pca9685->setPWMFrequency(50) ;
    }
    // Set the PWM to "neutral" (1.5ms)
    sleep(1);
    pca9685->setPWM(ESC_CHANNEL,0,THROTTLE_NEUTRAL);
    sleep(1);
    pca9685->setPWM(ESC_CHANNEL,0,280);
   
    //ros::Subscriber cood_sub = nh.subscribe("/darknet_ros/bounding_boxes",100,msgCallback);
    ros::Subscriber cood_sub2 = nh.subscribe("/darknet_ros/bounding_boxes",100,carDetect);
    ros::Subscriber cood_sub3 = nh.subscribe("/darknet_ros/bounding_boxes",100,manualMode);
    
    ros::spin();
    
    //pca9685->closePCA9685();
    
    return 0;
}

