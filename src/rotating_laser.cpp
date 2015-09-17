#include <ros/ros.h>
#include <std_msgs/Float64.h>

int main(int argc, char** argv){
  ros::init(argc, argv, "rotating_laser");

  ros::NodeHandle n;
  ros::Publisher laser_angle_pub = n.advertise<std_msgs::Float64>("/example3_robot/laser_position_controller/command", 50);

  float angle = 0.0;

  ros::Rate r(100.0);

  std_msgs::Float64 laser_angle;
  while(n.ok()){

    laser_angle.data = angle;
    angle  = angle + 6.28/720;

    laser_angle_pub.publish(laser_angle); 

    r.sleep();
  }
}

