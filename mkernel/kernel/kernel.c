/*
* Copyright (C) 2014  Arjun Sreedharan
* License: GPL version 2 or higher http://www.gnu.org/licenses/gpl.html
*/

#include "type.h"
#include "const.h"
#include "protect.h"
#include "print.h"

PUBLIC void* memcpy(void* pDst, void* pSrc, int iSize);
PUBLIC void disp_str(char * pszInfo);

extern char set_cursor(int data);
void sleep();

void cstart(void)
{
	char *str = "1";
	CleanScreen();
/*	int i , j ,k,a;
	for(i = 0;i < 100 ;i++)	
	{
		for(j = i; j < 79 ; j ++ )
		{
			Puts(str);
		}
		sleep();
		Puts("\na");
	}
	*/
	int i;
	char c;
	for(i = 0; i < 10; i++)
	{
		Puts("1234567890");
		c=set_cursor(1);
		sleep();
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
