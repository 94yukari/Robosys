#!/usr/bin/env python

#AUTHOR：YUKARI SUZUKI,RYUICHI UEDA
#DESCRIPTION：rate(1000) count timer
#LICENSE：GPL
#VERSION：0.1


import rospy
from std_msgs.msg import Int32

n = 0
 
def cb(message):
    global n
    n = message.data*2

if __name__== '__main__':
    rospy.init_node('twice')
    sub = rospy.Subscriber('count_up', Int32 ,cb)
    pub = rospy.Publisher('twice', Int32,queue_size=1)
    rate = rospy.Rate(1)
    
while not rospy.is_shutdown():
	n += 1
	t = n%10
	pub.publish(t)
	rate.sleep(1000)
