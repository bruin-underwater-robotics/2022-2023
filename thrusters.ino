/*
  from https://bluerobotics.com/learn/guide-for-controlling-the-basic-esc-with-a-potentiometer/
  and https://atadiat.com/en/e-rosserial-arduino-introduction/
*/
#include <Servo.h>
#include <ros.h>
#include <geometry_msgs/Twist.h>

#include <math.h>

ros::NodeHandle nh;

byte servo_pins = 6; // signal pin for the ESC. needs 6 pins next to each other 
Servo servos[6];

// vectors for controlling linear movement ? but now im not sure how to go down 
float top_right[] = {-.25, -.25, 0}; // jank rn but can expiremtn 
float top_left[] = {-.25, .25, 0};
float bottom_right[] = {.25, -.25, 0};
float bottom_left[] = {.25, .25, 0};
float right[] = {0, 0, .5};
float left[] = {0, 0, .5};

double pwm_x=0;
double pwm_y=0;
double pwm_z=0; 
double pwm = 0;

#define PI 3.14159

// depends on how thrusters are plugged in 
float* thrusters[] = {top_right, top_left, bottom_right, bottom_left, right, left};

void handler( const geometry_msgs::Twist& msg ) {
  int pwm_val = 0; 
  int thrust = 0; 
  for(int i = 0; i<6; i++){
    pwm_x = thrusters[i][0] * msg.linear.x; 
    pwm_y = thrusters[i][1] * msg.linear.y; 
    pwm_z = thrusters[i][2] * msg.linear.z; 

    pwm = map(long(100 * (pwm_x + pwm_y + pwm_z)), -50, 50, 0, 180); 

    // pwm_x = map((thrusters[i][0]*msg.linear.x), -1, 1, 0, 60);
    // pwm_y = map((thrusters[i][1]*msg.linear.y), -1, 1, 0, 60);
    // pwm_z = map((thrusters[i][2]*msg.linear.z), -1, 1, 0, 60);
    //pw = atan(msg.linear.x / msg.linear.y) * (180.0 / PI);
    servos[i].write( pwm /*pwm_x + pwmmy + pwm_z*/); // Send signal to ESC.
    // digitalWrite(LED_BUILTIN, HIGH);
    // delay(100);
    // digitalWrite(LED_BUILTIN, LOW);
  }
}

ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", &handler);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  nh.initNode(); 
  nh.subscribe(sub); 

  for(int i = 0; i<6; i++){
    servos[i].attach(i+servo_pins); 
  }
  for(int i = 0; i<6; i++){
    servos[i].write(90); 
  }
  delay(7000); // delay to allow the ESC to recognize the stopped signal.
}

void loop(){
  digitalWrite(LED_BUILTIN, LOW);
  nh.spinOnce();
}



