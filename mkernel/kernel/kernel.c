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
	const char *str = "first kernel";
	CleanScreen();
	/* this loop writes the string to video memory */
	char *vidptr = (char*)0xb8000;
	int j = 0;
	int i = 0;
	while (str[j] != '\0') {
		/* the character's ascii */
		vidptr[i] = str[j];
		/* attribute-byte: give character black bg and light grey fg */
		vidptr[i+1] = 0x07;
		++j;
		i = i + 2;
	}
	return;
}

