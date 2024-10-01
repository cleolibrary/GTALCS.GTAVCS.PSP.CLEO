TARGET = opcodes
OBJS = main.o
LIBS = -lstdc++

BUILD_PRX = 1

PRX_EXPORTS = exports.exp

#USE_PSPSDK_LIBC = 1

INCDIR = 
CFLAGS = -Os -G0 -Wall -D PSP -mpreferred-stack-boundary=4
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)
LIBDIR =

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
