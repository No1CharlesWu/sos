# Programs, flags
ASM		= nasm
DASM 		= ndisasm
CC		= gcc
LD 		= ld

ASMKFLAGS	= -f elf
CFLAGS		= -fno-stack-protector -m32 -c 
LDFLAGS		= -m elf_i386 -T link.ld

# This Program
KERNEL 		= kernel
OBJS		= kc.o kasm.o lib/kliba.o lib/string.o

run : everything
	qemu-system-i386 -kernel $(KERNEL)

# All Phony Targets
.PHONY : everything all final clean realclean

everything : $(KERNEL)

all : realclean everything

final : all clean

clean : 
	rm -f $(OBJS)

realclean : 
	rm -f $(OBJS) $(KERNEL)

$(KERNEL) : $(OBJS)
	$(LD) $(LDFLAGS) -o $(KERNEL) $(OBJS)

kasm.o : kernel.asm
	$(ASM) $(ASMKFLAGS) $< -o $@ 

kc.o : kernel.c
	$(CC) $(CFLAGS)  $< -o $@

lib/klib.o : lib/kliba.asm
	$(ASM) $(ASMKFLAGS) $< -o $@

lib/string.o : lib/string.asm
	$(ASM) $(ASMKFLAGS) $< -o $@

#nasm -f elf kernel.asm -o kasm.o
#gcc -fno-stack-protector -m32 -c kernel.c -0 kc.o
#ld -m elf_i386 -T link.ld -o kernel kasm.o kc.o
