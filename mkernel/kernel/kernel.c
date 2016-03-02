#include "type.h"
#include "const.h"
#include "protect.h"
#include "print.h"

PUBLIC void* memcpy(void* pDst, void* pSrc, int iSize);
PUBLIC void disp_str(char * pszInfo);

void sleep();

void cstart(void)
{
	char *str = "1";
	CleanScreen();
	int i=0 , j=2 ,k,a;
	Printf("s%df%d",i,j);
	for(i = 0;i < 100 ;i++)	
	{
		for(j = i; j < 79 ; j ++ )
		{
			Puts(str);
		}
		sleep();
		Puts("\na");
	}
	return;
}

void sleep()
{
	int i,j,k;
	for(i = 0 ; i <10000;i++)
		for(k = 0; k < 10000;k ++)
			j = 1;
}
