CFLAGS += -DCORE_M0PLUS
CXXFLAGS += -DCORE_M0PLUS -I. -I../../../lib/vendor/lpcopen/inc
ISPOPTS += -s -i 2
LINK = LPC810.ld
ARCH = lpc8xx

OBJS = main.o sys.o system_LPC8xx.o gcc_startup_lpc8xx.o \
		printf.o printf-retarget.o

default: isp

LIBDIR = ../../../lib
SHARED = $(LIBDIR)/sys-none
include $(SHARED)/rules.mk
