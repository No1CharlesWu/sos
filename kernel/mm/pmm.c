#include "pmm.h"
#include "multiboot.h"
#include "debug.h"
#include "common.h"
#include "scrn.h"

// 物理内存页面管理的栈
static uint32_t pmm_stack[PAGE_MAX_SIZE+1];

// 物理内存管理的栈指针
static uint32_t pmm_stack_top;

// 物理内存页的数量
uint32_t phy_page_count;

void init_pmm()
{
	mmap_entry_t *mmap_start_addr = (mmap_entry_t *)glb_mboot_ptr->mmap_addr;
	mmap_entry_t *mmap_end_addr = (mmap_entry_t *)glb_mboot_ptr->mmap_addr + glb_mboot_ptr->mmap_length;

	mmap_entry_t *map_entry;

	for (map_entry = mmap_start_addr; map_entry < mmap_end_addr; map_entry++)
       	{
		if (map_entry->type == 1 && map_entry->base_addr_low == 0x100000) 
		{
			uint32_t page_addr = map_entry->base_addr_low + (uint32_t)&kernel_end-(uint32_t)&kernel_start;
			page_addr = ((uint32_t)(page_addr / PMM_PAGE_SIZE) + 1) * PMM_PAGE_SIZE;
			uint32_t length = map_entry->base_addr_low + map_entry->length_low;

//			printf("%x,%d,%d\n",page_addr,PMM_PAGE_SIZE,((uint32_t)(page_addr)/PMM_PAGE_SIZE));
//			printf("page_addr: 0x%x\n",page_addr);
//			printf("length:	0x%x\n",length);
//			printf("PMM_MAX_SIZE : 0x%x\n",PMM_MAX_SIZE);
//			printf("PAGE_MAX_SIZE: 0x%x\n",PAGE_MAX_SIZE);
//			printf("current page size : %d\n",(length - page_addr) / PMM_PAGE_SIZE);
//			printf("phy_page_count : %d \n",phy_page_count);

			while (page_addr < length && page_addr < PMM_MAX_SIZE)
		       	{
				pmm_free_page(page_addr);
				page_addr += PMM_PAGE_SIZE;
				phy_page_count++;
			}
		}
	}
}

uint32_t pmm_alloc_page()
{
	ASSERT(pmm_stack_top != 0);

	uint32_t page = pmm_stack[pmm_stack_top--];

	return page;
}

void pmm_free_page(uint32_t p)
{
	ASSERT(pmm_stack_top != PAGE_MAX_SIZE);

	pmm_stack[++pmm_stack_top] = p;
}

void show_memory_map(multiboot_t *glb_mboot_ptr)
{
	uint32_t mmap_addr = glb_mboot_ptr->mmap_addr;
	uint32_t mmap_length = glb_mboot_ptr->mmap_length;

	printf("\nShow Memory Map:\n");
	
	mmap_entry_t *mmap = (mmap_entry_t *)mmap_addr;
	for (mmap = (mmap_entry_t *)mmap_addr; (uint32_t)mmap < mmap_addr + mmap_length; mmap++) 
	{
		printf("base_addr = 0x%x%x, length = 0x%x%x, type = 0x%x\n",
			(uint32_t)mmap->base_addr_high, (uint32_t)mmap->base_addr_low,
			(uint32_t)mmap->length_high, (uint32_t)mmap->length_low,
			(uint32_t)mmap->type);
	}
	printf("\n");
}

void test_alloc_and_free_page()
{
    printf( "Test Physical Memory Alloc :\n");
    uint32_t allc_addr = pmm_alloc_page();
    printf("Alloc Physical Addr: 0x%x\n", allc_addr);
    allc_addr = pmm_alloc_page();
    printf("Alloc Physical Addr: 0x%x\n", allc_addr);
    allc_addr = pmm_alloc_page();
    printf("Alloc Physical Addr: 0x%x\n", allc_addr);
    allc_addr = pmm_alloc_page();
    printf("Alloc Physical Addr: 0x%x\n", allc_addr);
    pmm_free_page(allc_addr) ;
    printf("Free Physical Addr.\n");
    allc_addr = pmm_alloc_page();
    printf("Alloc Physical Addr: 0x%x\n", allc_addr);
}
