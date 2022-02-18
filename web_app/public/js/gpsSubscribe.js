
var gps_listener = new ROSLIB.Topic({
    ros:ros,
    name:"/gps_fix_test_topic",
    messageType: "gps_common/GPSFix"
})

gps_listener.subscribe((m) => {
    document.getElementById("status").innerHTML = "Status: " + m.status.status
    document.getElementById("satellitesUsed").innerHTML = "Status: " + m.status.satellites_used
    document.getElementById("motionSource").innerHTML = "Status: " + m.status.motion_source
    document.getElementById("latitude").innerHTML = "Latitude: " + m.latitude
    document.getElementById("longitude").innerHTML = "Longitude: " + m.longitude
    document.getElementById("altitude").innerHTML = "Altitude: " + m.altitude
    document.getElementById("dip").innerHTML = "Dip: " + m.dip
})
