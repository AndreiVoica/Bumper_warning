#include <ros/ros.h>
#include <kobuki_msgs/BumperEvent.h>
#include <kobuki_msgs/CliffEvent.h>
#include <kobuki_msgs/MotorPower.h>
#include "geometry_msgs/Twist.h"
#include <sys/types.h>
#include <signal.h>


ros::Subscriber sub_bumper;
ros::Subscriber sub_cliff;
ros::Subscriber sub_teleop;
ros::Publisher cmd_vel_pub;
ros::Subscriber MotorPower;


void clbk_bumper(const kobuki_msgs::BumperEvent::ConstPtr& msg){
  if(msg->bumper == 1){
    ROS_INFO("Center bumper activated, move back");
    system("/home/ros/ros_ws/src/bumper_warning/src/script.sh");
  }
  else if(msg->bumper == 0){
    ROS_INFO("Left bumper activated, turn right");
    system("/home/ros/ros_ws/src/bumper_warning/src/script.sh");
  }
  else if(msg->bumper == 2){
    ROS_INFO("Right bumper activated, turn left");
    system("/home/ros/ros_ws/src/bumper_warning/src/script.sh");
  }
  geometry_msgs::Twist msgvel;
  msgvel.linear.x = -10.0;
  msgvel.linear.y = -10.0;
  cmd_vel_pub.publish(msgvel);

  ros::Duration(1.0).sleep();
}



void clbk_cliff(const kobuki_msgs::CliffEvent::ConstPtr& asd){
  //sub_teleop.shutdown();
  ROS_INFO("Cliff detected, move back!");
}


int main(int argc, char **argv){

  ros::init(argc, argv, "bumper_warning");
  ros::NodeHandle n;

  sub_bumper = n.subscribe("/mobile_base/events/bumper", 1, clbk_bumper);

  sub_cliff = n.subscribe("/mobile_base/events/cliff", 10, clbk_cliff);


  cmd_vel_pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);
  //sub_teleop = n.subscribe("/cmd_vel_mux/input/teleop", 10, )



  ros::spin();
}
