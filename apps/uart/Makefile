TOP				:= ../..
#TOOLCHAIN_LOC	:= /opt/gcc-arm-none-eabi/10.3-2021.10/bin/
TOOLCHAIN_LOC	:= 
CC				:= $(TOOLCHAIN_LOC)arm-none-eabi-gcc
OBJCOPY         := $(TOOLCHAIN_LOC)arm-none-eabi-objcopy
OBJDUMP         := $(TOOLCHAIN_LOC)arm-none-eabi-objdump


PRJ				:= uart


CFLAGS			:= -Wall -Os -mcpu=cortex-m4 -mlittle-endian -mfloat-abi=soft -mthumb -mtp=soft -munaligned-access
CFLAGS			+= -g3 -fshort-enums -fno-builtin-printf -ffreestanding -flto -fomit-frame-pointer -fno-dwarf2-cfi-asm -fno-builtin -ffunction-sections -fdata-sections -fshort-enums -fno-common
CFLAGS			+= -std=gnu99 -nostdlib

CFILES			:= $(TOP)/arch/cortexm/boot.c
CFILES			+= $(TOP)/arch/cortexm/delay.c
CFILES			+= $(TOP)/board/nrf52840_dk/init.c
CFILES			+= $(TOP)/board/nrf52840_dk/led.c
CFILES			+= $(TOP)/drivers/serial/uart/nrf52_ctrl.c
CFILES			+= uart.c
CINC			:= -I /opt/gcc-arm-none-eabi/10.3-2021.10/include
CINC			+= -I $(TOP)/include
CINC			+= -I $(TOP)/arch/cortexm/include
CINC			+= -I $(TOP)/board/nrf52840_dk/include
CINC			+= -I $(TOP)/chip/nrf52840/include


CFLAGS			+= $(CINC)
CFLAGS			+= -DCONFIG_DEBUG_UART=0

ASMFILES		:=
ASMFILES		+= 

LDFLAGS			:= -T $(TOP)/arch/cortexm/linker.ld -flto -ffreestanding -nostdlib -fstack-usage


OBJ       		= $(ASMFILES:.S=.o) $(CFILES:.c=.o) $(EXTC:.c=.o) $(CPPFILES:.cpp=.o) $(EXTCPP:.cpp=.o)


all: ver $(PRJ).elf hex bin


clean:
	rm -f $(OBJ)
	rm -f *.hex *.elf *.o *.lst *.map *.bin

ver:
	$(CC) --version


hex:
	$(OBJCOPY) -O ihex $(PRJ).elf $(PRJ).hex


bin:
	$(OBJCOPY) -O binary $(PRJ).elf $(PRJ).bin


program: $(PRJ).bin
	echo "r\nh\nloadbin $(PRJ).bin 0\nr\nexit\n" |\
	JLinkExe -device nrf52840 -autoconnect 1 -if SWD -speed 4000


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
