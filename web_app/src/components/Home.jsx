import React from "react"
import Box from "@mui/material/Box"
import VideoFeed from "./VideoFeed"
const boxStyle = {
    margin: 10,
    display: "flex",
    alignContent: "center",
    justifyContent: "space-evenly",

}
const Home = () => {
    return (
        <>
        <Box style={boxStyle} sx={{border: 3, borderRadius: 3, borderColor: "divider"}}> 
            <VideoFeed url="http://localhost:8080/stream?topic=/image_raw" alt="webcam1"/>
            <VideoFeed url="http://localhost:8080/stream?topic=/image_raw" alt="webcam1"/>
        </Box >
        <Box style={boxStyle} sx={{border: 3, borderRadius: 3, borderColor: "divider"}}>
        <h1>Data Box</h1> 
        <h1>test</h1>
        </Box>
        </>
    )
}

export default Home