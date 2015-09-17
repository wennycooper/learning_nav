#include <stdio.h>
#include <stdlib.h>
#include <ros/ros.h>
#include <unistd.h>

int main(int argc, char** argv){
  int seconds;
  ros::init(argc, argv, "sleep_seconds");

  if (argc != 2) {
    printf("sleep_seconds <num_seconds>\n");
    exit;
  }

  seconds = atoi(argv[1]);

  printf("sleep for %d seconds... \n", seconds);

  sleep(seconds);
}
