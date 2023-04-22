; Auto-generated. Do not edit!


(cl:in-package rov-msg)


;//! \htmlinclude imu.msg.html

(cl:defclass <imu> (roslisp-msg-protocol:ros-message)
  ((linear
    :reader linear
    :initarg :linear
    :type (cl:vector cl:float)
   :initform (cl:make-array 3 :element-type 'cl:float :initial-element 0.0))
   (angular
    :reader angular
    :initarg :angular
    :type (cl:vector cl:float)
   :initform (cl:make-array 3 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass imu (<imu>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <imu>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'imu)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name rov-msg:<imu> is deprecated: use rov-msg:imu instead.")))

(cl:ensure-generic-function 'linear-val :lambda-list '(m))
(cl:defmethod linear-val ((m <imu>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader rov-msg:linear-val is deprecated.  Use rov-msg:linear instead.")
  (linear m))

(cl:ensure-generic-function 'angular-val :lambda-list '(m))
(cl:defmethod angular-val ((m <imu>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader rov-msg:angular-val is deprecated.  Use rov-msg:angular instead.")
  (angular m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <imu>) ostream)
  "Serializes a message object of type '<imu>"
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'linear))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'angular))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <imu>) istream)
  "Deserializes a message object of type '<imu>"
  (cl:setf (cl:slot-value msg 'linear) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'linear)))
    (cl:dotimes (i 3)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits)))))
  (cl:setf (cl:slot-value msg 'angular) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'angular)))
    (cl:dotimes (i 3)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<imu>)))
  "Returns string type for a message object of type '<imu>"
  "rov/imu")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'imu)))
  "Returns string type for a message object of type 'imu"
  "rov/imu")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<imu>)))
  "Returns md5sum for a message object of type '<imu>"
  "bc7ac922642df8ef742b73a9501e5b6d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'imu)))
  "Returns md5sum for a message object of type 'imu"
  "bc7ac922642df8ef742b73a9501e5b6d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<imu>)))
  "Returns full string definition for message of type '<imu>"
  (cl:format cl:nil "float32[3] linear~%float32[3] angular~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'imu)))
  "Returns full string definition for message of type 'imu"
  (cl:format cl:nil "float32[3] linear~%float32[3] angular~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <imu>))
  (cl:+ 0
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'linear) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'angular) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <imu>))
  "Converts a ROS message object to a list"
  (cl:list 'imu
    (cl:cons ':linear (linear msg))
    (cl:cons ':angular (angular msg))
))
