#ifndef _MULTIBOOT_H_
#define _MULTIBOOT_H_
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
#endif 
