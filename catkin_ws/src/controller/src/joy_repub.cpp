#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/Joy.h"
#include <ros/time.h>

struct Joy_repub
{
    Joy_repub();
    ros::NodeHandle nh;
    ros::Publisher cmd_vel_pub;
    geometry_msgs::Twist cmd_vel_msg;
    ros::Subscriber joy_sub;
    void joyCallBack(const sensor_msgs::Joy::ConstPtr& twist_msg);
};

Joy_repub::Joy_repub()
{
    cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 10);
    joy_sub = nh.subscribe<sensor_msgs::Joy>("joy", 10, &Joy_repub::joyCallBack, this);
}

void Joy_repub::joyCallBack(const sensor_msgs::Joy::ConstPtr& joy_msg){
    cmd_vel_msg.linear.x = joy_msg->axes[4];
    cmd_vel_msg.linear.y = joy_msg->axes[3];
    cmd_vel_msg.linear.z = joy_msg->axes[1];
    cmd_vel_msg.angular.z = joy_msg->axes[0];

    cmd_vel_pub.publish(cmd_vel_msg);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "joy_repub");
    Joy_repub j;
    while (ros::ok())
    {
        ros::spinOnce();
        // Add a small sleep to avoid 100% CPU usage
        ros::Duration(0.001).sleep();
    }
}