
#include <ros.h>
#include <rov/cmd_thruster.h>
#include <Servo.h>

Servo motor[6];
ros::NodeHandle  nh;
const byte motor_pin_begin = 6;
const byte valve_pin_begin = 2;
bool valve_state[4];
bool prev_state[4];

void msg_Cb( const rov::cmd_thruster &msg){
  
  for(int i =0; i< 6; i++){
    motor[i].write(msg.thruster_val[i]*90. + 90.);
  }
  
  for(int i =0; i< 4; i++){
    if(msg.buttons[i] == 0){
      prev_state[i] = true;
    } 
    else if(msg.buttons[i] == 1 && prev_state[i] == true){
      prev_state[i] = false;
      valve_state[i] = 1 - valve_state[i]; 
      digitalWrite(i+valve_pin_begin, valve_state[i]);    
    }
  }
}

ros::Subscriber<rov::cmd_thruster> sub("cmd_thruster", &msg_Cb );

void setup()
{ 
  Serial.begin(115200);
  nh.initNode();
  nh.subscribe(sub);
  for(int i = 0; i<6; i++){
    motor[i].attach(i+motor_pin_begin);
    motor[i].write(90); // 1500 for the thrusters  
  }
    for(int i = 0; i<4; i++){
      pinMode(i+valve_pin_begin, OUTPUT);
      valve_state[i] = false;
      prev_state[i] = true;
  }
}  

void loop()
{  
  nh.spinOnce();
}
