# Programs, flags
ASM		= nasm
DASM 		= ndisasm
CC		= gcc
LD 		= ld

ASMKFLAGS	= -I include/ -f elf
CFLAGS		= -I include/ -fno-stack-protector -fno-builtin -m32 -c 
LDFLAGS		= -m elf_i386 -T link.ld

# This Program
IMG		= os.img
KERNEL 		= kernel.bin
OBJS		= main.o start.o func.o

run : everything
	make clean
	qemu-system-i386 -kernel $(KERNEL)

debug : everything img
	make clean
	bochs -f os.bxrc

# All Phony Targets
.PHONY : everything all final clean realclean image buildimg

everything : $(KERNEL) $(IMG)

all : realclean everything

clean : 
	rm -f $(OBJS)

realclean : 
	rm -f $(OBJS) $(KERNEL)

img:
	sudo kpartx -av ./os.img
	sudo mount -text2 /dev/mapper/loop0p1 /mnt
	sudo cp ./kernel.bin /mnt/
	sudo umount /mnt
	sudo kpartx -dv ./os.img

$(KERNEL) : $(OBJS)
	$(LD) $(LDFLAGS) -o $(KERNEL) $(OBJS)

start.o : start.asm
	$(ASM) $(ASMKFLAGS) $< -o $@ 

main.o : main.c include/type.h include/multiboot.h include/gdt.h include/idt.h include/scrn.h include/isrs.h include/irq.h include/timer.h include/kb.h include/common.h include/ordered_array.h
	$(CC) $(CFLAGS)  $< -o $@

func.o : include/func.inc
	$(ASM) $(ASMKFLAGS) $< -o $@

