#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/Float32MultiArray.h"
#include "rov/cmd_thruster.h"
#include <cmath>

struct Throttle_mixer{
        Throttle_mixer();
        // void cmd_velCallback(const geometry_msgs::Twist::ConstPtr& msg);
        void cmd_velCallback(const geometry_msgs::Twist::ConstPtr& msg);
        ros::NodeHandle n;

        ros::Publisher cmd_thruster_pub;
        ros::Subscriber sub;

        //motors listed in order of top left clockwise
        //up-down motors are in the middle
        /*
        1----2
        |    |
        5    6
        |    |
        4----3
        */
        const int forward[6] = {1, 1, -1, -1, 0, 0};
        const int right[6] = {1, -1, 1, -1, 0, 0};
        const int up[6] = {0, 0, 0, 0, 1, 1};
        const int turn[6] = {1, -1, -1, 1, 0, 0};
        float output[6];
};

int main(int argc, char **argv){
    ros::init(argc, argv, "throttle_mixer");
    Throttle_mixer t;
    ros::spin();
}
Throttle_mixer::Throttle_mixer(){
    for(int i = 0; i < 6; i++){
        output[i]=0;
    }
    cmd_thruster_pub = n.advertise<rov::cmd_thruster>("cmd_thruster", 1);
    // cmd_thruster_pub = n.advertise<std_msgs::Float32MultiArray>("cmd_thruster", 1);
    sub = n.subscribe<geometry_msgs::Twist>("cmd_vel", 10, &Throttle_mixer::cmd_velCallback, this);
}
void Throttle_mixer::cmd_velCallback(const geometry_msgs::Twist::ConstPtr& twist_msg){
    //std_msgs::Float32MultiArray msg;
    rov::cmd_thruster msg;
    // set up dimensions
    //msg.layout.dim.push_back(std_msgs::MultiArrayDimension());
    //msg.layout.dim[0].size = 6;
    //msg.layout.dim[0].stride = 6;
    //msg.layout.dim[0].label = "thruster values";
    msg.thruster_val.clear();
    for(int i =0; i<6; i++){
        output[i] = twist_msg->linear.x*forward[i] + twist_msg->linear.y*right[i] + 
        twist_msg->linear.z*up[i] + twist_msg->angular.z*turn[i];
        if(output[i] != 0){
        output[i] = output[i]/(ceil(abs(twist_msg->linear.x*forward[i])) + 
        ceil(abs(twist_msg->linear.y*right[i])) + abs(up[i]) + 
        ceil(abs(twist_msg->angular.z*turn[i])));      
        }
        msg.thruster_val.push_back(output[i]);
    }
    cmd_thruster_pub.publish(thruster);
}