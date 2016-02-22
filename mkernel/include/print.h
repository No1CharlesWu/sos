#ifndef _PRINT_H_
#define _PRINT_H_

#define LINES 25
#define COLUMNS 80
#define BYTES_FOR_EACH_ELEMENT 2
#define SCREENSIZE LINES * COLUMNS * BYTES_FOR_EACH_ELEMENT
#define TXT_COLOR 0x07

char *VIDPTR = (char*)0xb8000;
static int INDEX = 0;

void CleanScreen();
void RollScreen();  
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
	INDEX = 0;
}

void Putc(char c)
{
	switch(c)
	{
		case '\n' :
			INDEX = (INDEX / (COLUMNS * BYTES_FOR_EACH_ELEMENT) + 1)*(COLUMNS * BYTES_FOR_EACH_ELEMENT);
			break;
		default :
			if(INDEX == SCREENSIZE)
			{
				RollScreen();	
			}
			VIDPTR[INDEX ] = c;
			VIDPTR[INDEX +1] = TXT_COLOR;
			INDEX = INDEX + 2;
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
void RollScreen()
{
	int i, j;
	for(i = 0,j = COLUMNS * BYTES_FOR_EACH_ELEMENT;j < SCREENSIZE;i++,j++)
	{
		VIDPTR[i] = VIDPTR[j];
	}
	for(i = (COLUMNS * BYTES_FOR_EACH_ELEMENT * (LINES - 1));i < SCREENSIZE;i = i + 2)
	{
		VIDPTR[i] = ' ';
		VIDPTR[i+1] = TXT_COLOR;
	}
	INDEX =  (COLUMNS * BYTES_FOR_EACH_ELEMENT * (LINES -1 ));
}
#endif 
