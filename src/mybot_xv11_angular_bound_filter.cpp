#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <iostream>
using namespace std;

ros::Publisher filtered_scan_pub;
ros::Subscriber input_scan_sub;
sensor_msgs::LaserScan filtered_scan;

bool my_update(const sensor_msgs::LaserScan& input_scan)
{
  
  filtered_scan.ranges.resize(input_scan.ranges.size());
  filtered_scan.intensities.resize(input_scan.intensities.size());

  ros::Time start_time = input_scan.header.stamp;
  unsigned int count = 0;

  //loop through the scan and truncate the beginning and the end of the scan as necessary
  for (unsigned int i = 270; i < 360; ++i) {
    filtered_scan.ranges[count] = input_scan.ranges[i];
    filtered_scan.intensities[count] = input_scan.intensities[i];
    ++count;
  }

  for (unsigned int i = 0; i < 90; ++i) {
    filtered_scan.ranges[count] = input_scan.ranges[i];
    filtered_scan.intensities[count] = input_scan.intensities[i];
    ++count;
  }
 
  //make sure to set all the needed fields on the filtered scan
  filtered_scan.header.frame_id = input_scan.header.frame_id;
  filtered_scan.header.stamp = start_time;
  filtered_scan.angle_min = -1.57;
  filtered_scan.angle_max = 1.57;
  filtered_scan.angle_increment = input_scan.angle_increment;
  filtered_scan.time_increment = input_scan.time_increment;
  filtered_scan.scan_time = input_scan.scan_time;
  filtered_scan.range_min = input_scan.range_min;
  filtered_scan.range_max = input_scan.range_max;
 
  filtered_scan.ranges.resize(count);
  filtered_scan.intensities.resize(count);

  //ROS_DEBUG("Filtered out %d points from the laser scan.", (int)input_scan.ranges.size() - (int)count);
  return true;
}

void input_scan_sub_callback(const sensor_msgs::LaserScan& input_scan)
{
  my_update(input_scan);
  filtered_scan_pub.publish(filtered_scan);

}


int main(int argc, char** argv){
  ros::init(argc, argv, "mybot_xv11_angular_bound_filter");
  ros::NodeHandle n1, n2;
  input_scan_sub = n1.subscribe("/xv11_scan", 10, input_scan_sub_callback);
  filtered_scan_pub = n2.advertise<sensor_msgs::LaserScan>("/xv11_scan_filtered", 50);
  ros::Rate loop_rate(50);

  while(ros::ok())
  {
    ros::spinOnce();
    loop_rate.sleep();
  }
}


