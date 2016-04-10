#ifndef _PMM_H_
#define _PMM_H_

#include "multiboot.h"
#include "type.h"
extern uint32_t kernel_start;
extern uint32_t kernel_end;

// 线程栈的大小
#define STACK_SIZE 8192

// 支持的最大物理内存(512MB)
#define PMM_MAX_SIZE 0x20000000

// 物理内存页框大小 
#define PMM_PAGE_SIZE 0x1000

// 最多支持的物理页面个数
#define PAGE_MAX_SIZE (PMM_MAX_SIZE/PMM_PAGE_SIZE)

// 页掩码 按照 4096 对齐地址
#define PHY_PAGE_MASK 0xFFFFF000

// 内核栈的栈顶
extern uint32_t kern_stack_top;

// 动态分配物理内存页的总数
extern uint32_t phy_page_count;

// 输出 BIOS 提供的物理内存布局
void show_memory_map(multiboot_t *glb_mboot_ptr);

// 初始化物理内存管理
void init_pmm();

// 返回一个内存页的物理地址
uint32_t pmm_alloc_page();

// 释放申请的内存
void pmm_free_page(uint32_t p);

void test_alloc_and_free_page();

#endif
