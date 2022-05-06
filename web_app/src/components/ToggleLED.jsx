import React, {useState} from 'react'

const buttonStyle = {
    width: "100px",
    height: "50px",
    margin: "10px",
}

export default function ToggleLED(props) {

    const [roverStatus, setStatus] = useState("Unknown")
    const statusObject = {
        green: "Success",
        red: "Autonomous",
        blue: "Teleoperation",
        off: "Off"
    }

    const toggleLED = new ROSLIB.Service({
        ros: props.ros,
        name: "/LED_toggle_server",
        serviceType: 'protobot_hardware/LED_toggle'
    })
    
    var requestOff = new ROSLIB.ServiceRequest({
        service_name: "/LED_toggle_server",
        LED_toggle: 4
    })
    
    var requestBlue = new ROSLIB.ServiceRequest({
        service_name: "LED_toggle_server",
        LED_toggle: 3
    })
    
    var requestRed = new ROSLIB.ServiceRequest({
        service_name: "LED_toggle_server",
        LED_toggle: 2
    })
    
    var requestGreen = new ROSLIB.ServiceRequest({
        service_name: "LED_toggle_server",
        LED_toggle: 1
    })
    
    var consoleLogResult = (result) => {
        console.log(result)
    }
    
    var requestLED = (num) => {
        switch(num) {
            case 1: 
                toggleLED.callService(requestGreen, consoleLogResult); 
                setStatus(statusObject.green)
                break;
            case 2: 
                toggleLED.callService(requestRed, consoleLogResult); 
                setStatus(statusObject.red)
                break;
            case 3: toggleLED.callService(requestBlue, consoleLogResult); 
                    setStatus(statusObject.blue)
                    break;
            case 4: 
                    toggleLED.callService(requestOff, consoleLogResult); 
                    setStatus(statusObject.off)
                    break;
        }
    }
    
  return (
        <>
            <h2>Rover Status: <i id="status">{roverStatus}</i></h2>
            <div>
                <button style={buttonStyle} onClick={() => {requestLED(1)}}>Green</button>
                <button style={buttonStyle} onClick={() =>{requestLED(2)}}>Red</button>
                <button style={buttonStyle} onClick={() => {requestLED(3)}}>Blue</button>
                <button style={buttonStyle} onClick={() => {requestLED(4)}}>Off</button>
            </div>
            
        </>
    )
}
