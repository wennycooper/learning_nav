# learning_nav

# Installation 
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

        rosrun learning_nav tf_broadster

* run slam

        rosrun gmapping slam_gmapping scan:=/pioneer/laser/scan

* launch rviz

        roslaunch learning_nav display.launch   

# Bugs

* Sent a Goal but didn't see any message on /cmd_vel topic

