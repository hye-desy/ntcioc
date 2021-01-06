#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>

#include <atomic>
#include <thread>
#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>

#include <wiringPi.h>
#include <wiringPiSPI.h>

#include "gpios.h"
#include "MCP3008.h"
#include "NTC10kOhm.h"
#include "result.h"
#include "ntc.h"

using std::uint32_t;

#define SLEEPTIME  2

void read_ntc(std::atomic_uchar &run){

    run = 1;

    const std::string export_str("/sys/class/gpio/export");
    const std::string unexport_str("/sys/class/gpio/unexport");
    const std::string gpio_str("/sys/class/gpio/gpio");
    for(uint32_t i=0; i<gpio.size(); i++){
	std::ofstream of_exp(export_str);
	of_exp << gpio[i];
    }
    std::this_thread::sleep_for (std::chrono::seconds(4));
    for(uint32_t i=0; i<gpio.size(); i++){
	std::ofstream of_dir(gpio_str+std::to_string(gpio[i])+"/direction");
	of_dir << "out";
	of_dir.close();
	std::this_thread::sleep_for (std::chrono::seconds(1));
	std::ofstream of_val(gpio_str+std::to_string(gpio[i])+"/value");
	if(i == 0)
	    of_val << "0";
	else
	    of_val << "1";
    }

    wiringPiSetup () ;

    uint32_t value;
    float temp[8];
    int spiChannel = 0;
    int channelConfig=CHAN_CONFIG_SINGLE;

    uint32_t i = 0;  

    time_t timev;

    spiSetup(spiChannel);

    while(run){

	//  read ntc
	for (int chan=0; chan<8; chan++) {

	    std::ofstream of_gpio(gpio_str+std::to_string(gpio[i])+"/value");
	    of_gpio << "0";
	    of_gpio.close();

	    time(&timev);
	    value = read_adc(spiChannel,channelConfig,chan);
	    if(value>0){
		temp[chan]=ThermistorCal(value);
	    }
	    else{
		temp[chan]=0;
	    }

	    std::ofstream of_gpio_xx(gpio_str+std::to_string(gpio[i])+"/value");
	    of_gpio_xx << "1";
	    of_gpio_xx.close();

	}

	result r;
	r.ch0 = temp[0];
	r.ch1 = temp[1];
	r.ch2 = temp[2];
	r.ch3 = temp[3];
	r.ch4 = temp[4];
	r.ch5 = temp[5];
	r.ch6 = temp[6];
	r.ch7 = temp[7];
	r.ok = true;
	result_list::instance()->update_result(gpio[i], std::move(r));

	i++;
	if(i == gpio.size()){ 
	    i=0;
	    std::this_thread::sleep_for (std::chrono::seconds(SLEEPTIME));
	}

    }

}

