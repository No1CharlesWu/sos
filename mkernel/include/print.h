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
static void itoa (char *buf, int base, int d);
void Printf(const char *format, ...);

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
	set_cursor(INDEX/2);
}

void Putc(char c)
{
	switch(c)
	{
		case '\n' :
			INDEX = (INDEX / (COLUMNS * BYTES_FOR_EACH_ELEMENT) + 1)*(COLUMNS * BYTES_FOR_EACH_ELEMENT);
			set_cursor(INDEX/2);
			break;
		default :
			if(INDEX == SCREENSIZE)
			{
				RollScreen();	
			}
			VIDPTR[INDEX ] = c;
			VIDPTR[INDEX +1] = TXT_COLOR;
			INDEX = INDEX + 2;
			set_cursor(INDEX/2);
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
	set_cursor(INDEX/2);
}

/* 将整数 D 转换为字符串并保存在 BUF 中。如果 BASE 为 'd'，则 D 为十进制，如果 BASE 为 'x'，则 D 为十六进制。 */  
static void itoa (char *buf, int base, int d)  
{  
	char *p = buf;  
	char *p1, *p2;  
	unsigned long ud = d;  
	int divisor = 10;  

	/* 如果指定了 %d 并且 D 是负数，在开始添上负号。 */  
	if (base == 'd' && d < 0)  
	{  
		*p++ = '-';  
		buf++;  
		ud = -d;  
	}  
	else if (base == 'x')  
		divisor = 16;  

	/* 用 DIVISOR 去除 UD 直到 UD == 0。 */  
	do  
	{  
		int remainder = ud % divisor;  

		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;  
	}  
	while (ud /= divisor);  

	/* 在字符串尾添上终结符。 */  
	*p = 0;  

	/* 反转 BUF。 */  
	p1 = buf;  
	p2 = p - 1;  
	while (p1 < p2)  
	{  
		char tmp = *p1;  
		*p1 = *p2;  
		*p2 = tmp;  
		p1++;  
		p2--;  
	}  
}  
/*
static void putchar (int c)  
{  
	if (c == '\n' || c == '\r')  
	{  
newline:  
		xpos = 0;  
		ypos++;  
		if (ypos >= LINES)  
			ypos = 0;  
		return;  
	}  

	*(video + (xpos + ypos * COLUMNS) * 2) = c & 0xFF;  
	*(video + (xpos + ypos * COLUMNS) * 2 + 1) = ATTRIBUTE;  

	xpos++;  
	if (xpos >= COLUMNS)  
		goto newline;  
}  
*/
/* 格式化字符串并在屏幕上输出，就像 libc 函数 printf 一样。 */  
void Printf(const char *format, ...)  
{  
	char **arg = (char **) &format;  
	int c;  
	char buf[20];  

	arg++;  

	while ((c = *format++) != 0)  
	{  
		if (c != '%')  
			Putc(c);  
		else  
		{  
			char *p;  

			c = *format++;  
			switch (c)  
			{  
				case 'd':  
				case 'u':  
				case 'x':  
					itoa (buf, c, *((int *) arg++));  
					p = buf;  
					goto string;  
					break;  

				case 's':  
					p = *arg++;  
					if (! p)  
						p = "(null)";  

string:  
					while (*p)  
						Putc(*p++);  
					break;  

				default:  
					Putc(*((int *) arg++));  
					break;  
			}  
		}  
	}  
}  
#endif 
