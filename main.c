#include "system.h"
#include "type.h"
#include "scrn.h"
#include "gdt.h"
#include "idt.h"
#include "isrs.h"
#include "irq.h"
#include "timer.h"
#include "kb.h"
#include "common.h"
//#include "ordered_array.h"
//#include "kheap.h"
//#include "paging.h"

extern unsigned int code;
extern unsigned int bss;
extern unsigned int end;
void main()
{
    int i;

    cls();
    Printf("code: 0x%x\n",&code);
    Printf("bss: 0x%x\n",&bss);
    Printf("end: 0x%x\n",&end);
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
    switch_install();
    Printf("simple switch test install ready.\n");
    __asm__ __volatile__ ("sti");	
    switch_test();
}
