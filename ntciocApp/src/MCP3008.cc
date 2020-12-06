#include <iostream>
#include "MCP3008.h"

#define CHAN_CONFIG_SINGLE  8
#define CHAN_CONFIG_DIFF    0


void spiSetup (int spiChannel){
    int myFd=0;
    if ((myFd = wiringPiSPISetup (spiChannel, 1000000)) < 0){
	std::cout<<"SPI Setup Error"<<std::endl;
	exit (EXIT_FAILURE) ;
    }
}

int read_adc(int spiChannel,int channelConfig,int analogChannel){
    if(analogChannel<0 || analogChannel>7)
	return -1;
    unsigned char buffer[3] = {1}; // start bit
    buffer[1] = (channelConfig+analogChannel) << 4;
    wiringPiSPIDataRW(spiChannel, buffer, 3);
    return ( (buffer[1] & 3 ) << 8 ) + buffer[2]; // get last 10 bits
}


