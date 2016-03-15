%include "pm.inc"
;[SECTION .gdt]
;LABEL_GDT:		Descriptor	0,		0,			0
;LABEL_DESC_CODE32:	Descriptor	0,		SegCode32Len- 1,	DA_C + DA_32
;LABEL_DESC_VIDEO:	Descriptor	0B8000h,	0ffffh,			DA_DRW
;
;GdtLen		equ 	$ - LABEL_GDT
;GdtPtr 		dw 	GdtLen - 1
;		dd	0
;
;SelectorCode32 	equ 	LABEL_DESC_CODE32 - LABEL_GDT
;SelectorVideo	equ 	LABEL_DESC_VIDEO  - LABEL_GDT	

bits 32
section .text
        ;multiboot spec
        align 4
        dd 0x1BADB002              	;magic
        dd 0x00000003              	;flags
        dd - (0x1BADB002 + 0x00000003)   	;checksum. m+f+c should be zero

global start
extern cstart 				;this is defined in the c file

start:
	xchg bx,bx
	cli 				;block interrupts
	mov esp, stack_space		;set stack pointer
	push ebx
	push eax
	call cstart
	xchg bx,bx
	;jmp Test
	hlt 				;halt the CPU

global gdt_flush
extern gp
gdt_flush:
	lgdt [gp]
	mov ax,0x10
	mov ds,ax
	mov es,ax
	mov fs,ax
	mov gs,ax
	mov ss,ax
	jmp 0x08:flush2
flush2:
	ret

global idt_load
extern idtp
idt_load:
    lidt [idtp]
    ret

;global Test
;Test:
;	mov ax,cs
;	mov ds,ax
;	mov es,ax
;	mov ss,ax
;	mov sp, 0100h

	;xor eax,eax
	;mov ax,cs
	;shl eax,4
	;add eax,Test
	;mov word [LABEL_DESC_CODE32 + 2],ax
	;shr eax,16
	;mov byte [LABEL_DESC_CODE32 + 4],al
	;mov byte [LABEL_DESC_CODE32 + 7],ah

	;xor eax,eax
	;mov ax,ds
	;shr eax,4
	;add eax,LABEL_GDT
	;mov dword [GdtPtr + 2],eax

	;lgdt [GdtPtr]
	;
	;mov ax, SelectorVideo
	;mov gs,ax
	;mov edi,(80 * 19 + 79) * 2
	;mov ah,0Ch
	;mov al,'P'
	;mov [gs:edi],ax
	;hlt
;SegCode32Len	equ 	$-start	

section .bss
resb 8192				;8KB for stack
stack_space:
