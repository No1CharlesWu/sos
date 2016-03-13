%include "pm.inc"
[SECTION .gdt]
LABEL_GDT:		Descriptor	0,		0,			0
LABEL_DESC_CODE32:	Descriptor	0,		SegCode32Len- 1,	DA_C + DA_32
LABEL_DESC_VIDEO:	Descriptor	0B8000h,	0ffffh,			DA_DRW

GdtLen		equ 	$ - LABEL_GDT
GdtPtr 		dw 	GdtLen - 1
		dd	0

SelectorCode32 	equ 	LABEL_DESC_CODE32 - LABEL_GDT
SelectorVideo	equ 	LABEL_DESC_VIDEO  - LABEL_GDT	

bits 32
section .text
        ;multiboot spec
        align 4
        dd 0x1BADB002              	;magic
        dd 0x00000003              	;flags
        dd - (0x1BADB002 + 0x00000003)   	;checksum. m+f+c should be zero

global start
global Test
extern cstart 				;this is defined in the c file

Test:
	mov ax, SelectorVideo
	mov gs,ax
	mov edi,(80 * 19 + 79) * 2
	mov ah,0Ch
	mov al,'P'
	mov [gs:edi],ax
	jmp $

start:
	cli 				;block interrupts
	xchg bx,bx
	mov esp, stack_space		;set stack pointer
	push ebx
	push eax
	call cstart
	xchg bx,bx
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
SegCode32Len	equ 	$-start	
section .bss
resb 8192				;8KB for stack
stack_space:
