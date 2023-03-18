/**
 * Subscribes to the following topics: 
 *   controlEffortLinearX
 *   controlEffortLinearY
 *   controlEffortLinearZ
 *   controlEffortAngularX
 *   controlEffortAngularY
 *   controlEffortAngularZ
 * Publishes a geometry_msgs::Twist message to: 
 *   controlEffort
 */

#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <geometry_msgs/Twist.h>
#include <iostream>

geometry_msgs::Twist output;

void callbackLinearX(const std_msgs::Float64& value) {
  output.linear.x = value.data;
}

void callbackLinearY(const std_msgs::Float64& value) {
  output.linear.y = value.data;
}

void callbackLinearZ(const std_msgs::Float64& value) {
  output.linear.z = value.data;
}

void callbackAngularX(const std_msgs::Float64& value) {
  output.angular.x = value.data;
}

void callbackAngularY(const std_msgs::Float64& value) {
  output.angular.y = value.data;
}
void callbackAngularZ(const std_msgs::Float64& value) {
  output.angular.z = value.data;
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "PID Combiner");
  ros::NodeHandle handle;
  
  ros::Subscriber linearX = handle.subscribe("controlEffortLinearX", 1, callbackLinearX);
  ros::Subscriber linearY = handle.subscribe("controlEffortLinearY", 1, callbackLinearY);
  ros::Subscriber linearZ = handle.subscribe("controlEffortLinearZ", 1, callbackLinearZ);
  ros::Subscriber angularX = handle.subscribe("controlEffortAngularX", 1, callbackAngularX);
  ros::Subscriber angularY = handle.subscribe("controlEffortAngularY", 1, callbackAngularY);
  ros::Subscriber angularZ = handle.subscribe("controlEffortAngularZ", 1, callbackAngularZ);
  
  ros::Publisher control = handle.advertise<geometry_msgs::Twist>("controlEffort", 1);

  while(ros::ok()) {
    control.publish(output);
    ros::spinOnce();
  }

  return 0;
}
