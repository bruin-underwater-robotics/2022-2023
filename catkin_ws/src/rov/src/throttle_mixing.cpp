#include "ros/ros.h"
#include <dynamic_reconfigure/server.h>
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
        const int forward[6] = {1, 0, 1, 1, 0, 1};
        const int right[6] = {-1, 0, 1, 1, 0, -1};
        const int up[6] = {0, -1, 0, 0, 1, 0};
        const int yaw[6] = {-1, 0, -1, 1, 0, 1};
        const int roll[6] = {0, -1, 0, 0, -1, 0};
        float output[6] = { 0 };
        bool val[17] = { 0 };
        bool prev_state[17] = { 0 };
        double multiplier = 0.5;
        
        nh.param<double>("x_rate", x_rate_, 1.0);
        nh.param<double>("y_rate", y_rate_, 1.0);
        nh.param<double>("z_rate", z_rate_, 1.0);
        nh.param<double>("pitch_rate", pitch_rate_, 1.0);
        nh.param<double>("roll_rate", roll_rate_, 1.0);
        nh.param<double>("yaw_rate", yaw_rate_, 1.0);
        
        nh.param<double>("x_expo", x_rate_, 1.0);
        nh.param<double>("y_expo", y_rate_, 1.0);
        nh.param<double>("z_expo", z_rate_, 1.0);
        nh.param<double>("pitch_expo", pitch_rate_, 1.0);
        nh.param<double>("roll_expo", roll_rate_, 1.0);
        nh.param<double>("yaw_expo", yaw_rate_, 1.0);
        
        double rateCalc(const double rate, const double expo);
        
        // dynamic reconfiguration
        dynamic_reconfigure::Server<Throttle_mixer::rateConfig> config_server;
        dynamic_reconfigure::Server<Throttle_mixer::rateConfig>::CallbackType f;
        f = boost::bind(&Throttle_mixer::reconfigureCallback, this, _1, _2);
        config_server.setCallback(f);
};

Throttle_mixer::Throttle_mixer(){
    for(int i = 0; i < 6; i++){
        output[i]=0;
    }
        for(int i = 0; i < 17; i++){
        val[i]=0;
    }
    cmd_thruster_pub = nh.advertise<rov::cmd_thruster>("cmd_thruster", 1);
    sub = nh.subscribe<geometry_msgs::Twist>("cmd_vel", 1, &Throttle_mixer::cmd_velCallback, this);
    joy_sub = nh.subscribe<sensor_msgs::Joy>("joy", 1, &Throttle_mixer::joy_callBack, this);
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
            
            if(i == 5){
                multiplier = multiplier + 0.1;
                if(multiplier >= 1){
                    multiplier = 1;
                }
            }
            else if(i == 4){
                multiplier = multiplier - 0.1;
                if(multiplier <= 0.1){
                    multiplier = 0.1;
                }
            }
        }
        msg.buttons.push_back(val[i]);
    }
    msg.multiplier = multiplier;
    cmd_thruster_pub.publish(msg);
}

double Throttle_mixer::rateCalc(const double input, const double rate, const double expo){
        if(input < 0){
                y = rate*pow(input, expo);
        }else{
                y = -rate*pow(input, expo);
        }
        return y;
}

void Throttle_mixer::reconfigureCallback(Throttle_mixer::Config& config, uint32_t level)
{
  if (first_reconfig_)
  {
    getParam("x_rate", x_rate_);
    getParam("x_expo", x_expo_);
    getParam("y_rate", y_rate_);
    getParam("y_expo", y_expo_);
    getParam("z_rate", z_rate_);
    getParam("z_expo", z_expo_);
    first_reconfig_ = false;
    return;  // Ignore the first call to reconfigure which happens at startup
  }
  ROS_INFO("Pid reconfigure request: Kp: %f, Ki: %f, Kd: %f", Kp_, Ki_, Kd_);
}

void Throttle_mixer::cmd_velCallback(const geometry_msgs::Twist::ConstPtr& twist_msg){
    msg.thruster_val.clear();
        
    x_val = (twist_msg->linear.x, nh.getParam("x_rate", x_rate_), nh.getParam("x_expo", x_expo_));
    y_val = (twist_msg->linear.y, nh.getParam("y_rate", y_rate_), nh.getParam("y_expo", y_expo_));
    z_val = (twist_msg->linear.z, nh.getParam("z_rate", z_rate_), nh.getParam("z_expo", z_expo_));
    //pitch_val = (twist_msg->angular.x, nh.getParam("x_rate", x_rate_), nh.getParam("x_expo", pitch_expo_));
    roll_vall = (twist_msg->angular.y, nh.getParam("roll_rate", roll_rate_), nh.getParam("roll_expo", roll_expo_));
    yaw_val = (twist_msg->angular.z, nh.getParam("yaw_rate", yaw_rate_), nh.getParam("yaw_expo", yaw_expo_));
    
        
    for(int i =0; i<6; i++){
        output[i] = x_val*forward[i] + y_val*right[i] + 
        z_val*up[i] + yaw_val*yaw[i] + roll_val*roll[i];
        if(output[i] != 0){
            output[i] = multiplier*output[i]/(ceil(abs(x_val*forward[i])) + ceil(abs(y_val*right[i])) + ceil(abs(z_val*up[i])) + ceil(abs(yaw_val*yaw[i])) + ceil(abs(roll_val*roll[i])));      
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
