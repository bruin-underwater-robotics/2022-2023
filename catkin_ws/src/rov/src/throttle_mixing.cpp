#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/Joy.h"
#include "rov/cmd_thruster.h"
#include <cmath>

struct Throttle_mixer{
        Throttle_mixer();
        void cmd_velCallback(const geometry_msgs::Twist::ConstPtr& joy_msg);
        void joy_callBack(const sensor_msgs::Joy::ConstPtr& twist_msg);
        rov::cmd_thruster msg;
        ros::NodeHandle nh;
        ros::Publisher cmd_thruster_pub;
        ros::Subscriber sub;
        ros::Subscriber joy_sub;

        //motors listed in order of top left clockwise
        //up-down motors are in the middle
        /*
        1----5
        |    |
        2    4
        |    |
        3----6
        */
        const int forward[6] = {1, 0, 1, 0, 1, 1};
        const int right[6] = {-1, 0, 1, 0, 1, -1};
        const int up[6] = {0, -1, 0, 1, 0, 0};
        const int yaw[6] = {-1, 0, -1, 0, 1, 1};
        const int roll[6] = {0, -1, 0, -1, 0, 0};
        float output[6] = { 0 };
        bool val[17] = { 0 };
        bool prev_state[17] = { 0 };
};

Throttle_mixer::Throttle_mixer(){
    for(int i = 0; i < 6; i++){
        output[i]=0;
    }
        for(int i = 0; i < 17; i++){
        val[i]=0;
    }
    cmd_thruster_pub = nh.advertise<rov::cmd_thruster>("cmd_thruster", 1);
    sub = nh.subscribe<geometry_msgs::Twist>("cmd_vel", 10, &Throttle_mixer::cmd_velCallback, this);
    joy_sub = nh.subscribe<sensor_msgs::Joy>("joy", 10, &Throttle_mixer::joy_callBack, this);
}

void Throttle_mixer::joy_callBack(const sensor_msgs::Joy::ConstPtr& joy_msg){
    msg.buttons.clear();
    for(int i = 0; i<17; i++){
        if(joy_msg->buttons[i] == 0){
            prev_state[i] = true;
        }
        else if(joy_msg->buttons[i] == 1 && prev_state[i] == true){
            prev_state[i] = false;
            val[i] = 1 - val[i];
        }
        msg.buttons.push_back(val[i]);
    }
    cmd_thruster_pub.publish(msg);
}

void Throttle_mixer::cmd_velCallback(const geometry_msgs::Twist::ConstPtr& twist_msg){
    
    msg.thruster_val.clear();
    for(int i =0; i<6; i++){
        output[i] = twist_msg->linear.x*forward[i] + twist_msg->linear.y*right[i] + 
        twist_msg->linear.z*up[i] + twist_msg->angular.z*yaw[i] + twist_msg->angular.x*roll[i];
        if(output[i] != 0){
        output[i] = 0.3 * output[i]/(ceil(abs(twist_msg->linear.x*forward[i])) + 
        ceil(abs(twist_msg->linear.y*right[i])) + ceil(abs(up[i])) + 
        ceil(abs(twist_msg->angular.z*yaw[i])) + ceil(abs(twist_msg->angular.x*roll[i])));      
        }
        msg.thruster_val.push_back(output[i]);
    }
    cmd_thruster_pub.publish(msg);
}

int main(int argc, char **argv){
    ros::init(argc, argv, "throttle_mixer");
    Throttle_mixer t;
    while(ros::ok()){
        ros::spinOnce();
    }
}