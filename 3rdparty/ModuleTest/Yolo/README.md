TEST
This is darknet ROS for Nvidia Jetson.

$ roscore

$ rosrun usb_cam usb_cam_node /usb_cam/image_raw:=/camera/image_raw

$ roslaunch darknet_ros darknet_ros.launch

$ rosrun rqt_graph rqt_graph

##If you have error or not fonund, you input next code
$ source ~/catkin_ws/devel/setup.bash

##if error while decoding frame, you input once next code
$ roslaunch usb_cam usb_cam-test.launch
