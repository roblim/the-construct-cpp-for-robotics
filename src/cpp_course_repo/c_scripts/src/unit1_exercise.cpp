#include "rosbot_control/rosbot_class.h"
#include <iostream>
#include <list>
#include <map>
#include <ros/ros.h>
#include <string>

using namespace std;

int main(int argc, char **argv) {
  ros::init(argc, argv, "rosbot_node");

  RosbotClass rosbot;
  rosbot.move();

  map<double, float> x_pos_map;
  float x_coordinate;
  double time;

  for (int i = 0; i < 10; i++) {
    x_coordinate = rosbot.get_position(1);
    time = rosbot.get_time();
    x_pos_map[time] = x_coordinate;
    rosbot.move();
  }

  for (auto x_pos : x_pos_map) {
    ROS_INFO_STREAM("x position at time " << x_pos.first << " was "
                                          << x_pos.second << "\n");
  }

  return 0;
}