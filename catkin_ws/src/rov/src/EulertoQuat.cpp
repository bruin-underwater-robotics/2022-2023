#include <cmath>
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Pose.h"

struct Quaternion
{
    double x, y, z, w;
};

Quaternion ToQuaternion(double roll, double pitch, double yaw) // roll (x), pitch (Y), yaw (z)
{
    // Abbreviations for the various angular functions

    double cr = cos(roll * 0.5);
    double sr = sin(roll * 0.5);
    double cp = cos(pitch * 0.5);
    double sp = sin(pitch * 0.5);
    double cy = cos(yaw * 0.5);
    double sy = sin(yaw * 0.5);

    Quaternion q;
    q.w = cr * cp * cy + sr * sp * sy;
    q.x = sr * cp * cy - cr * sp * sy;
    q.y = cr * sp * cy + sr * cp * sy;
    q.z = cr * cp * sy - sr * sp * cy;

    return q;
}

class EulertoQuat{
    public:
        EulertoQuat();
        void cmd_velCallback(const geometry_msgs::Twist::ConstPtr& msg);
    private:
        geometry_msgs::Pose pose_msg;
        ros::NodeHandle nh;
        ros::Publisher pose_pub;
        ros::Subscriber cmd_vel_sub;
        Quaternion q;
        double x;
        double y;
        double z;
};

EulertoQuat::EulertoQuat(){
    pose_pub = nh.advertise<geometry_msgs::Pose>("orientation", 1);
    cmd_vel_sub = nh.subscribe<geometry_msgs::Twist>("imu_output", 10, &EulertoQuat::cmd_velCallback, this);
}

void EulertoQuat::cmd_velCallback(const geometry_msgs::Twist::ConstPtr& msg){
    q = ToQuaternion(msg->angular.x, msg->angular.y, msg->angular.z);
    pose_msg.position.x = msg->linear.x;
    pose_msg.position.y = msg->linear.y;
    pose_msg.position.z = msg->linear.z;
    pose_msg.orientation.x = q.x;
    pose_msg.orientation.y = q.y;
    pose_msg.orientation.z = q.z;
    pose_msg.orientation.w = q.w;
    pose_pub.publish(pose_msg);
}

int main(int argc, char **argv){
    ros::init(argc, argv, "rov_orientation_quat");
    EulertoQuat E;
    while(ros::ok()){
        ros::spinOnce();
    }
}