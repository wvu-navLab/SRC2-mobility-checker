#include <ros/ros.h>
#include <mobility_checker/mobility_checker.h>

MobilityChecker::MobilityChecker(ros::NodeHandle &nh) :nh_(nh)
{


  mobility_sub = nh_.subscribe("/state_machine/mobility_scout", 1, &MobilityChecker::mobilityCallback, this);
  clt_setMobility_ =nh_.serviceClient<state_machine::SetMobility>("/state_machine/mobility_service_scout");

}

void MobilityChecker::mobilityCallback(const std_msgs::Int64::ConstPtr& msg)
{
  flag_mobility = msg->data;
  if (flag_mobility) {
    ROS_WARN_ONCE("MC:MEssage Received from SF: Rover is traversing = %i",flag_mobility);
  }
  else {
    ROS_ERROR("MC:Rover is immobile, Sending stop command to state Machine!  = %i",flag_mobility);
    mobility(false);
  }
}

void MobilityChecker::mobility(bool flag)
{
  state_machine::SetMobility srv_set_mobility;
  srv_set_mobility.request.mobility  = flag;
  if (clt_setMobility_.call(srv_set_mobility))
  {
    ROS_INFO_STREAM("MC: Called mobility service. Flag is: " << flag);
  }
  else
  {
    ROS_ERROR(" Failed to call mobility service");
  }

}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "mobility_checker");
  ros::NodeHandle nh("");

  MobilityChecker mobility_checker(nh);

  ros::spin();

  return 0;
}
