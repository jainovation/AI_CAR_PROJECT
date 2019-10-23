OpenCV in ROS
====
가제보 연동하여 캠 설정
- roscore
- roslaunch turtlebot3_gazebo turtlebot3_autorace.launch
- //ros_opencv_try파일에 있는 코드 활용 , rostopic으로 소스코드안에 있는 subscribe 경로 수정해야함.
- catkin_make
- rosrun ros_opencv_try opencv_subscriber
- //추가로 조작하기 위해 다음과 같이 설정
- export TURTLEBOT3_MODEL=burger
-  . devel/setup.bash
- roslaunch turtlebot3_teleop turtlebot3_teleop_key.launch

