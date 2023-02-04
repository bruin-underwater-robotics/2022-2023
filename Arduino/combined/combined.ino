
#include <ros.h>
#include <rov/cmd_thruster.h>
#include <rov/imu.h>
#include <Servo.h>
#include <geometry_msgs/Twist.h>
#include <Adafruit_BNO08x.h>

// For SPI mode, we need a CS pin
#define BNO08X_CS 10
#define BNO08X_INT 9

// For SPI mode, we also need a RESET 
//#define BNO08X_RESET 5
// but not for I2C or UART
#define BNO08X_RESET -1

Adafruit_BNO08x  bno08x(BNO08X_RESET);
sh2_SensorValue_t sensorValue;

Servo motor[6];
ros::NodeHandle  nh;
const byte motor_pin_begin = 6;
const byte util_pin_begin = 2;


void msg_Cb( const rov::cmd_thruster &msg){
  
  for(int i =0; i< 6; i++){
    motor[i].write(msg.thruster_val[i]*90. + 90.);
  }
  
  for(int i =0; i< 4; i++){
      digitalWrite(i+util_pin_begin, msg.buttons[i]);    
  }
}

geometry_msgs::Twist twist_msg;
ros::Publisher rotationPublisher("imu_output", &twist_msg);
ros::Subscriber<rov::cmd_thruster> sub("cmd_thruster", &msg_Cb );

void setup()
{ 
  Serial.begin(115200);
  if (!bno08x.begin_I2C()) {
    while (1) { delay(10); }
  }
  nh.getHardware()->setBaud(115200);

  bno08x.enableReport(SH2_GAME_ROTATION_VECTOR);
  bno08x.enableReport(SH2_ACCELEROMETER);

  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(rotationPublisher);
  
  for(int i = 0; i<6; i++){
    motor[i].attach(i+motor_pin_begin);
    motor[i].write(90); // 1500 for the thrusters  
  }
    for(int i = 0; i<4; i++){
      pinMode(i+util_pin_begin, OUTPUT);
  }
  delay(100);
}  

void loop()
{ 
  delay(1);
  if (! bno08x.getSensorEvent(&sensorValue)) {
    return;
  }
  
  switch (sensorValue.sensorId) {
    
    case SH2_GAME_ROTATION_VECTOR:
      twist_msg.angular.x = sensorValue.un.gameRotationVector.i;
      twist_msg.angular.y = sensorValue.un.gameRotationVector.j;
      twist_msg.angular.z = sensorValue.un.gameRotationVector.k;
      break;

    case SH2_ACCELEROMETER:
      twist_msg.linear.x = sensorValue.un.accelerometer.x;
      twist_msg.linear.y = sensorValue.un.accelerometer.y;
      twist_msg.linear.z = sensorValue.un.accelerometer.z;
      break;
  }
  rotationPublisher.publish( &twist_msg ); 
  nh.spinOnce();
}
