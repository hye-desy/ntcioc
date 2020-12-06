#pragma once

#include <wiringPi.h>
#include <wiringPiSPI.h>

#define CHAN_CONFIG_SINGLE  8
#define CHAN_CONFIG_DIFF    0

void spiSetup (int spiChannel);
int read_adc(int spiChannel,int channelConfig,int analogChannel);
