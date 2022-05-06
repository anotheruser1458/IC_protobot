import React from "react"
import Box from "@mui/material/Box"
import VideoFeed from "./VideoFeed"
import DataPanel from "./DataPanel"

const videoBoxStyle = {
    margin: 10,
    display: "flex",
    alignContent: "center",
    justifyContent: "space-evenly",
}

const Home = () => {
    return (
        <>
        <Box style={videoBoxStyle} sx={{border: 3, borderRadius: 3, borderColor: "divider"}}> 
            {/* <VideoFeed url="http://localhost:8080/stream?topic=/image_raw" alt="webcam1"/>
            <VideoFeed url="http://localhost:8080/stream?topic=/image_raw" alt="webcam1"/> */}
        </Box >
        <DataPanel />
        </>
    )
}

export default Home