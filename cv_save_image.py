import cv2
import rospy
from sensor_msgs.msg import Image
import numpy as np
from cv_bridge import CvBridge
import sys

bridge = CvBridge()

if __name__ == '__main__':
        rospy.init_node("save_image", anonymous=True)
        image_message = rospy.wait_for_message(sys.argv[1], Image)
        cv_image = bridge.imgmsg_to_cv2(image_message, desired_encoding="bgr8")
        cv2.imwrite(sys.argv[2], cv_image)
