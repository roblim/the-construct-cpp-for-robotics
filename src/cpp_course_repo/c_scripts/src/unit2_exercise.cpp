#include "rosbot_control/rosbot_class.h"
#include <iostream>
#include <list>
#include <map>
#include <ros/ros.h>
#include <string>

using namespace std;

int main(int argc, char **argv) {
  int counter = 0;
  while (counter < 9) {
    counter += 1;
    cout << "Count: " << counter << endl;
  }


  return 0;
}