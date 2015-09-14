#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Vector3.h>

ros::Publisher feedback_wheel_angularVel_pub;
ros::Subscriber cmd_wheel_angularVel_sub;
ros::Time current_time, last_time;

double wheelRadius = 0.0625;
double wheelSeparation = 0.22;
double omega_right = 0.0;
double omega_left = 0.0;

void cmd_wheel_angularVelCallback(const geometry_msgs::Vector3 &vector3)
{
  omega_left 	= vector3.x;
  omega_right  	= vector3.y;

}

int main(int argc, char** argv){
  ros::init(argc, argv, "mybot_loop");

  ros::NodeHandle n1, n2;
  feedback_wheel_angularVel_pub = n1.advertise<geometry_msgs::Vector3>("feedback_wheel_angularVel", 10);
  cmd_wheel_angularVel_sub = n2.subscribe("cmd_wheel_angularVel", 10, cmd_wheel_angularVelCallback);
  
  ros::Rate r(10.0); // rate for publishing odom
  while(n1.ok()){

    ros::spinOnce();               // check for incoming messages
    geometry_msgs::Vector3 vector3;
    vector3.x = omega_left;
    vector3.y = omega_right;

    //publish the message
    feedback_wheel_angularVel_pub.publish(vector3);

    r.sleep();
  }
}
