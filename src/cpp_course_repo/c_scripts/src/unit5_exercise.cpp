#include "rosbot_control/rosbot_class.h"
#include <ros/ros.h>

#include <string>

using namespace std;

class MyRosbotClass : public RosbotClass { // DEFINE YOUR CLASS HERE
public:
  static constexpr float threshold = 1.80;
  float frontal_laser_distance;
  float laser_distance_45d;
  float laser_distance_315d;
  float l_laser_distance;
  float r_laser_distance;
  float rear_r_laser_distance;
  float rear_l_laser_distance;

  void set_laser_distances() {
    frontal_laser_distance = get_laser(0);
    cout << "Front distance: " << frontal_laser_distance << endl;
    laser_distance_45d = get_laser(90);
    cout << "45d distance: " << laser_distance_45d << endl;
    laser_distance_315d = get_laser(630);
    cout << "315d distance: " << laser_distance_315d << endl;
    l_laser_distance = get_laser(540);
    cout << "L distance: " << l_laser_distance << endl;
    r_laser_distance = get_laser(180);
    cout << "R distance: " << r_laser_distance << endl;
    rear_r_laser_distance = get_laser(270);
    cout << "Rear R distance: " << rear_r_laser_distance << endl;
    rear_l_laser_distance = get_laser(450);
    cout << "Rear L distance: " << rear_l_laser_distance << endl;
  }

  void obstacle_avoid() {
    set_laser_distances();

    while (frontal_laser_distance > threshold) {
      move_forward(1);
      set_laser_distances();
    }

    if (laser_distance_45d < laser_distance_315d) {
      while (frontal_laser_distance < threshold) {
        turn("counterclockwise", 1);
        set_laser_distances();
      }
    } else {
      while (frontal_laser_distance < threshold) {
        turn("clockwise", 1);
        set_laser_distances();
      }
    }

    while (!isnan(l_laser_distance) || !isnan(r_laser_distance)) {
      move_forward(1);
      set_laser_distances();
    }

    if (rear_l_laser_distance < rear_r_laser_distance) {
      turn("counterclockwise", 1);
    } else {
      turn("clockwise", 1);
    }
    set_laser_distances();

    while (frontal_laser_distance > threshold) {
      move_forward(1);
      set_laser_distances();
    }
  }
};

int main(int argc, char **argv) {
  ros::init(argc, argv, "Rosbot_move_node");
  MyRosbotClass cutie;
  cutie.obstacle_avoid();

  return 0;
}