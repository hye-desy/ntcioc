#include <math.h>

#include "NTC10kOhm.h"


float VoltageCal(int value){
    float V=float(value)/1024.0*3.3;
    return V;
}

float ResisCal(int value){
    float V=VoltageCal(value);
    float R;
    if(V>0.1&&V<3.2)
	R=12000*(3.3-V)/V;
    else
	R=1;
    return R;
}

float ThermistorCal(int value){
    float A=0.9017477480e-3;
    float B=2.489190310e-4;
    float C=2.043213857e-7;

    float R=ResisCal(value);

    float T=1.0/(A+B*log(R)+C*pow(log(R),3))-273;

    return T;
}

