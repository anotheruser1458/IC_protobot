import React from 'react'

const imageStyle = {
    margin: 10,
    width: "40%",
}

export default function VideoFeed(props) {
  return (
    <img style={imageStyle} src={props.url} alt={props.alt}/>
  )
}