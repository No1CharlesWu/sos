bits 32

global io_xchg      ;void io_xchg(void);
global io_hlt		;void io_hlt(void);
global io_cli		;void io_cli(void);
global io_sti		;void io_sti(void);
global io_stihlt	;void io_stihlt(void);
global io_in8		;int io_in8(int port)
global io_in16		;int io_in16(int port)
global io_in32		;int io_in32(int port)
global io_out8		;void io_out8(int port,int data)
global io_out16		;void io_out16(int port,int data)
global io_out32		;void io_out32(int port,int data)
global io_load_eflags	;int io_load_eflags(void)
global io_store_eflags	;void io_store_eflags(int eflags)

section .text
io_xchg:    ;void io_xchg(void);
	xchg bx,bx
	ret

io_hlt:		;void io_hlt(void);
	HLT
	RET

io_cli:		;void io_cli(void);
	CLI
	RET
	
io_sti:		;void io_sti(void);
	STI
	RET

io_stihlt:	;void io_stihlt(void);
	STI
	HLT
	RET

io_in8:		;int io_in8(int port)
	mov edx,[esp+4]
	mov eax,0
	in  al,dx
	ret

io_in16:	;int io_in16(int port)
	mov edx,[esp+4]
	mov eax,0
	in  ax,dx
	ret
io_in32:	;int io_in32(int port)
	mov edx,[esp+4]
	mov eax,0
	in  eax,dx
	ret

io_out8:	;void io_out8(int port,int data)
	mov edx,[esp+4]
	mov al,[esp+8]
	out dx,al
	ret

io_out16:	;void io_out16(int port,int data)
	mov edx,[esp+4]
	mov eax,[esp+8]
	out dx,ax
	ret
io_out32:	;void io_out32(int port,int data)
	mov edx,[esp+4]
	mov eax,[esp+8]
	out dx,eax
	ret

io_load_eflags:	;int io_load_eflags(void)
	pushfd
	pop eax
	ret

io_store_eflags:	;void io_store_eflags(int eflags)
	mov eax,[esp+4]
	push eax
	popfd
	ret
