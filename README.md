# IC_protobot

## Overview

This is a clone of the shared project repository made by the members of the University of Hawaii Robotic Space Exploration Team(link). Our team's goal is to creat a six wheeled robot that can drive, operate a manipulator arm, detect life, and autonomously navigate which we will officially enter into the University Rover Challenge(link), June 2022. This repository contains the software module prototypes which we worked diligently on in order to prove the architectural concepts laid out in our Critical Design Review(link).

Contributors: Maxwell Pauly, Bret Witt, Ashten Akemoto, Jacob Sequeira, Jeraldine Milla, Stephanie Alemore, and Zolbo Tomita.

## Robot Operating System (ROS)

ROS is an open source robotics middleware suite and is the premier framework for robotic rapid prototyping. The ROS wiki(link) is an outstanding resource to learn more so I won't go into detail here. The project uses ROS for the majority of the robot's communication between components and functionality. Each software developer on the project completed the ROS Tutorials(link) and below is a demonstration of ROS nodes talking to one another and executing commands.


https://user-images.githubusercontent.com/74911365/154920396-d8579ff4-1784-4360-8b3e-b7f285558c4d.mp4



## Gazebo Simulation

## Web App Graphical User Interface

<!-- 
https://user-images.githubusercontent.com/74911365/140019513-80895195-2fa0-49e1-8030-edcdf03711ba.mp4

## Dependencies
### sudo apt update
### sudo apt upgrade
### sudo apt-get install ros-noetic-rosbridge-suite
### sudo apt-get install ros-noetic-rosbridge-server
### sudo apt install nodejs npm


## To get it to work:

### Terminal 1 (runs ros core through the rosbridge (web socket package) launch file):

cd catkin_ws
source devel/setup.bash
roslaunch rosbridge_server rosbridge_websocket.launch

### Terminal 2 (runs the package I made that listens to /score topic which uses std_msgs/Int64 messages):
cd catkin_ws
source devel/setup.bash
rosrun listener_package score_listener

### Terminal 3 (runs the web app):
cd webapp
npm install
npm run dev

### Web Browser:
http://localhost:8000 -->

## Motor Encoders
<script src="https://gist.github.com/anotheruser1458/6c4cc14e8b29b6d2e9777a6b1872d5c9.js"></script>

## Arm Simulation
