#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Vector3.h>

double x = 0.0;
double y = 0.0;
double th = 0.0;

double vel_x = 0.0;
double omega_z = 0.0;

ros::Publisher odom_pub;
ros::Subscriber feedback_wheel_angularVel_sub;
ros::Time current_time, last_time;

double wheelRadius = 0.0625;
double wheelSeparation = 0.22;
double omega_right = 0.0;
double omega_left = 0.0;

void feedback_wheel_angularVelCallback(const geometry_msgs::Vector3 &vector3)
{
  omega_left = vector3.x;
  omega_right  = vector3.y;

  //printf("[KKUEI] Omega_left=%f, Omega_right=%f\n", omega_left, omega_right);

  current_time = ros::Time::now();

  //compute odometry in a typical way given the velocities of the robot

  vel_x = wheelRadius * (omega_right + omega_left) / 2;
  omega_z = wheelRadius * (omega_right - omega_left) / wheelSeparation;

  //printf("[KKUEI] vel_x=%f, omega_z=%f\n", vel_x, omega_z);

  current_time = ros::Time::now(); 
  double dt = (current_time - last_time).toSec();
  last_time = current_time;

  double delta_x = vel_x * cos(th) * dt;
  double delta_y = vel_x * sin(th) * dt;
  double delta_th = omega_z * dt;
   
  x += delta_x;
  y += delta_y;
  th += delta_th;

  // tf_transform
  // odom publisher
}

int main(int argc, char** argv){
  ros::init(argc, argv, "mybot_odometry");

  ros::NodeHandle n1, n2;
  odom_pub = n1.advertise<nav_msgs::Odometry>("odom", 50);
  feedback_wheel_angularVel_sub = n2.subscribe("feedback_wheel_angularVel", 10, feedback_wheel_angularVelCallback);
  
  tf::TransformBroadcaster odom_broadcaster;

  current_time = ros::Time::now();
  last_time = ros::Time::now();

  ros::Rate r(10.0); // rate for publishing odom
  while(n1.ok()){

    ros::spinOnce();               // check for incoming messages

    geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(th);

    //first, we'll publish the transform over tf
    geometry_msgs::TransformStamped odom_trans;
    odom_trans.header.stamp = current_time;
    odom_trans.header.frame_id = "odom";
    odom_trans.child_frame_id = "base_footprint";

    odom_trans.transform.translation.x = x;
    odom_trans.transform.translation.y = y;
    odom_trans.transform.translation.z = 0.0;
    odom_trans.transform.rotation = odom_quat;

    //send the transform
    odom_broadcaster.sendTransform(odom_trans);


    //next, we'll publish the odometry message over ROS
    nav_msgs::Odometry odom;
    odom.header.stamp = current_time;
    odom.header.frame_id = "odom";

    //set the position
    odom.pose.pose.position.x = x;
    odom.pose.pose.position.y = y;
    odom.pose.pose.position.z = 0.0;
    odom.pose.pose.orientation = odom_quat;

    //set the velocity
    odom.child_frame_id = "base_footprint";
    odom.twist.twist.linear.x = vel_x;
    odom.twist.twist.linear.y = 0.0;
    odom.twist.twist.angular.z = omega_z;

    //publish the message
    odom_pub.publish(odom);

    r.sleep();
  }
}
