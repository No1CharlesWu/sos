bits 32
global set_cursor 

set_cursor:
	push ax
	push bx
	push cx
	push dx

	mov bx,[esp+12]

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
	
	pop dx
	pop cx
	pop bx
	pop ax

	ret
