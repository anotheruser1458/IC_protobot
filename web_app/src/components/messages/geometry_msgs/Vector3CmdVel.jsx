//URL for ROS message
//http://docs.ros.org/en/noetic/api/geometry_msgs/html/msg/Vector3.html

import React, {useState} from 'react'
import { roundWithPrecision } from '../../util/roundData'

// props.title can only be 'angular' or 'linear'
export default function Vector3CmdVel(props) {


  var topic = new ROSLIB.Topic({
    ros: props.ros,
    name: props.name
  })
  
  const nameX = props.title + "X"
  const nameY = props.title + "Y"
  const nameZ = props.title + "Z"

  topic.subscribe((m) => {
    var data = m[props.title]
    document.getElementById(nameX).innerHTML = roundWithPrecision(data.x, 3)
    document.getElementById(nameY).innerHTML = roundWithPrecision(data.y, 3)
    document.getElementById(nameZ).innerHTML = roundWithPrecision(data.z, 3)
  })
  return (
      <>
      <p>X: <i id={nameX}>0</i></p>
      <p>Y: <i id={nameY}>0</i></p>
      <p>Z: <i id={nameZ}>0</i></p>
    </>
  )
}

