import React from "react"
import Box from "@mui/material/Box"

const boxStyle = {
    margin: 5,
}
const Home = () => {
    return (
        <>
        <Box style={boxStyle} sx={{border: 3, borderRadius: 3, borderColor: "divider"}}> 
        <h1>Video Feed Box</h1>
        </Box >
        <Box style={boxStyle} sx={{border: 3, borderRadius: 3, borderColor: "divider"}}>
        <h1>Data Box</h1>
        </Box>
        </>
    )
}

export default Home