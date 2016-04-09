#ifndef _ISRS_H_
#define _ISRS_H_

#include "idt.h"

/* These are function prototypes for all of the exception
*  handler: The first 32 entries in the IDT are reserved
*  by Intel, and are designed to service exceptions! */
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29(); //system call
extern void isr30(); //tou
extern void isr31(); //tok

#define T_SWITCH_TOU 30
#define T_SWITCH_TOK 31

/* This is a very repetitive function... it's not hard, it's
*  just annoying. As you can see, we set the first 32 entries
*  in the IDT to the first 32 ISRs. We can't use a for loop
*  for this, because there is no way to get the function names
*  that correspond to that given entry. We set the access
*  flags to 0x8E. This means that the entry is present, is
*  running in ring 0 (kernel level), and has the lower 5 bits
*  set to the required '14', which is represented by 'E' in
*  hex. */
void isrs_install();

void isr_install_handler(int isr,void (*handler)(struct regs * r));

void isr_uninstall_handler(int isr);
/* All of our Exception handling Interrupt Service Routines will
*  point to this function. This will tell us what exception has
*  happened! Right now, we simply halt the system by hitting an
*  endless loop. All ISRs disable interrupts while they are being
*  serviced as a 'locking' mechanism to prevent an IRQ from
*  happening and messing up kernel data structures */
void isr_handler(struct regs *r);

//void print_cur_status(void) {
//    static int round = 0;
//    uint16_t reg1, reg2, reg3, reg4;
//    asm volatile (
//            "mov %%cs, %0;"
//            "mov %%ds, %1;"
//            "mov %%es, %2;"
//            "mov %%ss, %3;"
//            : "=m"(reg1), "=m"(reg2), "=m"(reg3), "=m"(reg4));
//    Printf("%d:  @ring %d\n", round, reg1 & 3);
//    Printf("%d:  cs = %x\n", round, reg1);
//    Printf("%d:  ds = %x\n", round, reg2);
//    Printf("%d:  es = %x\n", round, reg3);
//    Printf("%d:  ss = %x\n", round, reg4);
//    round ++;
//}
//
//void switch_to_user(void) {
//	asm volatile (
//	    "sub $0x8, %%esp \n"
//	    "int %0 \n"
//	    "movl %%ebp, %%esp"
//	    : 
//	    : "i"(T_SWITCH_TOU)
//	);
//}
//
//void switch_to_kernel(void) {
//	asm volatile (
//	    "int %0 \n"
//	    "movl %%ebp, %%esp \n"
//	    : 
//	    : "i"(T_SWITCH_TOK)
//	);
//}
//void print_regs(struct regs *r)
//{
//	Printf("r at %x\n",&r);
//	Printf("cs : %x\n",r->cs);
//	Printf("ds : %x\n",r->ds);
//	Printf("es : %x\n",r->es);
//	Printf("ss : %x\n",r->ss);
//	Printf("int_no: %d\n",r->int_no);
//	Printf("esp : %x\n\n",r->useresp);
//}
//void switch_test()
//{
//	print_cur_status();
//	puts("switch to user mode.\n");
//	switch_to_user();
//	print_cur_status();
//	puts("switch to kernel mode.\n");
//	switch_to_kernel();
//	print_cur_status();
//}
//struct regs switchk2u,*switchu2k;
//void switch_tou_handler(struct regs *r)
//{
//	//puts("\nswitch_tou_handler install ready\n");
//	//print_regs(r);
//	if(r->cs != 0x1B)
//	{
//		switchk2u = *r;
//		switchk2u.cs = 0x1B;
//		switchk2u.ds = switchk2u.es = switchk2u.ss = 0x23;
//		switchk2u.useresp = (uint32_t)r + sizeof(struct regs) - 8;
//            switchk2u.eflags |= 0x00003000;
//            *((uint32_t *)r- 1) = (uint32_t)&switchk2u;
//	 //   print_regs(&switchk2u);
//	}
//	//print_regs(r);
//}
//void switch_tok_handler(struct regs *r)
//{
//	//puts("switch_tok_handler install ready\n");
//	if(r->cs != 0x08)
//	{
//		r->cs = 0x08;
//		r->ds = r->es = 0x10;
//		r->eflags &= ~(0x00003000);
//		switchu2k = (struct regs *)(r->useresp - (sizeof(struct regs) - 8));
//		memcpy(switchu2k, r, sizeof(struct regs) - 8);
//		*((uint32_t *)r - 1) = (uint32_t)switchu2k;
//	}
//}
//void switch_install()
//{
//	isr_install_handler(30,switch_tou_handler);
//	isr_install_handler(31,switch_tok_handler);
//}
#endif

