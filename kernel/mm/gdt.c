#include "gdt.h"
#include "mmu.h"

uint8_t stack0[1024];
struct taskstate ts = {0};

inline void ltr(uint16_t sel) 
{
    asm volatile ("ltr %0" :: "r" (sel));
}

void set_ts(struct taskstate ts)
{
   ts.ts_esp0 = (uint32_t)&stack0 + sizeof(stack0);
   ts.ts_ss0 = (KERNEL_DS);  
}
/* Setup a descriptor in the Global Descriptor Table */
void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran)
{
    /* Setup the descriptor base address */
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    /* Setup the descriptor limits */
    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);

    /* Finally, set up the granularity and access flags */
    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;
}

void gdt_install()
{
    /* Setup the GDT pointer and limit */
    gp.limit = (sizeof(struct gdt_entry) * gdt_size) - 1;
    gp.base = (int)&gdt;
    /* Our NULL descriptor */
    gdt_set_gate(0, 0, 0, 0, 0);
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

   //// gdt_set_gate(5, base, limit,0xE9,0x00);
    set_ts(ts);
    gdt_set_gate(5,(unsigned int)&ts, ((unsigned int)&ts + sizeof(ts)),0x89,0x40);

    /* Flush out the old GDT and install the new changes! */
    gdt_flush();

    ltr(GD_TSS);
}

