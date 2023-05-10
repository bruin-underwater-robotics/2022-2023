#ifndef THROTTLE_MIXER_H
#define THROTTLE_MIXER_H

#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/Joy.h"
#include "rov/cmd_thruster.h"
#include <iostream>
#include <ros/time.h>
#include "std_msgs/Float32.h"
#include <dynamic_reconfigure/server.h>
#include <controller/ControllerConfig.h>
#include <cmath>

class Throttle_mixer{
    public:
        Throttle_mixer();

    private:
        void cmd_velCallback(const geometry_msgs::Twist::ConstPtr& joy_msg);
        void joyCallBack(const sensor_msgs::Joy::ConstPtr& twist_msg);
        void reconfigureCallback(controller::ControllerConfig& config, uint32_t level);
        double rateCalc(const double input, const double rate, const double expo);
        rov::cmd_thruster msg;
        std_msgs::Float32 speed_msg;
        ros::NodeHandle nh;
        ros::Publisher cmd_thruster_pub;
        ros::Publisher speed_multiplier;
        ros::Subscriber sub;
        ros::Subscriber joy_sub;
        dynamic_reconfigure::Server<controller::ControllerConfig> config_server;
        //motors listed in order of top left clockwise
        //up-down motors are in the middle
        /*
        1----5
        |    |
        2    4
        |    |
        3----6
        */
        const int forward[6] = {1, 0, 1, 1, 0, 1};
        const int right[6] = {-1, 0, 1, 1, 0, -1};
        const int up[6] = {0, -1, 0, 0, 1, 0};
        const int yaw[6] = {-1, 0, -1, 1, 0, 1};
        const int roll[6] = {0, -1, 0, 0, -1, 0};
        double input[6] = { 0 };
        float output[6] = { 0 };
        bool val[17] = { 0 };
        bool prev_state[17] = { 0 };
        double multiplier = 0.5;

        double x_rate_, y_rate_, z_rate_, pitch_rate_, roll_rate_, yaw_rate_;
        double x_expo_, y_expo_, z_expo_, pitch_expo_, roll_expo_, yaw_expo_;
        bool reset_ = false;
};  

#endif 