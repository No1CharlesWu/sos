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

void cstart(void)
{
	char *str = "first kernel\n";
	CleanScreen();
	Puts("123456789012345678901234567890123456789012345678901234567890123456789012345678901234\n567890\n");
	Puts(str);
	return;
}

