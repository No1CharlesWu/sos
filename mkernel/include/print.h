#ifndef _PRINT_H_
#define _PRINT_H_

#define LINES 25
#define COLUMNS 80
#define BYTES_FOR_EACH_ELEMENT 2
#define SCREENSIZE LINES * COLUMNS * BYTES_FOR_EACH_ELEMENT

char *VIDPTR = (char*)0xb8000;

void CleanScreen();
void Putc(char c);
void Puts(char *str);
void CleanScreen()
{
	int i = 0;
	while(i < SCREENSIZE)
	{
		VIDPTR[i] = ' ';
		VIDPTR[i+1] = 0x07;
		i = i + 2;
	}
}

void Putc(char c)
{

}
void Puts(char *str)
{

}
#endif 
