import * as React from 'react';
import PropTypes from 'prop-types';
import Tabs from '@mui/material/Tabs';
import Tab from '@mui/material/Tab';
import Typography from '@mui/material/Typography';
import Box from '@mui/material/Box';
import CmdVel from './topics/CmdVel';
import Imu from "./messages/Imu"
import GPSFix from './messages/gps_common/GPSFix';

function TabPanel(props) {
  const { children, value, index, ...other } = props;

  return (
    <div
      role="tabpanel"
      hidden={value !== index}
      id={`simple-tabpanel-${index}`}
      aria-labelledby={`simple-tab-${index}`}
      {...other}
    >
      {value === index && (
        <Box sx={{ p: 3 }}>
          <Typography>{children}</Typography>
        </Box>
      )}
    </div>
  );
}

TabPanel.propTypes = {
  children: PropTypes.node,
  index: PropTypes.number.isRequired,
  value: PropTypes.number.isRequired,
};

function a11yProps(index) {
  return {
    id: `simple-tab-${index}`,
    'aria-controls': `simple-tabpanel-${index}`,
  };
}

export default function DataPanel(props) {
  const [value, setValue] = React.useState(0);

  const handleChange = (event, newValue) => {
    setValue(newValue);
  };

  var ros = new ROSLIB.Ros({
    url: "ws://168.105.224.55:9090"
  })

  return (
    <Box sx={{ width: '100%' }}>
      <Box sx={{ borderBottom: 1, borderColor: 'divider' }}>
        <Tabs value={value} onChange={handleChange}>
          <Tab label="Cmd_Vel" {...a11yProps(0)} />
          <Tab label="Topic 2" {...a11yProps(1)} />
          <Tab label="Topic 3" {...a11yProps(2)} />
        </Tabs>
      </Box>
      
      {/* CMD_VEL */}

        <TabPanel value={value} index={0}>
          <h2>/protobot_velocity_controller/cmd_vel</h2>
            <CmdVel ros={ros} name={"/protobot_velocity_controller/cmd_vel"}/>
          <br></br>

          <h2>/track_cam/imu</h2>
          <Imu ros={ros} title={"trackCam"} name={"/track_cam/imu"}/>
          <br></br>

          <h2>/depth_cam/imu</h2>
          <Imu ros={ros} title={"depthCam"} name={"/depth_cam/imu"}/>
          <br></br>

          {/* <GPSFix ros={ros} /> */}
        </TabPanel>

        <TabPanel value={value} index={1}>
          Item Two
        </TabPanel>
        <TabPanel value={value} index={2}>
          Item Three
        </TabPanel>
    </Box>
  );
}