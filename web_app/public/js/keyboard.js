var keyboardTopic = new ROSLIB.Topic({
    ros:ros,
    name: "/cmd_vel"
})

keyboardTopic.subscribe((m) => {
    console.log(m.linear.x)
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