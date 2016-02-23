
; License: GPL version 2 or higher http://www.gnu.org/licenses/gpl.html

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
	call set_cursor	
	call cstart
	hlt 				;halt the CPU

global set_cursor
global get_cursor
get_cursor:
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

	add bx,10

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
set_cursor:
	push ax
	push bx
	push cx
	push dx
	push ds
	push es
	push ecx

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
	
	xor bx,bx
	mov ecx,[esp+4]

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
	
	pop ecx
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
