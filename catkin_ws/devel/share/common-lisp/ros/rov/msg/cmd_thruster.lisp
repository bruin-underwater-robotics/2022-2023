; Auto-generated. Do not edit!


(cl:in-package rov-msg)


;//! \htmlinclude cmd_thruster.msg.html

(cl:defclass <cmd_thruster> (roslisp-msg-protocol:ros-message)
  ((thruster_val
    :reader thruster_val
    :initarg :thruster_val
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0))
   (buttons
    :reader buttons
    :initarg :buttons
    :type (cl:vector cl:fixnum)
   :initform (cl:make-array 0 :element-type 'cl:fixnum :initial-element 0)))
)

(cl:defclass cmd_thruster (<cmd_thruster>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <cmd_thruster>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'cmd_thruster)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name rov-msg:<cmd_thruster> is deprecated: use rov-msg:cmd_thruster instead.")))

(cl:ensure-generic-function 'thruster_val-val :lambda-list '(m))
(cl:defmethod thruster_val-val ((m <cmd_thruster>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader rov-msg:thruster_val-val is deprecated.  Use rov-msg:thruster_val instead.")
  (thruster_val m))

(cl:ensure-generic-function 'buttons-val :lambda-list '(m))
(cl:defmethod buttons-val ((m <cmd_thruster>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader rov-msg:buttons-val is deprecated.  Use rov-msg:buttons instead.")
  (buttons m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <cmd_thruster>) ostream)
  "Serializes a message object of type '<cmd_thruster>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'thruster_val))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'thruster_val))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'buttons))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    ))
   (cl:slot-value msg 'buttons))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <cmd_thruster>) istream)
  "Deserializes a message object of type '<cmd_thruster>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'thruster_val) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'thruster_val)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits))))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'buttons) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'buttons)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256)))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<cmd_thruster>)))
  "Returns string type for a message object of type '<cmd_thruster>"
  "rov/cmd_thruster")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'cmd_thruster)))
  "Returns string type for a message object of type 'cmd_thruster"
  "rov/cmd_thruster")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<cmd_thruster>)))
  "Returns md5sum for a message object of type '<cmd_thruster>"
  "65da02d2a44549142e6d6c43c806567f")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'cmd_thruster)))
  "Returns md5sum for a message object of type 'cmd_thruster"
  "65da02d2a44549142e6d6c43c806567f")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<cmd_thruster>)))
  "Returns full string definition for message of type '<cmd_thruster>"
  (cl:format cl:nil "float32[] thruster_val~%int8[] buttons~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'cmd_thruster)))
  "Returns full string definition for message of type 'cmd_thruster"
  (cl:format cl:nil "float32[] thruster_val~%int8[] buttons~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <cmd_thruster>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'thruster_val) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'buttons) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <cmd_thruster>))
  "Converts a ROS message object to a list"
  (cl:list 'cmd_thruster
    (cl:cons ':thruster_val (thruster_val msg))
    (cl:cons ':buttons (buttons msg))
))
