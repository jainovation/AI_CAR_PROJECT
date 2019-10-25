#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <boost/asio.hpp>
#include <hls_lfcd_lds_driver/lfcd_laser.h>

#define RAD2DEG(x) ((x)*180./M_PI)

using namespace std;

char checkDirection(int i)
{
	if((0 < i) && (i < 10))
		return 'F';
	else if((85 < i) && (i < 95))
		return 'R';
	else if((175 < i) && (i < 185))
		return 'B';
	else if((265) < i) && (i < 275))
		return 'L';
}
void msgCallback(const sensor_msgs::LaserScan::Ptr& scan)
{
	float cnt = scan->scan_time / scan->time_increment;
	char Dir;

	for(int i = 0; i < 360; i++)
	{
		if((i > 0) && (i < 10))
		{
			ROS_INFO("DIRECTION: FRONT");
			if(scan->ranges[i] < 0.1)
				ROS_INFO("stop -> range[%d]: %lf",i,scan->ranges[i]);
			else
				ROS_INFO("Don't stop -> range[%d]: %lf",i,scan->ranges[i]);
		}
		if((i > 175) && (i < 185))
		{
			ROS_INFO("DIRECTION: BACK");
			if(scan->ranges[i] == 0)
				ROS_INFO("I can't detect");
			else if(scan->ranges[i] < 0.1)
				ROS_INFO("stop -> range[%d]: %lf",i,scan->ranges[i]);
			else
				ROS_INFO("Don't stop -> range[%d]: %lf",i,scan->ranges[i]);
		}
	}
	cout << "\033[2J\033[1;1H";
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "hls_laser_subscriber");
	ros::NodeHandle nh;

	ros::Subscriber hls_laser_sub = nh.subscribe("scan", 1000, msgCallback);
	ros::spin();

	return 0;
}
