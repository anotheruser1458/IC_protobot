#include "ros/ros.h"
#include "std_msgs/Int64.h"

void scoreCallback(const std_msgs::Int64::ConstPtr& msg) {
    ROS_INFO("I herd: [%ld]", msg->data);
}

int main(int argc, char **argv){
    ros::init(argc, argv, "score_listener");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("score", 1000, scoreCallback);
    ros::spin();

    return 0;
}