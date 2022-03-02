//URL for ROS message
//http://docs.ros.org/en/noetic/api/geometry_msgs/html/msg/Vector3.html

import React, {useState} from 'react'
import { roundWithPrecision } from '../../util/roundData'

// props.title can only be 'angular' or 'linear' or it will break
export default function Vector3(props) {

  var cmd_vel_topic = new ROSLIB.Topic({
    ros: props.ros,
    name: "/cmd_vel"
  })
  
  const nameX = props.title + "X"
  const nameY = props.title + "Y"
  const nameZ = props.title + "Z"

  cmd_vel_topic.subscribe((m) => {
    // @todo rounding errors of small decimal increments cause
    // infinite state reset, need to do some type of rounding then compare
    var data = m[props.title]

    document.getElementById(nameX).innerHTML = roundWithPrecision(data.x, 3)
    document.getElementById(nameY).innerHTML = roundWithPrecision(data.y, 3)
    document.getElementById(nameZ).innerHTML = roundWithPrecision(data.z, 3)
  })


  return (
      <>
      <h3>{props.title}</h3>
      <p>{nameX}: <i id={nameX}>0</i></p>
      <p>{nameY}: <i id={nameY}>0</i></p>
      <p>{nameZ}: <i id={nameZ}>0</i></p>
    </>
  )
}

