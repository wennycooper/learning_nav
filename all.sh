!/bin/bash

my_pid=$$
echo "My process ID is $my_pid"

#echo "Launching roscore..."
#roscore &
#pid=$!
#sleep 3s

echo "display.launch..."
roslaunch learning_nav display.launch &
pid="$pid $!"

sleep 3s

echo "fake_move_base_blank_map.launch..."
roslaunch learning_nav fake_move_base_map_with_obstacles.launch &
pid="$pid $!"

sleep 1s

echo "mybot_base_controller..."
rosrun learning_nav mybot_base_controller &
pid="$pid $!"

sleep 1s

echo "Launching mybot_loop..."
rosrun learning_nav mybot_loop &
pid="$pid $!"

sleep 1s
echo "Launching mybot_odometry..."
rosrun learning_nav mybot_odometry &
pid="$pid $!"

trap "echo Killing all processes.; kill -2 TERM $pid; exit" SIGINT SIGTERM

sleep 24h

