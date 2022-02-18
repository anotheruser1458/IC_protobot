#include "ros/ros.h"
#include "nav_msgs/Odometry.h"
#include "boost/array.hpp"

int main(int argc, char** argv) {
    ros::init(argc, argv, "odom_test_pub");
    ros::NodeHandle n;
    ros::Publisher odom_pub = n.advertise<nav_msgs::Odometry>("odom_test_topic", 1000);
    ros::Rate loop_rate(10);
    while (ros::ok()) {
        nav_msgs::Odometry odom_msg;
        boost::array<_Float64, 36> cov1;
        cov1[0] = 3.4;
        cov1[1] = 38.3;
        boost::array<_Float64, 36> cov2;
        cov2[0] = 5.9;
        cov2[1] = 8.2;

        odom_msg.child_frame_id = "child_frame_id";
        odom_msg.pose.covariance = cov1;
        odom_msg.pose.pose.position.x = 2;
        odom_msg.pose.pose.position.y = 3;
        odom_msg.pose.pose.position.z = 4;
        odom_msg.pose.pose.orientation.x = 5;
        odom_msg.pose.pose.orientation.y = 6;
        odom_msg.pose.pose.orientation.z = 7;
        odom_msg.pose.pose.orientation.w = 8;

        odom_msg.twist.covariance = cov2;
        odom_msg.twist.twist.linear.x = 9;
        odom_msg.twist.twist.linear.y = 10;
        odom_msg.twist.twist.linear.z = 11;
        odom_msg.twist.twist.angular.x = 12;
        odom_msg.twist.twist.angular.y = 13;
        odom_msg.twist.twist.angular.z = 14;
        
        odom_pub.publish(odom_msg);
        
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}