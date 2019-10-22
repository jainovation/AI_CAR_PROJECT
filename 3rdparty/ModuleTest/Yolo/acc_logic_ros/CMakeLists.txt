cmake_minimum_required(VERSION 2.8.3)
project(acc_logic_ros)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  message_generation
  roscpp
  std_msgs
  std_msgs
  darknet_ros
  darknet_ros_msgs
)

###################################
## catkin specific configuration ##
###################################
catkin_package(
  LIBRARIES acc_logic_ros
  CATKIN_DEPENDS roscpp std_msgs darknet_ros darknet_ros_msgs
)

###########
## Build ##
###########

link_directories(
  /usr/local/cuda/lib64
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${catkin_INCLUDE_DIRS}/include
  ${catkin_INCLUDE_DIRS}/src 
)

add_executable(obj_subscriber src/obj_subscriber.cpp)
add_dependencies(obj_subscriber ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(obj_subscriber
  cuda
  cudart
  cublas
  ${catkin_LIBRARIES}
)

