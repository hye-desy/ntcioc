#!../../bin/linux-arm/ntcioc

## You may have to change ntcioc to something else
## everywhere it appears in this file

< envPaths

cd ${TOP}

## Register all support components
dbLoadDatabase "dbd/ntcioc.dbd"
ntcioc_registerRecordDeviceDriver pdbbase

## Load record instances
dbLoadRecords "db/ntc.db", "user=PXD"

## Set this to see messages from mySub
#var mySubDebug 1

## Run this to trace the stages of iocInit
#traceIocInit

cd ${TOP}/iocBoot/${IOC}
iocInit

## Start any sequence programs
#seq sncExample, "user=piHost"
