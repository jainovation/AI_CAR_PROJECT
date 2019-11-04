#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>

#include "JHPWMPCA9685.h"
#include "JHPWMPCA9685.cpp"
#include <ros/ros.h>
#include "ros_opencv_try/MsgACC.h"

// Calibrated for a Robot Geek RGS-13 Servo
// Make sure these are appropriate for the servo being used!

#define THROTTLE_FULL_REVERSE 204 // 1ms/20ms * 4096
#define THROTTLE_NEUTRAL 307      // 1.5ms/20ms * 4096
#define THROTTLE_FULL_FORWARD 409 // 2ms/20ms * 4096

// The ESC is plugged into the following PWM channel
#define ESC_CHANNEL 1

// The Steering Servo is plugged into the follow PWM channel
#define STEERING_CHANNEL 0

using namespace std;

int stopDC = 307 ;
int servoMin = 250 ; //left
int servoMax = 430 ; //right
int angle = 340 ;
int speed = 307 ;

int number=0;

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

// Map an integer from one coordinate system to another
// This is used to map the servo values to degrees
// e.g. map(90,0,180,servoMin, servoMax)
// Maps 90 degrees to the servo value

int motorMap ( int x, int in_min, int in_max, int out_min, int out_max) 
{
    int toReturn =  (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min ;
    // For debugging:
    printf("MAPPED %d to: %d\n", x, toReturn);
    return toReturn ;
}

void msgCallback(const ros_opencv_try::MsgACC::ConstPtr& msg)
{
  //number = number+msg->acc_cmd;
  //ROS_INFO("recieve msg = %d", number);        // Prints the 'data' message
  
  ROS_INFO("recieve msg = %d", msg->acc_cmd);        // Prints the 'data' message
/*    
  if(msg->acc_cmd == 0)
    pca9685->setPWM(0,0,motorMap(90,0,180,servoMin, servoMax)) ; // Neutral
  else if(msg->acc_cmd == 1)
    pca9685->setPWM(0,0,servoMin) ; // left
  else if(msg->acc_cmd == 2)
    pca9685->setPWM(0,0,servoMax) ; // right
*/

   pca9685->setPWM(ESC_CHANNEL,0,285);
    usleep(500);    

  pca9685->setPWM(0,0,motorMap(msg->acc_cmd,0,180,servoMin, servoMax)) ; //
  usleep(500);  
}

void manualMode(const ros_opencv_try::MsgACC::ConstPtr& msg)
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
        case 100: // steering right
                pca9685->setPWM(0,0,servoMax) ;
                break;
        case 97: // steering left
                pca9685->setPWM(0,0,servoMin) ;
                break;
        case 120: /// steering neutral
                pca9685->setPWM(0,0,motorMap(90,0,180,servoMin, servoMax)) ;
                break;
    }
    cout << "\033[2J\033[1;1H";     // clear terminal
}


int main(int argc, char **argv) {
    
    ros::init(argc, argv, "subscriber");
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
    pca9685->setPWM(STEERING_CHANNEL,0,motorMap(90,0,180,servoMin, servoMax));
    sleep(1);
 //   pca9685->setPWM(ESC_CHANNEL,0,285);
   // sleep(1);    

    ros::Subscriber ros_tutorial_sub = nh.subscribe("logic_msg", 1, msgCallback);
    ros::spin();
    
}
