TOOLCHAIN_LOC	:= /opt/gcc-arm-none-eabi/8-2018-q4-major/bin
#TOOLCHAIN_LOC	:= 
CC				:= riscv32-unknown-elf-gcc
OBJCOPY         := riscv32-unknown-elf-objcopy

PRJ				:= tinzy_riscv

CFLAGS			:= -march=rv32im -mabi=ilp32  -Wl,--no-relax -fstack-usage
CFLAGS			+= -g -nostdlib -fshort-enums -fno-builtin-printf -ffreestanding -flto
CFLAGS			+= 

CFILES			:= boot.c
CFILES			+= main.c
CFILES			+= dhrystone.c
CINC			:= -I /opt/riscv32im/2020-04-14-d8243f7f/riscv32-unknown-elf/include
CINC			+= -I ./include
CINC			+= -I ./

CFLAGS			+= $(CINC)
CFLAGS			+= -DDEVICE_ASIC

ASMFILES		:=
ASMFILES		+= 

LDFLAGS			:= -T onio.zero_ram.ld -flto -ffreestanding -nostdlib -fstack-usage
#LDFLAGS			+= -L ./nrfxlib/bsdlib/lib/cortex-m33/soft-float/ -lbsd_nrf9160_xxaa
#LDFLAGS			+= -L ./nrfxlib/crypto/nrf_oberon/lib/cortex-m33/soft-float/ -loberon_3.0.2

OBJ       		= $(ASMFILES:.S=.o) $(CFILES:.c=.o) $(EXTC:.c=.o) $(CPPFILES:.cpp=.o) $(EXTCPP:.cpp=.o)


all: ver $(PRJ).elf hex


clean:
	rm -f *.hex *.elf *.o *.lst

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
	riscv32-unknown-elf-objdump -h -S $(PRJ).elf > $(PRJ).lst