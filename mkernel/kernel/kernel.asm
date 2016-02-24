bits 32
section .text
        ;multiboot spec
        align 4
        dd 0x1BADB002              	;magic
        dd 0x00                    	;flags
        dd - (0x1BADB002 + 0x00)   	;checksum. m+f+c should be zero

global start
extern cstart 				;this is defined in the c file

start:
	cli 				;block interrupts
	mov esp, stack_space		;set stack pointer
	call cstart
	hlt 				;halt the CPU

global set_cursor
set_cursor:
	push ax
	push bx
	push cx
	push dx
	push ds
	push es

	mov dx,0x3d4
	mov al,0x0e
	out dx,al
	mov dx,0x3d5
	in al,dx
	mov ah,al

	mov dx,0x3d4
	mov al,0x0f
	out dx,al
	mov dx,0x3d5
	in al,dx
	mov bx,ax
	
	mov bx,[esp+20]

	mov dx,0x3d4
	mov al,0x0e
	out dx,al
	mov dx,0x3d5
	mov al,bh
	out dx,al
	
	mov dx,0x3d4
	mov al,0x0f
	out dx,al
	mov dx,0x3d5
	mov al,bl
	out dx,al
	
	pop es
	pop ds
	pop dx
	pop cx
	pop bx
	pop ax

	ret

section .bss
resb 8192				;8KB for stack
stack_space:
