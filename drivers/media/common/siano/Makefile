#**********uniscope-driver-modify-file-on-qualcomm-platform*****************#
smsmdtv-objs := smscoreapi.o sms-cards.o smsendian.o
smsdvb-objs := smsdvb-main.o smssdio.o
obj-y +=smssdio.o  smscoreapi.o sms-cards.o smsendian.o smschar.o
obj-$(CONFIG_SMS_SIANO_MDTV) += smsmdtv.o smsdvb.o

ifeq ($(CONFIG_SMS_SIANO_RC),y)
  smsmdtv-objs += smsir.o
endif

ifeq ($(CONFIG_SMS_SIANO_DEBUGFS),y)
  smsdvb-objs += smsdvb-debugfs.o
endif

ccflags-y += -Idrivers/media/dvb-core
ccflags-y += $(extra-cflags-y) $(extra-cflags-m)

