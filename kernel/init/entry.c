#include "multiboot.h"
#include "type.h"
#include "common.h"
typedef uint32_t pgd_t;

#define PAGE_OFFSET 	0xC0000000
#define PAGE_PRESENT 	0x1
#define PAGE_WRITE 	0x2
#define PAGE_USER 	0x4
#define PAGE_SIZE 	4096
#define PAGE_MASK      0xFFFFF000
#define PGD_INDEX(x) (((x) >> 22) & 0x3FF)
#define PTE_INDEX(x) (((x) >> 12) & 0x3FF)
#define OFFSET_INDEX(x) ((x) & 0xFFF)
#define STACK_SIZE 8192

// 内核初始化函数
void kern_init();

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


	// 调用内核初始化函数
	kern_init();
}

void kern_init()
{
    asm volatile ("hlt");
}

