#include "type.h"
#include "const.h"
#include "protect.h"
#include "print.h"
#include "multiboot.h"

PUBLIC void* memcpy(void* pDst, void* pSrc, int iSize);
PUBLIC void disp_str(char * pszInfo);
void sleep();
void TestForPrint();
void TestForMultiboot();

void cstart(unsigned long magic,unsigned long addr)
{
	CleanScreen();
	Printf("\n======cstart begin======\n");
	int i;
	for(i=0xb8001;i<=0xb8fff;i=i+2)
		write_mem8(i,15);
	io_hlt();
//	TestForPrint();
//	TestForMultiboot(magic,addr);
	Printf("\n======cstart end======\n");
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
	int i=0 , j=2, k;
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
	int i,j,k;
	for(i = 0 ; i <1000;i++)
		for(k = 0; k < 10000;k ++)
			j = 1;
}
