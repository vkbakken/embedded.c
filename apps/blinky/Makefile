TOP				:= ../..
TOOLCHAIN_LOC	:= /opt/gcc-arm-none-eabi/10.3-2021.10/bin
#TOOLCHAIN_LOC	:= 
CC				:= $(TOOLCHAIN_LOC)/arm-none-eabi-gcc
OBJCOPY         := $(TOOLCHAIN_LOC)/arm-none-eabi-objcopy
OBJDUMP         := $(TOOLCHAIN_LOC)/arm-none-eabi-objdump


PRJ				:= blinky


CFLAGS			:= -Wall -Os -mcpu=cortex-m4 -mlittle-endian -mfloat-abi=soft -mthumb -mtp=soft -munaligned-access
CFLAGS			+= -g3 -fshort-enums -fno-builtin-printf -ffreestanding -flto -fomit-frame-pointer -fno-dwarf2-cfi-asm -fno-builtin -ffunction-sections -fdata-sections -fshort-enums -fno-common
CFLAGS			+= -std=gnu99 -nostdlib

CFILES			:= $(TOP)/arch/cortexm/boot.c
CFILES			+= $(TOP)/arch/cortexm/delay.c
CFILES			+= $(TOP)/board/nrf52840_dk/init.c
CFILES			+= $(TOP)/board/nrf52840_dk/led.c
CFILES			+= blinky.c
CINC			:= -I /opt/gcc-arm-none-eabi/10.3-2021.10/include
CINC			+= -I $(TOP)/include
CINC			+= -I $(TOP)/board/nrf52840_dk/include
CINC			+= -I $(TOP)/chip/nrf52840/include


CFLAGS			+= $(CINC)
CFLAGS			+=

ASMFILES		:=
ASMFILES		+= 

LDFLAGS			:= -T $(TOP)/arch/cortexm/linker.ld -flto -ffreestanding -nostdlib -fstack-usage
#LDFLAGS			+= -L ./nrfxlib/bsdlib/lib/cortex-m33/soft-float/ -lbsd_nrf9160_xxaa
#LDFLAGS			+= -L ./nrfxlib/crypto/nrf_oberon/lib/cortex-m33/soft-float/ -loberon_3.0.2

OBJ       		= $(ASMFILES:.S=.o) $(CFILES:.c=.o) $(EXTC:.c=.o) $(CPPFILES:.cpp=.o) $(EXTCPP:.cpp=.o)


all: ver $(PRJ).elf hex


clean:
	rm -f $(OBJ)
	rm -f *.hex *.elf *.o *.lst *.map

ver:
	$(CC) --version

hex:
	$(OBJCOPY) -O ihex $(PRJ).elf $(PRJ).hex

# objects from asm files
.s.o:
	$(CC) -c $(CFLAGS) $< -o $@

# objects from c files
.c.o:
	$(CC) -c $(CFLAGS) $< -o $@


# elf file
$(PRJ).elf: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) --output $@ $(LDFLAGS) -Xlinker -Map=output.map
	$(OBJDUMP) -h -S $(PRJ).elf > $(PRJ).lst