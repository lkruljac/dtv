CROSS_COMPILE=$(TOOLCHAIN_CROSS_COMPILE)

CC_PREFIX=$(CROSS_COMPILE)-
CC=$(CC_PREFIX)gcc
CXX=$(CC_PREFIX)g++
LD=$(CC_PREFIX)ld

SYSROOT=$(SDK_ROOTFS)
GALOIS_INCLUDE=$(SDK_GALOIS)

INCS =	-I./../tdp_api							
INCS += -I./include/							\
		-I$(SYSROOT)/usr/include/         		\
		-I$(GALOIS_INCLUDE)/Common/include/     \
		-I$(GALOIS_INCLUDE)/OSAL/include/		\
		-I$(GALOIS_INCLUDE)/OSAL/include/CPU1/	\
		-I$(GALOIS_INCLUDE)/PE/Common/include/  \
        -I$(SYSROOT)/usr/include/directfb/		\
		-I/home/student/pputvios1/toolchain/marvell/marvell-sdk-1046/rootfs/usr/include/directfb/directfb.h \
		-I/include/ \
		-I/$(PWD)/tdp_api/

LIBS_PATH = -Ltdp_api
LIBS_PATH += -L$(SYSROOT)/home/galois/lib/
LIBS_PATH += -L$(SYSROOT)/home/galois/lib/directfb-1.4-6-libs


LIBS := $(LIBS_PATH) -ltdp
LIBS += $(LIBS_PATH) -lOSAL	-lshm -lPEAgent
LIBS += $(LIBS_PATH) -ldirectfb -ldirect -lfusion -lrt

CFLAGS += -D__LINUX__ -O0 -Wno-psabi --sysroot=$(SYSROOT) -Iinclude -Itdp_api/
#CFLAGS += -Iinclude
CXXFLAGS = $(CFLAGS)

SRCFOLDER = $(PWD)/src/
SRC = $(SRCFOLDER)main.c 
SRC+= $(SRCFOLDER)remote.c
SRC+= $(SRCFOLDER)globals.c 
SRC+= $(SRCFOLDER)configTool.c 
SRC+= $(SRCFOLDER)streamplayer.c

all: clean kruljac copy

kruljac:
	$(CC) -o kruljac $(SRC) $(CFLAGS) $(LIBS)

copy:
	cp kruljac /home/student/pputvios1/ploca

clean:
	rm -f kruljac
