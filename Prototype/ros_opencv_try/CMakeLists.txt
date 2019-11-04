cmake_minimum_required(VERSION 2.8.3)
project(ros_opencv_try)



find_package(catkin REQUIRED COMPONENTS
  roscpp

  std_msgs
  cv_bridge
  sensor_msgs
  image_transport
  message_generation
)

add_message_files(FILES MsgACC.msg)
generate_messages(DEPENDENCIES std_msgs)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenCV REQUIRED)



catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES ros_opencv_try
#  CATKIN_DEPENDS roscpp std_msgs
#  DEPENDS system_lib
CATKIN_DEPENDS message_runtime
)


include_directories(
 include
  ${OpenCV_INCLUDE_DIRS}
  ${catkin_INCLUDE_DIRS}
)


add_executable(${PROJECT_NAME}_node src/ros_opencv_cam.cpp)
add_dependencies(${PROJECT_NAME}_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
#target_link_libraries(${PROJECT_NAME}_node ${catkin_LIBRARIES})
target_link_libraries(${PROJECT_NAME}_node
   ${OpenCV_LIBRARIES}
   ${catkin_LIBRARIES}
 )


add_executable(opencv_subscriber src/opencv_subscriber.cpp)
add_dependencies(opencv_subscriber ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(opencv_subscriber
   ${OpenCV_LIBRARIES}
   ${catkin_LIBRARIES}
 )

add_executable(servoExample src/servoExample.cpp)
add_dependencies(servoExample ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(servoExample ${catkin_LIBRARIES} )
