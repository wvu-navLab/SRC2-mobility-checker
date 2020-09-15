#ifndef MOBILITY_CHECKER_H_
#define MOBILITY_CHECKER_H_

#include <ros/ros.h>
#include <ros/console.h>
#include "std_msgs/Int64.h"
#include <std_msgs/Bool.h>
#include <state_machine/SetMobility.h>



class MobilityChecker
{
public:
  MobilityChecker(ros::NodeHandle &);
  void mobility(bool flag);
  void mobilityCallback(const std_msgs::Int64::ConstPtr& msg);
  int flag_mobility = 1;
private:
  ros::Subscriber mobility_sub;
  ros::ServiceClient clt_setMobility_;
  ros::NodeHandle & nh_;

};
int main(int argc, char **argv);

#endif //MOBILITY_CHECKER_H_
