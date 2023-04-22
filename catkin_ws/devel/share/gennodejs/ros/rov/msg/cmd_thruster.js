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

class cmd_thruster {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.thruster_val = null;
      this.buttons = null;
    }
    else {
      if (initObj.hasOwnProperty('thruster_val')) {
        this.thruster_val = initObj.thruster_val
      }
      else {
        this.thruster_val = [];
      }
      if (initObj.hasOwnProperty('buttons')) {
        this.buttons = initObj.buttons
      }
      else {
        this.buttons = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type cmd_thruster
    // Serialize message field [thruster_val]
    bufferOffset = _arraySerializer.float32(obj.thruster_val, buffer, bufferOffset, null);
    // Serialize message field [buttons]
    bufferOffset = _arraySerializer.int8(obj.buttons, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type cmd_thruster
    let len;
    let data = new cmd_thruster(null);
    // Deserialize message field [thruster_val]
    data.thruster_val = _arrayDeserializer.float32(buffer, bufferOffset, null)
    // Deserialize message field [buttons]
    data.buttons = _arrayDeserializer.int8(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 4 * object.thruster_val.length;
    length += object.buttons.length;
    return length + 8;
  }

  static datatype() {
    // Returns string type for a message object
    return 'rov/cmd_thruster';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '65da02d2a44549142e6d6c43c806567f';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32[] thruster_val
    int8[] buttons
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new cmd_thruster(null);
    if (msg.thruster_val !== undefined) {
      resolved.thruster_val = msg.thruster_val;
    }
    else {
      resolved.thruster_val = []
    }

    if (msg.buttons !== undefined) {
      resolved.buttons = msg.buttons;
    }
    else {
      resolved.buttons = []
    }

    return resolved;
    }
};

module.exports = cmd_thruster;
