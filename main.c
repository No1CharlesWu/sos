#include "type.h"
#include "multiboot.h"
#include "gdt.h"
#include "idt.h"
#include "scrn.h"

void sleep();
void TestForPrint();
void TestForMultiboot();
void *Memcpy(void *dest, const void *src, size_t count);
void *Memset(void *dest, char val, size_t count);
unsigned short *Memsetw(unsigned short *dest, unsigned short val, size_t count);
size_t strlen(const char *str);

void cstart()
{
	cls();
	Printf("\n======cstart begin======\n");
	init_video();
	gdt_install();
	idt_install();
//	TestForPrint();
	Printf("\n======cstart end========\n");
//	io_hlt();
	return;
}
void TestForMultiboot(unsigned long magic,unsigned long addr)
{
	Printf("\n====== TestForMultiboot begin======\n");

	multiboot_info_t *mbi;
	mbi = (multiboot_info_t*)addr;
	if(CHECK_FLAG(mbi->flags,0))
		Printf("mem_lower = %u KB,mem_upper = %u KB\n",(unsigned)mbi->mem_lower,(unsigned)mbi->mem_upper);

	Printf("\n====== TestForMultiboot end======\n");
}

void TestForPrint()
{
	Printf("\n====== TestForPrint begin ======\n");

	char *str = "5";
	int i=0 , j=2;
	for(i = 0;i < 29; i++)	
	{
		for(j = i; j < 79 ; j ++ )
		{
			Puts(str);
		}
		sleep();
		Puts("\n");
	}
	Printf("\n====== TestForPrint end======\n");
}

void sleep()
{
	int i,j;
	for(i = 0 ; i <1000;i++)
		for(j = 0; j < 10000;j ++);
}

void *Memcpy(void *dest, const void *src, size_t count)
{
    const char *sp = (const char *)src;
    char *dp = (char *)dest;
    for(; count != 0; count--) *dp++ = *sp++;
    return dest;
}

void *Memset(void *dest, char val, size_t count)
{
    char *temp = (char *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

unsigned short *Memsetw(unsigned short *dest, unsigned short val, size_t count)
{
    unsigned short *temp = (unsigned short *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

size_t strlen(const char *str)
{
    size_t retval;
    for(retval = 0; *str != '\0'; str++) retval++;
    return retval;
}

