#include <cmath>
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Pose.h"
#include "std_msgs/Float64.h"

struct Euler
{
    double x, y, z;
};

Euler ToEuler(double x, double y, double z, double w)
{
    Euler angles;
    // roll (x-axis rotation)
    double sinr_cosp = 2 * (w * x + y * z);
    double cosr_cosp = 1 - 2 * (x * x + y * y);
    angles.x = std::atan2(sinr_cosp, cosr_cosp);

    // pitch (y-axis rotation)
    double sinp = std::sqrt(1 + 2 * (w * y - x * z));
    double cosp = std::sqrt(1 - 2 * (w * y - x * z));
    angles.y = 2 * std::atan2(sinp, cosp) - M_PI / 2;

    // yaw (z-axis rotation)
    double siny_cosp = 2 * (w * z + x * y);
    double cosy_cosp = 1 - 2 * (y * y + z * z);
    angles.z = std::atan2(siny_cosp, cosy_cosp);

    return angles;
}

class QuattoEuler
{
public:
    QuattoEuler();
    void cmd_velCallback(const geometry_msgs::Pose::ConstPtr &msg);

private:
    // geometry_msgs::Twist twist_msg;
    std_msgs::Float64 roll_msg;
    std_msgs::Float64 pitch_msg;
    std_msgs::Float64 yaw_msg;
    std_msgs::Float64 x_msg;
    std_msgs::Float64 y_msg;
    std_msgs::Float64 z_msg;
    ros::NodeHandle nh;
    ros::Publisher roll_pub;
    ros::Publisher pitch_pub;
    ros::Publisher yaw_pub;
    ros::Publisher x_pub;
    ros::Publisher y_pub;
    ros::Publisher z_pub;
    ros::Subscriber cmd_vel_sub;
    Euler e;
    double x;
    double y;
    double z;
};

QuattoEuler::QuattoEuler()
{
    roll_pub = nh.advertise<std_msgs::Float64>("roll", 1);
    pitch_pub = nh.advertise<std_msgs::Float64>("pitch", 1);
    yaw_pub = nh.advertise<std_msgs::Float64>("yaw", 1);
    x_pub = nh.advertise<std_msgs::Float64>("x", 1);
    y_pub = nh.advertise<std_msgs::Float64>("y", 1);
    z_pub = nh.advertise<std_msgs::Float64>("z", 1);
    cmd_vel_sub = nh.subscribe<geometry_msgs::Pose>("imu_output", 10, &QuattoEuler::cmd_velCallback, this);
}

void QuattoEuler::cmd_velCallback(const geometry_msgs::Pose::ConstPtr &msg)
{
    e = ToEuler(msg->orientation.x, msg->orientation.y, msg->orientation.z, msg->orientation.w);
    x_msg.data = msg->position.x;
    y_msg.data = msg->position.y;
    z_msg.data = msg->position.z;
    roll_msg.data = 180 * e.x / M_PI;
    pitch_msg.data = 180 * e.y / M_PI;
    yaw_msg.data = 180 * e.z / M_PI;
    roll_pub.publish(roll_msg);
    pitch_pub.publish(pitch_msg);
    yaw_pub.publish(yaw_msg);
    x_pub.publish(x_msg);
    y_pub.publish(y_msg);
    z_pub.publish(z_msg);
}

// void QuattoEuler::cmd_velCallback(const geometry_msgs::Pose::ConstPtr& msg){
//     e = ToEuler(msg->orientation.x, msg->orientation.y, msg->orientation.z, msg->orientation.w);
//     twist_msg.linear.x = msg->position.x;
//     twist_msg.linear.y = msg->position.y;
//     twist_msg.linear.z = msg->position.z;
//     twist_msg.angular.x = 180 * e.x/M_PI;
//     twist_msg.angular.y = 180 * e.y/M_PI;
//     twist_msg.angular.z = 180 * e.z/M_PI;
//     twist_pub.publish(twist_msg);
// }

int main(int argc, char **argv)
{
    ros::init(argc, argv, "rov_orientation_euler");
    QuattoEuler Q;
    while (ros::ok())
    {
        ros::spinOnce();
    }
}