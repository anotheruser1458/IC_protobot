var ros = new ROSLIB.Ros({
    url:"ws://localhost:9090"
})

var odometry_listener = new ROSLIB.Topic({
    ros:ros,
    name:"/odom_test_topic",
    messageType: "nav_msgs/Odometry"
})

odometry_listener.subscribe((m) => {
    document.getElementById("childFrame").innerHTML = "Child Frame ID: " + m.child_frame_id;
    document.getElementById("posePositionX").innerHTML = "Position X: " + m.pose.pose.position.x;
    document.getElementById("posePositionY").innerHTML = "Position Y: " + m.pose.pose.position.y;
    document.getElementById("posePositionZ").innerHTML = "Position Z: " + m.pose.pose.position.z;
    document.getElementById("poseOrientationX").innerHTML = "Orientation X: " + m.pose.pose.orientation.x;
    document.getElementById("poseOrientationY").innerHTML = "Orientation Y: " + m.pose.pose.orientation.y;
    document.getElementById("poseOrientationZ").innerHTML = "Orientation Z: " + m.pose.pose.orientation.z;
    document.getElementById("poseOrientationW").innerHTML = "Orientation W: " + m.pose.pose.orientation.w;
    document.getElementById("twistLinearX").innerHTML = "Linear X: " + m.twist.twist.linear.x;
    document.getElementById("twistLinearY").innerHTML = "Linear Y: " + m.twist.twist.linear.y;
    document.getElementById("twistLinearZ").innerHTML = "Linear Z: " + m.twist.twist.linear.z;
    document.getElementById("twistAngularX").innerHTML = "Angular X: " + m.twist.twist.angular.x;
    document.getElementById("twistAngularY").innerHTML = "Angular Y: " + m.twist.twist.angular.y;
    document.getElementById("twistAngularZ").innerHTML = "Angular Z: " + m.twist.twist.angular.z;

})