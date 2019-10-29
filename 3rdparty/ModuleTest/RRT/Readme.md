>## Install all required packages

>#### $ sudo apt-get install ros-kinetic-gmapping ros-kinetic-navigation ros-kinetic-kobuki ros-kinetic-kobuki-core ros-kinetic-kobuki-gazebo

>#### $ sudo apt-get install python-opencv python-numpy python-scikits-learn

>#### $ cd ~/catkin_ws/src/
>#### $ git clone https://github.com/hasauino/rrt_exploration.git
>#### $ git clone https://github.com/hasauino/rrt_exploration_tutorials.git
>#### $ cd ~/catkin_ws
>#### $ catkin_make

>## Start Exploration

>#### roslaunch rrt_exploration_tutorials single_simulated_house.launch

>#### roslaunch rrt_exploration single.launch

>### How to use
>#### When defining the rectangular region for exploration, the sequence of points is important. The sequence is as follows: top-left corner, bottom-left corner, bottom-right corner, top right corner, and finally the initiation point. Initiation point can be chosen anywhere within the known area (white area in the occupancy grid).


>### Reference

>#### http://wiki.ros.org/rrt_exploration/Tutorials
>#### http://wiki.ros.org/rrt_exploration/Tutorials/singleRobot
