#include "ros/ros.h"
#include "gazebo_msgs/GetModelState.h"
#include "geometry_msgs/Pose.h"
#include "nav_msgs/Odometry.h"
#include "tf/transform_broadcaster.h"

int main(int argc, char** argv)
{
    ros::init(argc, argv, "tf_broadcaster_odom_footprint") ;
    ros::NodeHandle n ;
    ros::Rate loop_rate(10);
    
    static tf::TransformBroadcaster br ;
  
    tf::Transform transform ;

    while (ros::ok())
    {
        
        transform.setOrigin( tf::Vector3(0, 0, 0) ) ;
        tf::Quaternion q(0, 0, 0, 1) ;
        transform.setRotation(q) ;
        br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "odom", "base_footprint")) ;

        ros::spinOnce();
        loop_rate.sleep() ;
   }
   return 0;
}
