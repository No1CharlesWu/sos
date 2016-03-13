# Programs, flags
ASM		= nasm
DASM 		= ndisasm
CC		= gcc
LD 		= ld

ASMBFLAGS 	= -I boot/include/
ASMKFLAGS	= -I include/ -f elf
CFLAGS		= -I include -fno-stack-protector -m32 -c 
LDFLAGS		= -m elf_i386 -T link.ld

# This Program
#BOOT		= boot/boot.bin boot/loader.bin
IMG		= os.img
KERNEL 		= kernel.bin
OBJS		= kernel/kc.o kernel/kasm.o lib/klib.o lib/string.o include/func.o

run : everything
	make clean
	qemu-system-i386 -kernel $(KERNEL)

debug : everything img
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

kernel/kasm.o : kernel/kernel.asm include/pm.inc
	$(ASM) $(ASMKFLAGS) $< -o $@ 

kernel/kc.o : kernel/kernel.c include/const.h include/protect.h include/type.h  include/print.h include/multiboot.h
	$(CC) $(CFLAGS)  $< -o $@

lib/klib.o : lib/klib.asm
	$(ASM) $(ASMKFLAGS) $< -o $@

lib/string.o : lib/string.asm
	$(ASM) $(ASMKFLAGS) $< -o $@

include/func.o : include/func.inc
	$(ASM) $(ASMKFLAGS) $< -o $@
	

#final : all clean
#image : final buildimg
#buildimg :
#	dd if=boot/boot.bin of=a.img bs=512 count=1 conv=notrunc
#	sudo mount -o loop a.img /mnt/floppy/
#	sudo cp -fv boot/loader.bin /mnt/floppy/
#	sudo cp -fv kernel.bin /mnt/floppy
#	sudo umount /mnt/floppy
#boot/boot.bin : boot/boot.asm boot/include/load.inc boot/include/fat12hdr.inc
#	$(ASM) $(ASMBFLAGS) -o $@ $<
#boot/loader.bin : boot/loader.asm boot/include/load.inc \
#			boot/include/fat12hdr.inc boot/include/pm.inc
#	$(ASM) $(ASMBFLAGS) -o $@ $<
#
