# learning_nav

* This is a project to learn ROS navigation stack.
* The goal is to build a robot with URDF, running it in gazebo with laser range sensor, and be able to move to a specified goal autonomously.


# Installation 
* git clone this project into your catkin_ws/src
* cd to catkin_ws
* catkin_make

# Execution

Open terminals to run following commands in-sequencial

* launch gazebo and spawn a robot

        # roslaunch learning_nav gazebo.launch

* run slam_gmapping

        # rosrun gmapping slam_gmapping scan:=/pioneer/laser/scan

* launch rviz, joint_state_publisher and robot_state_publisher 

        # roslaunch learning_nav display.launch   

* run my_base_controller to serve /cmd_vel

        $ rosrun learning_nav mybot_base_controller

* run my_loop
 
        $ rosrun learning_nav mybot_loop

* run my_odometry

        $ rosrun learning_nav mybot_odometry

* run move_base to serve move-to-a-goal

        $ roslaunch learning_nav fake_move_base.launch

        
        
# BUGS

* Currently, there is problem in move-to-a-goal. It looks like localization causes problems 


