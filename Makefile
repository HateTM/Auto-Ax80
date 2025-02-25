# Makefile for nvrammngr lib.
# This lib is needed for tplink firmware recovery function support.
#


obj-$(CONFIG_NVRAMMANAGER) += nm_api.o nm_fwup.o sysProductInfo.o bigNumber.o shaAndSha512.o rsaVerify.o

