#ifndef _COMMON_H_
#define _COMMON_H_

unsigned char inportb(unsigned short _port);

unsigned short inportw(unsigned short port);

void outportb (unsigned short _port, unsigned char _data);

#endif 
