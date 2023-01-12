
#include <ros.h>
#include <rov/cmd_thruster.h>
#include <Servo.h>

Servo motor[6];
ros::NodeHandle  nh;
const byte pin_begin = 6;

void thrusterCb( const rov::cmd_thruster &msg){
  for(int i =0; i< 6; i++){
    motor[i].write(msg.thruster_val[i]*90 + 90);
  }
  for(int i =0; i< 4; i++){
       digitalWrite(i+2, msg.buttons[i]);
  }
}

ros::Subscriber<rov::cmd_thruster> sub("cmd_thruster", &thrusterCb );

void setup()
{ 
  nh.initNode();
  nh.subscribe(sub);
  for(int i = 0; i<6; i++){
    motor[i].attach(i+pin_begin);
    motor[i].write(90); // 1500 for the thrusters  
  }
    for(int i = 2; i<6; i++){
      pinMode(i, OUTPUT);
  }
}  

void loop()
{  
  nh.spinOnce();
  delay(1);
}
