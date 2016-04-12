#include "multiboot.h"
#include "type.h"
#include "common.h"
#include "scrn.h"
#include "gdt.h"
#include "mmu.h"
#include "pmm.h"
#include "idt.h"
#include "isrs.h"
#include "irq.h"
#include "vmm.h"
#include "kb.h"
#include "timer.h"
#include "heap.h"

// 内核初始化函数
void kern_init();

// 开启分页机制之后的 Multiboot 数据指针
multiboot_t *glb_mboot_ptr;

// 开启分页机制之后的内核栈
char kern_stack[STACK_SIZE];

// 内核使用的临时页表和页目录
// 该地址必须是页对齐的地址，内存 0-640KB 肯定是空闲的
__attribute__((section(".init.data"))) pgd_t *pgd_tmp  = (pgd_t *)0x1000;
__attribute__((section(".init.data"))) pgd_t *pte_low  = (pgd_t *)0x2000;
__attribute__((section(".init.data"))) pgd_t *pte_hign = (pgd_t *)0x3000;

// 内核入口函数
__attribute__((section(".init.text"))) void kern_entry()
{
	pgd_tmp[0] = (uint32_t)pte_low | PAGE_PRESENT | PAGE_WRITE;
	pgd_tmp[PGD_INDEX(PAGE_OFFSET)] = (uint32_t)pte_hign | PAGE_PRESENT | PAGE_WRITE;

	// 映射内核虚拟地址 4MB 到物理地址的前 4MB
	int i;
	for (i = 0; i < 1024; i++) {
		pte_low[i] = (i << 12) | PAGE_PRESENT | PAGE_WRITE;
	}

	// 映射 0x00000000-0x00400000 的物理地址到虚拟地址 0xC0000000-0xC0400000
	for (i = 0; i < 1024; i++) {
		pte_hign[i] = (i << 12) | PAGE_PRESENT | PAGE_WRITE;
	}
	
	// 设置临时页表
	asm volatile ("mov %0, %%cr3" : : "r" (pgd_tmp));

	uint32_t cr0;

	// 启用分页，将 cr0 寄存器的分页位置为 1 就好
	asm volatile ("mov %%cr0, %0" : "=r" (cr0));
	cr0 |= 0x80000000;
	asm volatile ("mov %0, %%cr0" : : "r" (cr0));
	
	// 切换内核栈
	uint32_t kern_stack_top = ((uint32_t)kern_stack + STACK_SIZE) & 0xFFFFFFF0;
	asm volatile ("mov %0, %%esp\n\t"
			"xor %%ebp, %%ebp" : : "r" (kern_stack_top));

	// 更新全局 multiboot_t 指针
	glb_mboot_ptr = mboot_ptr_tmp+ PAGE_OFFSET;
	// 调用内核初始化函数
    kern_init();
}

extern uint32_t kernel_start;
extern uint32_t kernel_end;

#define int_number  32
void test_int(void) {
	asm volatile (
	    "int %0 \n"
	    "movl %%ebp, %%esp \n"
	    :
	    : "i"(int_number)
	);
}

void kern_init()
{
    cls();
    init_video();
    printf("kernel start at : 0x%x\n",&kernel_start);
    printf("kernel   end at : 0x%x\n",&kernel_end);
    printf("kernel in memory used:   %d KB\n", (&kernel_end - &kernel_start+ 1023) / 1024);

    gdt_install();
    printf("gdt install ready.\n");
    idt_install();
    printf("idt install ready.\n");
    isrs_install();
    printf("isr install ready.\n");
    irq_install();
    printf("irq install ready.\n");
    keyboard_install();
    printf("keyboard install ready.\n");
    timer_install();
    printf("timer install ready.\n");
    io_sti();
    printf("open the interrupt.\n");

    //show_memory_map(glb_mboot_ptr);
    init_pmm();
    printf("init pmm ready.\n");
    init_vmm();
    printf("init vmm ready.\n");
    //test_alloc_and_free_page();

    init_heap();
    test_heap();
    //test_int();

    io_xchg();
    printf("\nWrite any things to test keyboard.\n");
    while(1);
}

