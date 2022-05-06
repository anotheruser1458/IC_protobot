import React from 'react'
import { roundWithPrecision } from '../util/roundData'
import sleep from "../util/sleep"

export default function Imu(props) {
    var topic = new ROSLIB.Topic({
        ros: props.ros,
        name: props.name
    })

    const lax = props.title+"linAccX"
    const lay = props.title+"linAccY"
    const laz = props.title+"linAccZ"

    const avx = props.title+"angVelX"
    const avy = props.title+"angVelY"
    const avz = props.title+"angVelZ"

    topic.subscribe((m) => {

    sleep(1000);
    const angular_velocity = m.angular_velocity
    const angular_velocity_covariance = m.angular_velocity_covariance
    const linear_acceleration = m.linear_acceleration
    const linear_acceleration_covariance = m.linear_acceleration_covariance
    const orientation = m.orientation
    const orientation_covariance = m.orientation_covariance


    document.getElementById(lax).innerHTML = roundWithPrecision(linear_acceleration.x, 3)
    document.getElementById(lay).innerHTML = roundWithPrecision(linear_acceleration.y, 3)
    document.getElementById(laz).innerHTML = roundWithPrecision(linear_acceleration.z, 3)

    document.getElementById(avx).innerHTML = roundWithPrecision(angular_velocity.x, 3)
    document.getElementById(avy).innerHTML = roundWithPrecision(angular_velocity.y, 3)
    document.getElementById(avz).innerHTML = roundWithPrecision(angular_velocity.z, 3)
})



  return (
        <>
            <h2>Linear Acceleration:</h2>
            <p>X: <i id={lax}>0</i></p>
            <p>Y: <i id={lay}>0</i></p>
            <p>Z: <i id={laz}>0</i></p>

            <h2>Angular Velocity:</h2>
            <p>X: <i id={avx}>0</i></p>
            <p>Y: <i id={avy}>0</i></p>
            <p>Z: <i id={avz}>0</i></p>
        </>
    )
}
