#include <ros.h>
#include <geometry_msgs/Twist.h>

// Basic demo for readings from Adafruit BNO08x
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

ros::NodeHandle  nh;
geometry_msgs::Twist twist_msg;
ros::Publisher rotationPublisher("imu_output", &twist_msg);

void setup(void) {
  Serial.begin(115200);

  bno08x.begin_I2C();

  bno08x.enableReport(SH2_GAME_ROTATION_VECTOR);
  bno08x.enableReport(SH2_ACCELEROMETER);

  nh.initNode();
  nh.advertise(rotationPublisher);

  delay(100);
}

void loop() {
  delay(50);
  
  if (! bno08x.getSensorEvent(&sensorValue)) {
    return;
  }
  
  switch (sensorValue.sensorId) {
    
    case SH2_GAME_ROTATION_VECTOR:
      // Serial.print("Game Rotation Vector - r: ");
      // Serial.print(sensorValue.un.gameRotationVector.real);
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