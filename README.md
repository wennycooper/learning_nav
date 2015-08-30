# learning_nav

* This is a project to learn ROS navigation stack.
* The goal is to build a robot in rviz which be able to move to a specified goal autonomously.
* without gazebo
* with a static blank_map.pgm

# Installation 
* Follow this document

        http://web.engr.oregonstate.edu/~chungje/Code/Pioneer3dx%20simulation/ros-indigo-gazebo2-pioneer.pdf

* git clone this project into your catkin_ws/src
* cd to catkin_ws
* catkin_make

# Execution

Open 3 terminals to run following commands in-sequencial

* launch map-server with a blank_map, run a static tf transform of map->odom and launch move_base

        roslaunch learning_nav fake_move_base_blank_map.launch



* launch rviz

        roslaunch learning_nav display.launch   

* launch our base_controller (it will also publish /odom and broadcast /odom->/base_footprint)

        rosrun learning_nav base_controller
        
# TODOs

* map with obstacles
* slam with localization
* 


