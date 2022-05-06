//imports
const express = require("express")
const app = express()
const path = require("path")
const ROSLIB = require("roslib")

//server config
app.use(express.json())
app.use(express.urlencoded())
app.use(express.static("public"))

// roslib
var ros = new ROSLIB.Ros({
    url: 'ws://168.105.224.55:9090'
})

ros.on('connection', () => {
    console.log("Connected to web socket server.")
})

var scoreTopic = new ROSLIB.Topic({
    ros:ros,
    name:'/score',
    messageType: 'std_msgs/Int64'
})


// paths
app.get("/", (req, res) => {
    res.sendFile(path.join(__dirname, "index.html"))
})

app.post('/', (req, res) => {
    num = parseInt(req.body.num_data)
    message = new ROSLIB.Message({
        data:num
    })
    scoreTopic.publish(message)
    res.sendFile(path.join(__dirname, "index.html"))
})



app.listen(3000, ()=> {console.log('now listening on port 3000')})