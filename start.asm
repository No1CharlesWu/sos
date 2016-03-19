bits 32
section .text
        ;multiboot spec
        align 4
        dd 0x1BADB002              	;magic
        dd 0x00000000              	;flags
        dd - (0x1BADB002 + 0x00000000)   	;checksum. m+f+c should be zero

global start
extern cstart 				;this is defined in the c file

start:
	mov esp, stack_space		;set stack pointer
	call cstart
	jmp $

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

global isr0
isr0:
	cli 
	push byte 0
	push byte 0
	jmp isr_common_stub

extern fault_handler
isr_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
    mov eax, fault_handler
    call eax
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret
	
section .bss
resb 8192				;8KB for stack
stack_space:
