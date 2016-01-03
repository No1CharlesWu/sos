debug: a.img bochsrc
	bochs -f bochsrc
	
a_boot.bin: a_boot.asm Makefile
	nasm a_boot.asm -o a_boot.bin

a.img: a_boot.bin a.img Makefile
	dd if=a_boot.bin of=a.img bs=512 count=1 conv=notrunc
	
run: a.img
	qemu-system-i386 a.img
