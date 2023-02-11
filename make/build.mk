include $(TOPLVL)/make/commands.mk


app-img				:= $(TOPLVL)/build/$(app-name).elf
objs					:= 

print_img_msg:
	$(PRINT) "\nBuilding application '" $(app-name) "'\n"

build_elf: print_elf_msg $(objs)

build_img: print_img_msg build_elf

all: build_img


clean:
	$(RM) $(objs)
	$(RM) $(app-img).elf