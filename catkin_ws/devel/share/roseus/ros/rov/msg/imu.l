;; Auto-generated. Do not edit!


(when (boundp 'rov::imu)
  (if (not (find-package "ROV"))
    (make-package "ROV"))
  (shadow 'imu (find-package "ROV")))
(unless (find-package "ROV::IMU")
  (make-package "ROV::IMU"))

(in-package "ROS")
;;//! \htmlinclude imu.msg.html


(defclass rov::imu
  :super ros::object
  :slots (_linear _angular ))

(defmethod rov::imu
  (:init
   (&key
    ((:linear __linear) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:angular __angular) (make-array 3 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _linear __linear)
   (setq _angular __angular)
   self)
  (:linear
   (&optional __linear)
   (if __linear (setq _linear __linear)) _linear)
  (:angular
   (&optional __angular)
   (if __angular (setq _angular __angular)) _angular)
  (:serialization-length
   ()
   (+
    ;; float32[3] _linear
    (* 4    3)
    ;; float32[3] _angular
    (* 4    3)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32[3] _linear
     (dotimes (i 3)
       (sys::poke (elt _linear i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; float32[3] _angular
     (dotimes (i 3)
       (sys::poke (elt _angular i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32[3] _linear
   (dotimes (i (length _linear))
     (setf (elt _linear i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     )
   ;; float32[3] _angular
   (dotimes (i (length _angular))
     (setf (elt _angular i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     )
   ;;
   self)
  )

(setf (get rov::imu :md5sum-) "bc7ac922642df8ef742b73a9501e5b6d")
(setf (get rov::imu :datatype-) "rov/imu")
(setf (get rov::imu :definition-)
      "float32[3] linear
float32[3] angular

")



(provide :rov/imu "bc7ac922642df8ef742b73a9501e5b6d")


