#include <stddef.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

#include "epicsExit.h"
#include "epicsThread.h"
#include "iocsh.h"

#include <thread>
#include <atomic>

#include "ntc.h"

int main(int argc,char *argv[])
{
    if(argc>=2) {    
	iocsh(argv[1]);
	epicsThreadSleep(.2);
    }

    std::atomic_uchar thread_run;
    std::thread reader(read_ntc, std::ref(thread_run));

    iocsh(NULL);

    thread_run = 0;
    reader.join();

    epicsExit(0);
    return(0);
}
