#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <iostream>

#define SERIAL_PORT "/dev/ttyS0"


int main() {
int serial_port = open(SERIAL_PORT, O_RDWR);
if (serial_port < 0) {
printf("Error %i from open: %s\n", errno, strerror(errno));
}
	return 0;
}
