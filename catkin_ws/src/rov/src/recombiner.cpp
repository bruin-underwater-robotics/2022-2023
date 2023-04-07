#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/Float64.h"

using geometry_msgs::Twist;
using std_msgs::Float64;

struct Combiner
{
    Combiner();
    void roll_callback(const Float64::ConstPtr &roll_msg);
    void pitch_callback(const Float64::ConstPtr &pitch_msg);
    void yaw_callback(const Float64::ConstPtr &yaw_msg);
    void x_callback(const Float64::ConstPtr &x_msg);
    void y_callback(const Float64::ConstPtr &y_msg);
    void z_callback(const Float64::ConstPtr &z_msg);
    void cmd_vel_callback(const Twist::ConstPtr &cmd_vel_msg);
    ros::NodeHandle nh;
    ros::Publisher cmd_vel_pid_pub;
    geometry_msgs::Twist cmd_vel_pid_msg;
    ros::Subscriber roll_sub;
    ros::Subscriber pitch_sub;
    ros::Subscriber yaw_sub;
    ros::Subscriber x_sub;
    ros::Subscriber y_sub;
    ros::Subscriber z_sub;
    ros::Subscriber cmd_vel_sub;

};

Combiner::Combiner()
{
    roll_sub = nh.subscribe<Float64>("roll_pid", 1, &Combiner::roll_callback, this);
    pitch_sub = nh.subscribe<Float64>("pitch", 1, &Combiner::pitch_callback, this);
    yaw_sub = nh.subscribe<Float64>("yaw", 1, &Combiner::yaw_callback, this);
    x_sub = nh.subscribe<Float64>("x", 1, &Combiner::x_callback, this);
    y_sub = nh.subscribe<Float64>("y", 1, &Combiner::y_callback, this);
    z_sub = nh.subscribe<Float64>("z", 1, &Combiner::z_callback, this);
    cmd_vel_sub = nh.subscribe<Twist>("cmd_vel", 1, &Combiner::cmd_vel_callback, this);

    cmd_vel_pid_pub = nh.advertise<geometry_msgs::Twist>("cmd_vel_pid", 1);
}

void Combiner::roll_callback(const Float64::ConstPtr &roll_msg)
{
    cmd_vel_pid_msg.angular.x = roll_msg->data/360;
}
void Combiner::pitch_callback(const Float64::ConstPtr &pitch_msg)
{
    cmd_vel_pid_msg.angular.y = pitch_msg->data/360;
}
void Combiner::yaw_callback(const Float64::ConstPtr &yaw_msg)
{
    cmd_vel_pid_msg.angular.z = yaw_msg->data/360;
}
void Combiner::x_callback(const Float64::ConstPtr &x_msg)
{
    cmd_vel_pid_msg.linear.x = x_msg->data;
}
void Combiner::y_callback(const Float64::ConstPtr &y_msg)
{
    cmd_vel_pid_msg.linear.y = y_msg->data;
}
void Combiner::z_callback(const Float64::ConstPtr &z_msg)
{
    cmd_vel_pid_msg.linear.z = z_msg->data;
}
void Combiner::cmd_vel_callback(const Twist::ConstPtr &cmd_vel_msg)
{
    cmd_vel_pid_msg.linear.x += cmd_vel_msg->linear.x;
    cmd_vel_pid_msg.linear.y += cmd_vel_msg->linear.y;
    cmd_vel_pid_msg.linear.z += cmd_vel_msg->linear.z;
    cmd_vel_pid_msg.angular.x += cmd_vel_msg->angular.x;
    cmd_vel_pid_msg.angular.y += cmd_vel_msg->angular.y;
    cmd_vel_pid_msg.angular.z += cmd_vel_msg->angular.z;
    cmd_vel_pid_pub.publish(cmd_vel_pid_msg);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "Combiner");
    Combiner c;
    while (ros::ok())
    {
        ros::spinOnce();
    }
}
