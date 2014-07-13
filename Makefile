TARGET      := tempgba_libretro_psp1.a
CC  = psp-gcc
AR  = psp-ar


ifeq ($(DEBUG), 1)
CFLAGS += -O0 -g
else
CFLAGS += -O2
endif

CFLAGS   += -G0

CFLAGS   += -march=allegrex -mfp32 -mgp32 -mlong32 -mabi=eabi
CFLAGS   += -fomit-frame-pointer -fstrict-aliasing
CFLAGS   += -falign-functions=32 -falign-loops -falign-labels -falign-jumps
CFLAGS   += -Wall -Wundef -Wpointer-arith -Wbad-function-cast -Wwrite-strings -Wmissing-prototypes -Wsign-compare
#CFLAGS   += -Werror

ASFLAGS = $(CFLAGS)

CFLAGS  += -D__LIBRETRO__ -DPSP
#CFLAGS  += -DSINGLE_THREAD

CFLAGS  += -D_PSP_FW_VERSION=371

OBJS := cpu.o mips_stub.o message.o zip.o libretro.o input.o
OBJS += main.o memory.o video.o sound.o

INCDIRS := -I.
INCDIRS += -I$(shell psp-config --pspsdk-path)/include
#INCDIRS += -I$(shell psp-config --psp-prefix)/include

all: $(TARGET)

$(TARGET): $(OBJS)
	$(AR) rcs $@ $(OBJS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS) $(INCDIRS)

%.o: %.S
	$(CC) -c -o $@ $< $(ASFLAGS)

clean:
#	rm -f libretro.o input.o main.o memory.o video.o sound.o
	rm -f $(OBJS)
	rm -f $(TARGET)

.PHONY: $(TARGET) clean
