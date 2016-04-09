#ifndef _COMMON_H_
#define _COMMON_H_

unsigned char inportb(unsigned short _port);

unsigned short inportw(unsigned short port);

void outportb (unsigned short _port, unsigned char _data);

void io_xchg(void);

void io_hlt(void);

void io_cli(void);

void io_sti(void);

void io_stihlt(void);

int io_in8(int port);

int io_in16(int port);

int io_in32(int port);

void io_out8(int port,int data);

void io_out16(int port,int data);

void io_out32(int port,int data);

int io_load_eflags(void);

void io_store_eflags(int eflags);

#endif 
