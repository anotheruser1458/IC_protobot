#include "ros/ros.h"
#include "gps_common/GPSFix.h"
#include "gps_common/GPSStatus.h"

int main(int argc, char** argv) {
    ros::init(argc, argv, "gps_fix_test_pub");
    ros::NodeHandle n;
    ros::Publisher gps_pub = n.advertise<gps_common::GPSFix>("gps_fix_test_topic", 1000);
    ros::Rate loop_rate(10);
    while(ros::ok()) {
        gps_common::GPSFix gps_msg;

        gps_common::GPSStatus gps_status;
        gps_status.status = 3;
        gps_status.satellites_used = 10;
        gps_status.motion_source = 4;
        gps_msg.status = gps_status;

        gps_msg.latitude = 20.457;
        gps_msg.longitude = 15.23;
        gps_msg.altitude = 38.3;
        gps_msg.track = 32;
        gps_msg.speed = 83;
        gps_msg.climb = 38;
        gps_msg.pitch = 8;
        gps_msg.roll = 3;
        gps_msg.dip = 88;
        gps_msg.time = 83;
        gps_msg.gdop = 32;
        gps_msg.pdop = 89;

        gps_pub.publish(gps_msg);

        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}