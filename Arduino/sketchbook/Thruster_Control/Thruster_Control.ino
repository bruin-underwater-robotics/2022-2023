
#include <ros.h>
#include <rov/cmd_thruster.h>
#include <Servo.h>

Servo motor[6];
ros::NodeHandle  nh;

void messageCb( const rov::cmd_thruster &msg){
  for(int i =0; i< 6; i++){
    motor[i].write(msg.thruster_val[i]*90 + 90);
  }
}

ros::Subscriber<rov::cmd_thruster> sub("cmd_thruster", &messageCb );

void setup()
{ 
  const int pin_begin = 6;
  for(int i = 0; i<6; i++){
    motor[i].attach(i+pin_begin);
    motor[i].write(90); // 1500 for the thrusters  
  }
  nh.initNode();
  nh.subscribe(sub);
}  

void loop()
{  
  nh.spinOnce();
  delay(1);
}
