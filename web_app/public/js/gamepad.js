// // const { request } = require("express");

// // var gamepads = {};
// // function gamepadHandler(event, connecting) {
// //     var gamepad = event.gamepad;

// //     if (connecting) {
// //         gamepads[gamepad.index] = gamepad;
// //     } else {
// //         delete gamepads[gamepad.index];
// //     }
// // }

// // window.addEventListener("gamepadconnected", function(e) {gamepadHandler(e, true); }, false);
// // window.addEventListener("gamepaddisconnected", function(e) {gamepadHandler(e, false); }, false)

// var gamepadInfo = document.getElementById("gamepad-info");
// var ball = document.getElementById("ball");
// var start;
// var a = 0;
// var b = 0;

// window.addEventListener("gamepadconnected", function(e) {
//     var gp = navigator.getGamepads()[e.gamepad.index];
//     gamepadInfo.innerHTML = "Gamepad connected at index " + gp.index + ": " + gp.id + ". It has " + gp.buttons.length + " buttons and " + gp.axes.length + " axes.";
  
//     gameLoop();
//   });
  
//   window.addEventListener("gamepaddisconnected", function(e) {
//     gamepadInfo.innerHTML = "Waiting for gamepad.";
  
//     cancelRequestAnimationFrame(start);
//   });

// var interval;

// if (!('ongamepadconnected' in window)) {
//     // No gamepad events available, poll instead.
//     interval = setInterval(pollGamepads, 500);
//   }

// function pollGamepads() {
    
// }