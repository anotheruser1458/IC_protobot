// file: serial.cpp
// By: Jacob Sequeira

using namespace std;

#include<iostream>
#include<cstdlib>
#include<cstring>
#include<stdint.h>
#include<fcntl.h>
#include<errno.h>
#include<termios.h>
#include<unistd.h>
#include<sys/ioctl.h>
#include<sys/time.h>
#include<assert.h>

/* Define Macros */

/* TODO: convert all macros to enums */

#define SERIAL_PORT  "/dev/ttyS0"   // serial port location
#define BAUD_RATE    B115200        // roboclaw encoder baud rate
#define TIMEOUT_DS   1              // timeout period, 1 ds = 100 ms (not used at the moment)
#define TIMEOUT_MS   12             // Actual encoder timeout, according to this library: https://github.com/bmegli/roboclaw
#define RETRIES      3              // number of retries
#define M1FORWARD    0              // M1 Forward command
#define M2FORWARD    4              // M2 Forward command
#define ROBOCLAW_ACK_BYTES 1        // number of acknowledgement bytes
#define ROBOCLAW_ACK_BYTE  0xFF     // roboclaw acknowledgement byte upon successful command
#define DEBUG                       // debug mode

/* Roboclaw Class */

class Roboclaw {

public:
    Roboclaw();
    void setupEncoders();                                                    // setup motor encoders
    void closeEncoders();                                                    // close encoder connection
    void ForwardM1(uint8_t address, uint8_t value);                          // move M1 Motors
    void ForwardM2(uint8_t address, uint8_t value);                          // move M2 Motors

private:
    int ClearIOBuffers();                                                    // flush I/O buffers
    int Write(uint8_t* data, int nBytes);                                    // write to encoders
    int WaitReadStatus(int nBytes, int timeout_ms);                          // wait for encoders to fill reply data to buffer, returns 1 on success
    int Read(int nBytes);                                                    // read data from encoders buffer
    uint32_t ValidateChecksum(uint8_t* packet, int nBytes);                  // get cyclic redundancy checksum (crc), used to validate 
    int SendCommands(uint8_t* data, int writeBytes, int readBytes);          // send specified commands to encoders
    
    struct termios tty;                                                      // declare serial termios struct, used to configure serial port
    int serialPort;                                                          // roboclaw serial port file descriptor
    //uint8_t readBuf[128];                                                    // read buffer                     
};

/* Roboclaw class constructor */

Roboclaw::Roboclaw() {}

/* Send and execute commands to encoders. Returns -1 or RETRIES on failure, 1 on success. Commands will be sent up to max RETRIES. 
   Successful writes to encoders are then polled to check if data is available to be read back. Once data is available, the data
   is read back, then the user's I/O buffers are cleared. */

/* NOTE: Read() blocks indefinitely, this needs to be fixed. By commenting it out, all commands execute flawlessly. */

int Roboclaw::SendCommands(uint8_t* data, int writeBytes, int readBytes) {

    int r, writeFlag, readFlag, flushFlag, waitStatus;
    
    for(r=0; r<RETRIES; ++r) {

        for( ; r<RETRIES; ++r) {
      
            writeFlag = Write(data, writeBytes);
            if(writeFlag == -1) return -1;
            
                
            waitStatus = WaitReadStatus(readBytes, TIMEOUT_MS); 
    
            if(waitStatus == 1) break; // data is available to be read back
            if(waitStatus == -1 || waitStatus == 0) return -1;
                
            flushFlag = ClearIOBuffers();
            if(flushFlag == -1) return -1;
        }

        if(r >= RETRIES) return -1;
      
        //readFlag = Read(readBytes); // this is blocking indefinitely for some reason
        if(readFlag > 0) return 1;
        if(readFlag == -1) return -1;
            
        assert(readFlag == readBytes);
            
        flushFlag = ClearIOBuffers();
        if(flushFlag == -1) return -1;

        /* TODO: implement checksum decoder to validate data read back from encoders */
    }
    
    return r; // max retries exceeded
}

