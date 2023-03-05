#ifndef _ROS_rov_cmd_thruster_h
#define _ROS_rov_cmd_thruster_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace rov
{

  class cmd_thruster : public ros::Msg
  {
    public:
      uint32_t thruster_val_length;
      typedef float _thruster_val_type;
      _thruster_val_type st_thruster_val;
      _thruster_val_type * thruster_val;
      uint32_t buttons_length;
      typedef int8_t _buttons_type;
      _buttons_type st_buttons;
      _buttons_type * buttons;

    cmd_thruster():
      thruster_val_length(0), st_thruster_val(), thruster_val(nullptr),
      buttons_length(0), st_buttons(), buttons(nullptr)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->thruster_val_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->thruster_val_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->thruster_val_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->thruster_val_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->thruster_val_length);
      for( uint32_t i = 0; i < thruster_val_length; i++){
      union {
        float real;
        uint32_t base;
      } u_thruster_vali;
      u_thruster_vali.real = this->thruster_val[i];
      *(outbuffer + offset + 0) = (u_thruster_vali.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_thruster_vali.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_thruster_vali.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_thruster_vali.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->thruster_val[i]);
      }
      *(outbuffer + offset + 0) = (this->buttons_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->buttons_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->buttons_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->buttons_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->buttons_length);
      for( uint32_t i = 0; i < buttons_length; i++){
      union {
        int8_t real;
        uint8_t base;
      } u_buttonsi;
      u_buttonsi.real = this->buttons[i];
      *(outbuffer + offset + 0) = (u_buttonsi.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->buttons[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      uint32_t thruster_val_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      thruster_val_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      thruster_val_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      thruster_val_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->thruster_val_length);
      if(thruster_val_lengthT > thruster_val_length)
        this->thruster_val = (float*)realloc(this->thruster_val, thruster_val_lengthT * sizeof(float));
      thruster_val_length = thruster_val_lengthT;
      for( uint32_t i = 0; i < thruster_val_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_thruster_val;
      u_st_thruster_val.base = 0;
      u_st_thruster_val.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_thruster_val.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_thruster_val.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_thruster_val.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_thruster_val = u_st_thruster_val.real;
      offset += sizeof(this->st_thruster_val);
        memcpy( &(this->thruster_val[i]), &(this->st_thruster_val), sizeof(float));
      }
      uint32_t buttons_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      buttons_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      buttons_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      buttons_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->buttons_length);
      if(buttons_lengthT > buttons_length)
        this->buttons = (int8_t*)realloc(this->buttons, buttons_lengthT * sizeof(int8_t));
      buttons_length = buttons_lengthT;
      for( uint32_t i = 0; i < buttons_length; i++){
      union {
        int8_t real;
        uint8_t base;
      } u_st_buttons;
      u_st_buttons.base = 0;
      u_st_buttons.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->st_buttons = u_st_buttons.real;
      offset += sizeof(this->st_buttons);
        memcpy( &(this->buttons[i]), &(this->st_buttons), sizeof(int8_t));
      }
     return offset;
    }

    virtual const char * getType() override { return "rov/cmd_thruster"; };
    virtual const char * getMD5() override { return "65da02d2a44549142e6d6c43c806567f"; };

  };

}
#endif
