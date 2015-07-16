#!bin/linux-x86_64/functino

epicsEnvSet("STREAM_PROTOCOL_PATH", "functinoApp/Db")

dbLoadDatabase("dbd/functino.dbd",0,0)
functino_registerRecordDeviceDriver(pdbbase)

drvAsynSerialPortConfigure("FUNCTINO", "/dev/ttyACM0")
asynSetOption("FUNCTINO", 0, "baud", 57600)

#asynSetTraceMask("FUNCTINO", -1, 0x9)
#asynSetTraceIOMask("FUNCTINO", -1, 0x2)

dbLoadTemplate("db/functino.substitutions")

iocInit()