int Roboclaw::ClearIOBuffers() {
        
    return tcflush(serialPort, TCIOFLUSH);
}

/* Setup Roboclaw motor encoders. Open serial port for reading and writing, configure for 1 stop bit, 8 bits per byte, no parity checking
   as per the roboclaw user manual. Send and receive raw bytes only. Set baud rate of sending and receiving end. */

void Roboclaw::setupEncoders() {

    serialPort = open(SERIAL_PORT, O_RDWR | O_NOCTTY); // enable read & write, disable controlling terminal

    fcntl(serialPort, F_SETFL, 0); // set to blocking mode (for reads)
    // fcntl(serialPort, F_SETFL, FNDELAY); // non-blocking mode (for reads)
    
    if (serialPort < 0) {

        printf("Error %i from open: %s\n", errno, strerror(errno));
        exit(1);
    }
 
    if (tcgetattr(serialPort, &tty) != 0) {

        printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
        exit(1);
    }
    
    // set necessary bits

	tty.c_cflag &= ~PARENB; 	    // disable parity
	tty.c_cflag &= ~CSTOPB; 	    // set 1 stop bit
	tty.c_cflag |= CS8;			    // set 8 bits per byte
	tty.c_cflag &= ~CRTSCTS;	    // Disable RTS/CTS hardware flow control
	tty.c_cflag |= CREAD | CLOCAL;	// enable read from device, ignore ctrl lines

	tty.c_lflag &= ~ICANON;		    // disable canonical mode
	
	// next 4 flags are probably already disabled from above flag

	tty.c_lflag &= ~ECHO;		    // disable echo of commands
	tty.c_lflag &= ~ECHOE;		    // disable erasure
	tty.c_lflag &= ~ECHONL;		    // disable new-line echo
	tty.c_lflag &= ~ISIG;		    // disable special character handling
    
	tty.c_iflag &= ~(IXON | IXOFF | IXANY);
	tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL);

	tty.c_oflag &= ~OPOST;
	tty.c_oflag &= ~ONLCR;

	tty.c_cc[VTIME] = 0;            // set min timeout period
	tty.c_cc[VMIN] = 1;             // set min number of characters to be read in

    // set baud rates
    
	cfsetispeed(&tty, BAUD_RATE);
	cfsetospeed(&tty, BAUD_RATE);

	// save flag settings

	if(tcsetattr(serialPort, TCSANOW, &tty) != 0)
			printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
}

/* Close serial port file descriptor. */

void Roboclaw::closeEncoders() {

    close(serialPort);
}

/* Write commands to encoders, check flag status. Returns number of bytes successfully sent to encoders (writeFlag > 0).
   Returns -1 on failure. */

int Roboclaw::Write(uint8_t* data, int nBytes) {

    int result;
    int written = 0;
    
    while(written < nBytes) {
        result = write(serialPort, data + written, nBytes - written);
        if(result == -1) return -1;
        written += result;
    }
    
    return written;
}

/* Check to see if roboclaw encoders sent back data (ACK byte, encoder data, etc.). Poll serial port to check that
   data is available to be read back, within the specified timeout period. Returns 1 on success. Otherwise, 
   return 0 or -1 signifying an error. */

