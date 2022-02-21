var keyboardTopic = new ROSLIB.Topic({
    ros:ros,
    name: "/cmd_vel"
})

keyboardTopic.subscribe((m) => {
    x = String(m.linear.x.toFixed(2))
    lx= String(m.angular.x.toFixed(2))
    document.getElementById("linearX").innerHTML = "LinearX: " + x
    document.getElementById("linearY").innerHTML = "LinearY: " + m.linear.y
    document.getElementById("linearZ").innerHTML = "LinearZ: " + m.linear.z
    document.getElementById("angularX").innerHTML = "AngularX: " + lx
    document.getElementById("angularY").innerHTML = "AngularY: " + m.linear.y
    document.getElementById("angularZ").innerHTML = "AngularZ: " + m.linear.z
})

var message;
var linear = {x:0, y:0, z:0};
var angular = {x:0, y:0, z:0};
console.log(linear, angular);
window.addEventListener("keydown", function(e){
    if (e.defaultPrevented) {
        return;
    }
    switch(e.key) {
        case "ArrowDown":
            linear.x -= 0.1;
            message = new ROSLIB.Message({
                linear:linear,
                angular:angular
            })
            keyboardTopic.publish(message);
            console.log("down message published");
            break;

        case "ArrowUp":
            linear.x += 0.1;
            message = new ROSLIB.Message({
                linear:linear,
                angular:angular
            })
            keyboardTopic.publish(message);
            console.log("up message published");
            break;
        case "ArrowLeft":
            console.log("arrow left");
            break;
        case "ArrowRight":
            console.log("Arrow right");
            break;

    }
})