#include "throttle_mixer.h"

Throttle_mixer::Throttle_mixer()
{
    ros::NodeHandle nh;
    ros::NodeHandle nh_priv("~");

    nh_priv.param<float>("x_rate", x_rate_, 1.0);
    nh_priv.param<float>("y_rate", y_rate_, 1.0);
    nh_priv.param<float>("z_rate", z_rate_, 1.0);
    nh_priv.param<float>("x_expo", x_expo_, 1.0);
    nh_priv.param<float>("y_expo", y_expo_, 1.0);
    nh_priv.param<float>("z_expo", z_expo_, 1.0);

    nh_priv.param<float>("pitch_rate", pitch_rate_, 1.0);
    nh_priv.param<float>("roll_rate", roll_rate_, 1.0);
    nh_priv.param<float>("yaw_rate", yaw_rate_, 1.0);
    nh_priv.param<float>("pitch_expo", pitch_expo_, 1.0);
    nh_priv.param<float>("roll_expo", roll_expo_, 1.0);
    nh_priv.param<float>("yaw_expo", yaw_expo_, 1.0);

    nh_priv.param<bool>("reset", reset_, false);

    cmd_thruster_pub = nh.advertise<rov::cmd_thruster>("cmd_thruster", 10);
    speed_multiplier = nh.advertise<std_msgs::Float32>("speed_multiplier", 10);
    sub = nh.subscribe<geometry_msgs::Twist>("cmd_vel", 10, &Throttle_mixer::cmd_velCallback, this);
    joy_sub = nh.subscribe<sensor_msgs::Joy>("joy", 10, &Throttle_mixer::joyCallBack, this);

    dynamic_reconfigure::Server<controller::ControllerConfig>::CallbackType f;
    f = boost::bind(&Throttle_mixer::reconfigureCallback, this, _1, _2);
    config_server.setCallback(f);
}

float Throttle_mixer::rateCalc(const float input, const float rate, const float expo)
{
    float y;
    if (input < 0)
    {
        y = -rate * pow(-input, expo);
    }
    else
    {
        y = rate * pow(input, expo);
    }
    if (y > 1)
    {
        y = 1;
    }
    else if (y < -1)
    {
        y = -1;
    }

    return y;
}

void Throttle_mixer::reconfigureCallback(controller::ControllerConfig &config, uint32_t level)
{
    if (config.reset == true)
    {
        config.x_rate = 1.0;
        config.y_rate = 1.0;
        config.z_rate = 1.0;
        config.pitch_rate = 1.0;
        config.roll_rate = 1.0;
        config.yaw_rate = 1.0;
        config.x_expo = 1.0;
        config.y_expo = 1.0;
        config.z_expo = 1.0;
        config.pitch_expo = 1.0;
        config.roll_expo = 1.0;
        config.yaw_expo = 1.0;
        config.reset = false;
    }
    x_rate_ = config.x_rate;
    y_rate_ = config.y_rate;
    z_rate_ = config.z_rate;
    pitch_rate_ = config.pitch_rate;
    roll_rate_ = config.roll_rate;
    yaw_rate_ = config.yaw_rate;
    x_expo_ = config.x_expo;
    y_expo_ = config.y_expo;
    z_expo_ = config.z_expo;
    pitch_expo_ = config.pitch_expo;
    roll_expo_ = config.roll_expo;
    yaw_expo_ = config.yaw_expo;
    reset_ = config.reset;
    ROS_INFO("Reconfigure Request: %f %f %f %f %f %f %f %f %f %f %f %f",
             x_rate_, y_rate_, z_rate_, pitch_rate_, roll_rate_, yaw_rate_,
             x_expo_, y_expo_, z_expo_, pitch_expo_, roll_expo_, yaw_expo_);
}

void Throttle_mixer::joyCallBack(const sensor_msgs::Joy::ConstPtr &joy_msg)
{
    msg.buttons.clear();
    for (int i = 0; i < 17; i++)
    {
        switch (i)
        {
        case 6:
            // rotation lock
            if (joy_msg->buttons[i] == 1)
                rotation_enable = 0;
            else
                rotation_enable = 1;
            break;
        default:
            // State Calculations
            if (joy_msg->buttons[i] == 0)
                prev_state[i] = true;
            // State Change
            else if (prev_state[i] == true)
            {
                prev_state[i] = false;
                val[i] = 1 - val[i];
                // Special cases for toggle buttons
                switch (i)
                {
                case 4:
                    // speed multiplier decrease
                    multiplier = multiplier - 0.1;
                    if (multiplier <= 0.1)
                        multiplier = 0.1;
                    break;
                case 5:
                    // speed multiplier increase
                    multiplier = multiplier + 0.1;
                    if (multiplier >= 1)
                        multiplier = 1;
                    break;
                }
            }
        }
        msg.buttons.push_back(val[i]);
    }
    speed_msg.data = multiplier;
    speed_multiplier.publish(speed_msg);
}

void Throttle_mixer::cmd_velCallback(const geometry_msgs::Twist::ConstPtr &twist_msg)
{
    msg.thruster_val.clear();
    // putting things in arrays to use for loops
    double twist_temp[6] = {
        twist_msg->linear.x,
        twist_msg->linear.y,
        twist_msg->linear.z,
        twist_msg->angular.x,
        twist_msg->angular.y,
        twist_msg->angular.z,
    };
    float calc[6] = {0};
    float rate[6] = {x_rate_, y_rate_, z_rate_, pitch_rate_, roll_rate_, yaw_rate_};
    float expo[6] = {x_expo_, y_expo_, z_expo_, pitch_expo_, roll_expo_, yaw_expo_};

    for (int i = 0; i < 6; i++)
    {
        calc[i] = rateCalc(twist_temp[i], rate[i], expo[i]);
    }

    for (int i = 0; i < 6; i++)
    {
        // amount of power to thruster i
        output[i] = calc[0] * forward[i] + calc[1] * right[i] +
                    calc[2] * up[i] + calc[4] * roll[i] + rotation_enable * calc[5] * yaw[i];
        // No calc[3] because we dont have pitch
        if (output[i] != 0)
        {
            // normalize i to be in the range of multiplier*[-1, 1]
            // Default multiplier is 0.5
            output[i] = multiplier * output[i] / (ceil(abs(twist_msg->linear.x * forward[i])) + ceil(abs(twist_msg->linear.y * right[i])) + ceil(abs(up[i])) + ceil(abs(twist_msg->angular.z * yaw[i])) + ceil(abs(twist_msg->angular.x * roll[i])));
        }
        msg.thruster_val.push_back(output[i]);
    }
    cmd_thruster_pub.publish(msg);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "throttle_mixer");
    Throttle_mixer t;
    while (ros::ok())
    {
        ros::spinOnce();
        // Add a small sleep to avoid 100% CPU usage
        ros::Duration(0.001).sleep();
    }
}