;; Auto-generated. Do not edit!


(when (boundp 'rov::cmd_thruster)
  (if (not (find-package "ROV"))
    (make-package "ROV"))
  (shadow 'cmd_thruster (find-package "ROV")))
(unless (find-package "ROV::CMD_THRUSTER")
  (make-package "ROV::CMD_THRUSTER"))

(in-package "ROS")
;;//! \htmlinclude cmd_thruster.msg.html


(defclass rov::cmd_thruster
  :super ros::object
  :slots (_thruster_val _buttons ))

(defmethod rov::cmd_thruster
  (:init
   (&key
    ((:thruster_val __thruster_val) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:buttons __buttons) (make-array 0 :initial-element 0 :element-type :integer))
    )
   (send-super :init)
   (setq _thruster_val __thruster_val)
   (setq _buttons __buttons)
   self)
  (:thruster_val
   (&optional __thruster_val)
   (if __thruster_val (setq _thruster_val __thruster_val)) _thruster_val)
  (:buttons
   (&optional __buttons)
   (if __buttons (setq _buttons __buttons)) _buttons)
  (:serialization-length
   ()
   (+
    ;; float32[] _thruster_val
    (* 4    (length _thruster_val)) 4
    ;; int8[] _buttons
    (* 1    (length _buttons)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32[] _thruster_val
     (write-long (length _thruster_val) s)
     (dotimes (i (length _thruster_val))
       (sys::poke (elt _thruster_val i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; int8[] _buttons
     (write-long (length _buttons) s)
     (dotimes (i (length _buttons))
       (write-byte (elt _buttons i) s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32[] _thruster_val
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _thruster_val (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _thruster_val i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     ))
   ;; int8[] _buttons
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _buttons (instantiate integer-vector n))
     (dotimes (i n)
     (setf (elt _buttons i) (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> (elt _buttons i) 127) (setf (elt _buttons i) (- (elt _buttons i) 256)))
     ))
   ;;
   self)
  )

(setf (get rov::cmd_thruster :md5sum-) "65da02d2a44549142e6d6c43c806567f")
(setf (get rov::cmd_thruster :datatype-) "rov/cmd_thruster")
(setf (get rov::cmd_thruster :definition-)
      "float32[] thruster_val
int8[] buttons

")



(provide :rov/cmd_thruster "65da02d2a44549142e6d6c43c806567f")


