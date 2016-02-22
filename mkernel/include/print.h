#ifndef _PRINT_H_
#define _PRINT_H_

#define LINES 25
#define COLUMNS 80
#define BYTES_FOR_EACH_ELEMENT 2
#define SCREENSIZE LINES * COLUMNS * BYTES_FOR_EACH_ELEMENT
#define TXT_COLOR 0x07
char *VIDPTR = (char*)0xb8000;
static char *INDEX = (char*)0xb8000;
static int count = 0;
void CleanScreen();
void Putc(char c);
void Puts(char *str);
void CleanScreen()
{
	int i = 0;
	while(i < SCREENSIZE)
	{
		VIDPTR[i] = ' ';
		VIDPTR[i+1] = TXT_COLOR;
		i = i + 2;
	}
	INDEX = VIDPTR;
	count = 0;
}

void Putc(char c)
{
	switch(c)
	{
		case '\n' :
			count = (count / (COLUMNS * BYTES_FOR_EACH_ELEMENT) + 1)*(COLUMNS * BYTES_FOR_EACH_ELEMENT);
			break;
		default :
			VIDPTR[count] = c;
			VIDPTR[count+1] = TXT_COLOR;
			count = count + 2;
			break;
	}
}
void Puts(char *str)
{
	int i = 0;
	while(str[i] != '\0')
	{
		Putc(str[i]);
		i++;
	}
}
#endif 