int Roboclaw::WaitReadStatus(int nBytes, int timeout_ms) {

    struct timeval tv;              // from sys/time.h, used to set timeout for roboclaw reads
    fd_set input;                   // contains all file descriptors used
    int ret;                        // select flag
    
    FD_ZERO(&input);                // initialize file descriptors
    FD_SET(serialPort, &input);     // set file descriptors
    
    tv.tv_sec = 0;
    tv.tv_usec = timeout_ms*1000;   // set timeout period
    
    if(tty.c_cc[VMIN] != nBytes) {
    
        tty.c_cc[VMIN] = nBytes;    // set minimum number of bytes to be read in

        if(tcsetattr(serialPort, TCSANOW, &tty) < 0) 
            return -1; // save settings, return -1 if tyheres an error
    }
    
    ret = select(serialPort + 1, &input, NULL, NULL, &tv);

    if (FD_ISSET(serialPort, &input))
        return 1;
    
    return ret; // error, will return either 0 or -1. check errno
    int bytesAvailable = 0;
    
    int flag = ioctl(serialPort, FIONREAD, &bytesAvailable);
cout << "flag: " << flag << endl;
    return bytesAvailable;

    if(ret < 0) return ret;
	
	if(ret ==0) return 0;
	
	return 1;

}

/* Reads available data from roboclaw buffer. returns the number of bytes specified by the user upon success (readFlag > 0). 
   Returns -1 upon failure. */

int Roboclaw::Read(int nBytes) {

    uint8_t buf[nBytes];            // declare buffer size

    for(int i=0; i<nBytes; i++)     // initialize buffer
        buf[i] = 0x00;
        
    //fcntl(serialPort, F_SETFL, FNDELAY); // non-blocking mode (for reads)

    int readFlag = read(serialPort, &buf, nBytes); // ***This is the problematic line!
    
    //fcntl(serialPort, F_SETFL, 0); // set to blocking mode (for reads)
    
    printf("readFlag: %d Read: ", readFlag);
    
    for(int i=0; i<nBytes; i++)
        printf("0x%X ", buf[i]);
    putchar('\n');


    if (readFlag != nBytes)
        return -1;
 cout << "serialPort " << serialPort << endl;   
    return readFlag;
}

/* Get checksum calculation. the Checksum is calculated using Cyclic Redundancy Check (CRC), which uses the encoder address, 
   commands and data sent to the encoders. Valid commands will be executed by the encoder, invalid commands will be discarded. */

uint32_t Roboclaw::ValidateChecksum(uint8_t* packet, int nBytes) {

    int crc = 0;
    int byte;
    uint8_t bit;
    
    for(byte=0; byte<nBytes; byte++) {

        crc = crc ^ ((uint32_t)packet[byte] << 8);

        for(bit=0; bit<8; ++bit) {

            if(crc & 0x8000) {

                crc = (crc << 1) ^ 0x1021;

            } else {

                crc = crc << 1;
            }
        }
    }

    return crc;
}

/* Move M1 motors. specify the motor address and desired speed value (0-127), then get checksum. Set commands 
   and checksum in an array, send commands to be executed. */

void Roboclaw::ForwardM1(uint8_t address, uint8_t value) {

    uint8_t get_crc[3] = {address, M1FORWARD, value}; 
    uint8_t data[5];

    uint16_t crc = ValidateChecksum(get_crc, 3);
    
    for(int i=0; i<3; i++)
        data[i] = get_crc[i];
        
    data[3] = crc >> 8;
    data[4] = crc;
    
    int cmdFlag = SendCommands(data, 5, 1);

}

/* Move M2 motors. specify the motor address and desired speed value (0-127), then get checksum. Set commands
   and checksum in an array, send commands to be executed. */

void Roboclaw::ForwardM2(uint8_t address, uint8_t value) {

    uint8_t get_crc[3] = {address, M2FORWARD, value};
    uint8_t data[5];
    
    uint16_t crc = ValidateChecksum(get_crc, 3);
    
    for(int i=0; i<3; i++)
        data[i] = get_crc[i];
        
    data[3] = crc >> 8;
    data[4] = crc;
    
    int cmdFlag = SendCommands(data, 5, 1);
}

int main(int argc, char **argv) {

    Roboclaw rb;
    
    rb.setupEncoders();
    
    rb.ForwardM1(0x80, 30);

    sleep(2);

    rb.ForwardM1(0x80, 0);
    
    rb.closeEncoders();

	return 0;
}
