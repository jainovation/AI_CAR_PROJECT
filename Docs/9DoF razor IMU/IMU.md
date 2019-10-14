IMU_Software Installation
=========================
### 1. Arduino IDE Install
+  ####  ubuntu-make install
   - `$ sudo apt-add-repository ppa:ubuntu-desktop/ubuntu-make`
   - `$ sudo apt-get update`
   - `$ sudo apt-get install ubuntu-make`
+  #### Arduino IDE 최신 버전 Install
   - `$ sudo umake ide arduino`
+  #### tty 접근 가능하게 하기
   - `$ sudo usermod -aG dialout (아이디)`
+  #### 설정 적용을 위해 재부팅
   - `$ sudo reboot`

### 2. Visual Python Install(Required for the 3D visualization node)
   - `$ sudo apt-get install python-visual`

### 3. ROS 9DoF razor IMU Package install
+ #### Clone the ROS source repository and build it:
   - `$ cd catkin_ws/src`
   - `$ git clone https://github.com/KristofRobot/razor_imu_9dof.git`
   - `$ cd ../`
   - `$ catkin_make`
+ #### Install the razor_imu_9dof package from repository, e.g. for Kinetic:
   - `$ sudo apt-get install ros-indigo-razor-imu-9dof`

### 4. Load Firmware into Razor Board
+ #### Copy the Razor firmware from the razor_imu_9dof/src directory to your arduino source directory.
   - `$ roscd razor_imu_9dof`
   - `$ cp -r src/Razor_AHRS ~/Arduino`
   
### 5. Create Configuration File
+ #### Copy the template file razor.yaml:
   - `$ roscd razor_imu_9dof/config`
   - `$ cp razor.yaml my_razor.yaml`
     * Edit my_razor.yaml as needed. See further for more information on setting the calibration values.
     
### 6. Testing the AHRS & 3D Visualization Test GUI
+ #### Source uproad & View Serial Moniter (Arduino IDE)
+ #### 3D GUI launch file start
   - `$ roscore`
   - `$ roslaunch razor_imu_9dof razor-pub-and-display.launch`
   
### 7. Testing the rostopic
+ #### The normal way to start publishing Imu data from the Razor is to run the launch file:
   - `$ roscore`
   - `$ roslaunch razor_imu_9dof razor-pub.launch`
        * ###### List 안에 imu 확인
   - `$ rostopic list`
        * ###### imu data를 rostopic를 이용해 터미널 상에서 볼 수 있다.
   - `$ rostopic echo imu`




### 참조 링크
+ ##### ROS wiki: http://wiki.ros.org/razor_imu_9dof
+ ##### Arduino: https://www.arduino.cc/en/Guide/Linux
