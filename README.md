# guiPrototype

## It can do this

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
http://localhost:8000
