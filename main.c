#include <system.h>
#include "type.h"
#include "scrn.h"
#include "gdt.h"
#include "idt.h"
#include "isrs.h"
#include "irq.h"
#include "timer.h"
#include "kb.h"

void *memcpy(void *dest, const void *src, size_t count)
{
    const char *sp = (const char *)src;
    char *dp = (char *)dest;
    for(; count != 0; count--) *dp++ = *sp++;
    return dest;
}

void *memset(void *dest, char val, size_t count)
{
    char *temp = (char *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count)
{
    unsigned short *temp = (unsigned short *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

size_t strlen(const char *str)
{
    size_t retval;
    for(retval = 0; *str != '\0'; str++) retval++;
    return retval;
}

unsigned char inportb (unsigned short _port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void outportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

void main()
{
    int i;

    cls();
    Printf("main start.\n");
    init_video();
    Printf("init video ready.\n");
    gdt_install();
    Printf("gdt install ready.\n");
    idt_install();
    Printf("idt install ready.\n");
    isrs_install();
    Printf("isr install ready.\n");
    irq_install();
    Printf("irq install ready.\n");
    timer_install();
    Printf("timer install ready.\n");
    keyboard_install();
    Printf("keyboard install ready.\n");
    __asm__ __volatile__ ("sti");	

}
