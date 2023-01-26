import cv2
import rospy
from sensor_msgs.msg import Image
import numpy as np
from cv_bridge import CvBridge
import sys 

bridge = CvBridge()

def callback(image):
        cv_image = bridge.imgmsg_to_cv2(image, desired_encoding='bgr8')
        cv2.imshow("test", cv_image)
        cv2.waitKey(1)

def listener():
        rospy.init_node("test", anonymous=True)
        rospy.Subscriber(sys.argv[1], Image, callback)
        rospy.spin()

if __name__ == '__main__':
        listener()
        
