#include "type.h"
#include "const.h"
#include "protect.h"
#include "print.h"

PUBLIC void* memcpy(void* pDst, void* pSrc, int iSize);
PUBLIC void disp_str(char * pszInfo);
typedef struct aout_symbol_table  
{  
	unsigned long tabsize;  
	unsigned long strsize;  
	unsigned long addr;  
	unsigned long reserved;  
} aout_symbol_table_t;  

/* ELF 的 section header table。 */  
typedef struct elf_section_header_table  
{  
	unsigned long num;  
	unsigned long size;  
	unsigned long addr;  
	unsigned long shndx;  
} elf_section_header_table_t;  

/* Multiboot 信息。 */  
typedef struct multiboot_info  
{  
	unsigned long flags;  
	unsigned long mem_lower;  
	unsigned long mem_upper;  
	unsigned long boot_device;  
	unsigned long cmdline;  
	unsigned long mods_count;  
	unsigned long mods_addr;  
	union  
	{  
		aout_symbol_table_t aout_sym;  
		elf_section_header_table_t elf_sec;  
	} u;  
	unsigned long mmap_length;  
	unsigned long mmap_addr;  
} multiboot_info_t; 

 /* 检测 FLAGS 中的位 BIT 是否被置位。 */  
#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit))) 

void sleep();
void TestForPrint();

void cstart(unsigned long magic,unsigned long addr)
{
	multiboot_info_t *mbi;
	mbi = (multiboot_info_t*)addr;
	CleanScreen();

	Printf("Hello World\n");
	if(CHECK_FLAG(mbi->flags,0))
		Printf("mem_lower = %u KB,mem_upper = %u KB\n",(unsigned)mbi->mem_lower,(unsigned)mbi->mem_upper);

	TestForPrint();
	
	return;
}
void TestForPrint()
{
	char *str = "5";
	int i=0 , j=2 ,k,a;
	for(i = 0;i < 100 ;i++)	
	{
		for(j = i; j < 79 ; j ++ )
		{
			Puts(str);
		}
		sleep();
		Puts("\n");
	}
}

void sleep()
{
	int i,j,k;
	for(i = 0 ; i <5000;i++)
		for(k = 0; k < 10000;k ++)
			j = 1;
}
