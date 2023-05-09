#ifndef _ROS_H_
#define _ROS_H_

#include "ros/node_handle.h"
#include "ArduinoHardware.h"

namespace ros
{
#if defined(__AVR_ATmega8__) || defined(__AVR_ATmega168__)
  /* downsize our buffers */
  typedef NodeHandle_<ArduinoHardware, 6, 6, 150, 150> NodeHandle;

#elif defined(__AVR_ATmega328P__)

  typedef NodeHandle_<ArduinoHardware, 25, 25, 280, 280> NodeHandle;

#elif defined(__AVR_ATmega2560__)

  typedef NodeHandle_<ArduinoHardware, 5, 10, 1024, 1024> NodeHandle;

#else

  typedef NodeHandle_<ArduinoHardware> NodeHandle;

#endif   
}

#endif
