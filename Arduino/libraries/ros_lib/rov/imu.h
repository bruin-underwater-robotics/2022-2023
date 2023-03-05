#ifndef _ROS_rov_imu_h
#define _ROS_rov_imu_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace rov
{

  class imu : public ros::Msg
  {
    public:
      float linear[3];
      float angular[3];

    imu():
      linear(),
      angular()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      for( uint32_t i = 0; i < 3; i++){
      union {
        float real;
        uint32_t base;
      } u_lineari;
      u_lineari.real = this->linear[i];
      *(outbuffer + offset + 0) = (u_lineari.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_lineari.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_lineari.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_lineari.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->linear[i]);
      }
      for( uint32_t i = 0; i < 3; i++){
      union {
        float real;
        uint32_t base;
      } u_angulari;
      u_angulari.real = this->angular[i];
      *(outbuffer + offset + 0) = (u_angulari.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_angulari.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_angulari.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_angulari.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->angular[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      for( uint32_t i = 0; i < 3; i++){
      union {
        float real;
        uint32_t base;
      } u_lineari;
      u_lineari.base = 0;
      u_lineari.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_lineari.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_lineari.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_lineari.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->linear[i] = u_lineari.real;
      offset += sizeof(this->linear[i]);
      }
      for( uint32_t i = 0; i < 3; i++){
      union {
        float real;
        uint32_t base;
      } u_angulari;
      u_angulari.base = 0;
      u_angulari.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_angulari.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_angulari.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_angulari.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->angular[i] = u_angulari.real;
      offset += sizeof(this->angular[i]);
      }
     return offset;
    }

    virtual const char * getType() override { return "rov/imu"; };
    virtual const char * getMD5() override { return "bc7ac922642df8ef742b73a9501e5b6d"; };

  };

}
#endif
