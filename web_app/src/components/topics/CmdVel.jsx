import React from 'react'
import Vector3CmdVel from '../messages/geometry_msgs/Vector3CmdVel'

export default function CmdVel(props) {
  return (
      <>
    <h2>Linear:</h2>
    <Vector3CmdVel ros={props.ros} name={props.name} title="linear"/>
    <h2>Angular:</h2>
    <Vector3CmdVel ros={props.ros} name={props.name} title="angular" />
    </>
    )
}