//URL for ROS message
//http://docs.ros.org/en/api/nav_msgs/html/msg/Odometry.html

import React from 'react'
import { roundWithPrecision } from '../../util/roundData'


export default function Odometry(props) {
    var topic = new ROSLIB.Topic({
      ros: props.ros,
      name: props.topicName
    })

    topic.subscribe((m) => {
    })

    return (
      <h3>{props.title} Odometry</h3>
    )
}