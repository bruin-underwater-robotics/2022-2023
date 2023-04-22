// Auto-generated. Do not edit!

// (in-package rov.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class imu {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.linear = null;
      this.angular = null;
    }
    else {
      if (initObj.hasOwnProperty('linear')) {
        this.linear = initObj.linear
      }
      else {
        this.linear = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('angular')) {
        this.angular = initObj.angular
      }
      else {
        this.angular = new Array(3).fill(0);
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type imu
    // Check that the constant length array field [linear] has the right length
    if (obj.linear.length !== 3) {
      throw new Error('Unable to serialize array field linear - length must be 3')
    }
    // Serialize message field [linear]
    bufferOffset = _arraySerializer.float32(obj.linear, buffer, bufferOffset, 3);
    // Check that the constant length array field [angular] has the right length
    if (obj.angular.length !== 3) {
      throw new Error('Unable to serialize array field angular - length must be 3')
    }
    // Serialize message field [angular]
    bufferOffset = _arraySerializer.float32(obj.angular, buffer, bufferOffset, 3);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type imu
    let len;
    let data = new imu(null);
    // Deserialize message field [linear]
    data.linear = _arrayDeserializer.float32(buffer, bufferOffset, 3)
    // Deserialize message field [angular]
    data.angular = _arrayDeserializer.float32(buffer, bufferOffset, 3)
    return data;
  }

  static getMessageSize(object) {
    return 24;
  }

  static datatype() {
    // Returns string type for a message object
    return 'rov/imu';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'bc7ac922642df8ef742b73a9501e5b6d';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32[3] linear
    float32[3] angular
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new imu(null);
    if (msg.linear !== undefined) {
      resolved.linear = msg.linear;
    }
    else {
      resolved.linear = new Array(3).fill(0)
    }

    if (msg.angular !== undefined) {
      resolved.angular = msg.angular;
    }
    else {
      resolved.angular = new Array(3).fill(0)
    }

    return resolved;
    }
};

module.exports = imu;
