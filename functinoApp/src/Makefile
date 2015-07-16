TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#=============================
# Build the IOC application

PROD_IOC = functino
DBD += functino.dbd

functino_DBD += base.dbd
functino_DBD += asyn.dbd
functino_DBD += drvAsynSerialPort.dbd
functino_DBD += stream.dbd
functino_DBD += calcSupport.dbd

# functino_registerRecordDeviceDriver.cpp derives from functino.dbd
functino_SRCS += functino_registerRecordDeviceDriver.cpp

# Build the main IOC entry point on workstation OSs.
functino_SRCS_DEFAULT += functinoMain.cpp
functino_SRCS_vxWorks += -nil-

# Finally link to the EPICS Base libraries
functino_LIBS += $(EPICS_BASE_IOC_LIBS)
functino_LIBS += asyn
functino_LIBS += stream
functino_LIBS += calc

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE
