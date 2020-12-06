TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE

##=============================
## Build the IOC support library
#
#LIBRARY_IOC += ntciocSupport
#
## xxxRecord.h will be created from xxxRecord.dbd
#DBDINC += xxxRecord
## Install devXxxSoft.dbd into <top>/dbd
#DBD += xxxSupport.dbd
#
## Compile and add the code to the support library
#ntciocSupport_SRCS += xxxRecord.c
#ntciocSupport_SRCS += devXxxSoft.c
#
## Link locally-provided code into the support library,
## rather than directly into the IOC application.
#ntciocSupport_SRCS += dbSubExample.c
#ntciocSupport_SRCS += ntciocHello.c
#ntciocSupport_SRCS += initTrace.c
#
#ntciocSupport_LIBS += $(EPICS_BASE_IOC_LIBS)

#=============================
# Build the IOC application

PROD_IOC = ntcioc
# ntcioc.dbd will be created and installed
DBD += ntcioc.dbd

# ntcioc.dbd will be made up from these files:
ntcioc_DBD += base.dbd
ntcioc_DBD += ntcdev.dbd

# ntcioc_registerRecordDeviceDriver.cpp derives from ntcioc.dbd
ntcioc_SRCS += ntcioc_registerRecordDeviceDriver.cpp
ntcioc_SRCS += device.cc
ntcioc_SRCS += gpios.cc
ntcioc_SRCS += result.cc
ntcioc_SRCS += NTC10kOhm.cc
ntcioc_SRCS += MCP3008.cc
ntcioc_SRCS += ntc.cc

# Build the main IOC entry point on workstation OSs.
ntcioc_SRCS_DEFAULT += ntciocMain.cpp
ntcioc_SRCS_vxWorks += -nil-

USR_CXXFLAGS += -std=c++11 -O3 -Wall

# Add support from base/src/vxWorks if needed
#ntcioc_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

## Link in the code from the support library
#ntcioc_LIBS += ntciocSupport
#
## NOTE: To build SNL programs, SNCSEQ must be defined
## in the <top>/configure/RELEASE file
#
#ifneq ($(SNCSEQ),)
#    # Build sncExample into ntciocSupport
#    sncExample_SNCFLAGS += +r
#    ntcioc_DBD += sncExample.dbd
#    ntciocSupport_SRCS += sncExample.stt
#    ntciocSupport_LIBS += seq pv
#    ntcioc_LIBS += seq pv
#
#    # Build sncProgram as a standalone program
#    PROD_HOST += sncProgram
#    sncProgram_SNCFLAGS += +m
#    sncProgram_SRCS += sncProgram.st
#    sncProgram_LIBS += seq pv
#    sncProgram_LIBS += $(EPICS_BASE_HOST_LIBS)
#endif

# Finally link to the EPICS Base libraries
ntcioc_LIBS += $(EPICS_BASE_IOC_LIBS)

ntcioc_SYS_LIBS += pthread
ntcioc_SYS_LIBS += wiringPi

#=============================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

