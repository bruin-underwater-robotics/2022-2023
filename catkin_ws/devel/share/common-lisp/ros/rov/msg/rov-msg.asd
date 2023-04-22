
(cl:in-package :asdf)

(defsystem "rov-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "cmd_thruster" :depends-on ("_package_cmd_thruster"))
    (:file "_package_cmd_thruster" :depends-on ("_package"))
    (:file "imu" :depends-on ("_package_imu"))
    (:file "_package_imu" :depends-on ("_package"))
  ))