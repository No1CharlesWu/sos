# Programs, flags
ASM		= nasm
CC		= gcc
LD 		= ld

ASMKFLAGS	= -I kernel/include/ -f elf
CFLAGS		= -Wall -I kernel/include/ -fno-stack-protector -fno-builtin -m32 -c -nostdinc
LDFLAGS		= -m elf_i386 -T tools/kernel.ld -nostdlib

# This Program
IMG		= tools/os.img
KERNEL 		= tools/kernel.bin
C_SOURCES = $(shell find . -name "*.c")
C_OBJECTS = $(patsubst %.c, %.o, $(C_SOURCES))
S_SOURCES = $(shell find . -name "*.s")
S_OBJECTS = $(patsubst %.s, %.o, $(S_SOURCES))

run : everything
	make clean
	qemu-system-i386 -kernel $(KERNEL)
	make clean

debug : everything img
	make clean
	bochs -f tools/os.bxrc
	make clean

# All Phony Targets
.PHONY : everything all final clean realclean image buildimg

everything : $(KERNEL) $(IMG)

all : realclean everything

clean : 
	rm -f $(C_OBJECTS) $(S_OBJECTS)

realclean : 
	rm -f $(C_OBJECTS) $(S_OBJECTS) $(KERNEL)

img:
	sudo kpartx -av ./tools/os.img
	sudo mount -text2 /dev/mapper/loop0p1 /mnt
	sudo cp ./tools/kernel.bin /mnt/
	sudo umount /mnt
	sudo kpartx -dv ./tools/os.img

.s.o:
	@echo 编译汇编文件 $< ...
	$(ASM) $(ASMKFLAGS) $< -o $@ 
.c.o:
	@echo 编译代码文件 $< ...
	$(CC) $(CFLAGS)  $< -o $@


$(KERNEL) : $(C_OBJECTS) $(S_OBJECTS)
	@echo 链接内核文件...
	$(LD) $(LDFLAGS) $(C_OBJECTS) $(S_OBJECTS) -o $(KERNEL)


