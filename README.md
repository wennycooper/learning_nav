# learning_nav

* This is a project to learn ROS navigation stack.
* The goal is to build a robot in gazebo which be able to move to a specified goal autonomously. 

# Installation 
* Follow this document

        http://web.engr.oregonstate.edu/~chungje/Code/Pioneer3dx%20simulation/ros-indigo-gazebo2-pioneer.pdf

* git clone this project into your catkin_ws/src
* cd to catkin_ws
* catkin_make

# Execution

Open 5 terminals to run following commands in-sequencial

* launch gazebo with robot and map

        roslaunch learning_nav gazebo.launch

* launch navigation move_base node

        roslaunch learning_nav move_base.launch

* run tf_broadcaster for odom->base_footprint

        rosrun learning_nav tf_broadcaster

* run slam

        rosrun gmapping slam_gmapping scan:=/pioneer/laser/scan

* launch rviz

        roslaunch learning_nav display.launch   

# TODOs

* base_controller to process /cmd_vel topic
* odom_publisher to report odometry info 

