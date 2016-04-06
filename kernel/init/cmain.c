#include "type.h"
#include "scrn.h"
#include "gdt.h"
#include "idt.h"
#include "isrs.h"
#include "irq.h"
#include "timer.h"
#include "kb.h"
#include "common.h"
#include "string.h"
#include "debug.h"
#include "multiboot.h"
#include "elf.h"
#include "mmu.h"
#include "pmm.h"

extern unsigned int code;
extern unsigned int end;
void cmain()
{
    cls();
    printf("kernel in memory start: 0x%x\n", &code);
    printf("kernel in memory end:   0x%x\n", &end);
    printf("kernel in memory used:   %d KB\n\n", (&end - &code + 1023) / 1024);

    printf("main start.\n");
    init_video();
    printf("init video ready.\n");
    gdt_install();
    printf("gdt install ready.\n");
    idt_install();
    printf("idt install ready.\n");
    isrs_install();
    printf("isr install ready.\n");
    irq_install();
    printf("irq install ready.\n");
    timer_install();
    printf("timer install ready.\n");
    keyboard_install();
    printf("keyboard install ready.\n");
    init_pmm();
    printf("init pmm ready.\n");

    __asm__ __volatile__ ("sti");	

    show_memory_map();
    test_alloc_and_free_page();

}
