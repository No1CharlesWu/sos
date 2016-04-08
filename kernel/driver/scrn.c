#include "scrn.h"
#include "string.h"
#include "common.h"

static char *VIDPTR = (char*)0xC00b8000;
static int INDEX = 0;
static unsigned short *textmemptr = (unsigned short *)0xC00b8000;
static int attrib = TXT_COLOR;
static int csr_x = 0, csr_y = 0;

/* Scrolls the screen */
void scroll(void)
{
    unsigned blank, temp;

    /* A blank is defined as a space... we need to give it
    *  backcolor too */
    blank = 0x20 | (attrib << 8);

    /* Row 25 is the end, this means we need to scroll up */
    if(csr_y >= LINES)
    {
        /* Move the current text chunk that makes up the screen
        *  back in the buffer by a line */
        temp = csr_y - LINES + 1;
        memcpy (textmemptr, textmemptr + temp * COLUMNS , (LINES - temp) *  COLUMNS * 2);

        /* Finally, we set the chunk of memory that occupies
        *  the last line of text to our 'blank' character */
        memsetw (textmemptr + (LINES - temp) * COLUMNS , blank, COLUMNS );
        csr_y = LINES - 1;
    }
}

void move_csr(void)
{
    unsigned temp;

    temp = csr_y *  COLUMNS + csr_x;

    outportb(0x3D4, 14);
    outportb(0x3D5, temp >> 8);
    outportb(0x3D4, 15);
    outportb(0x3D5, temp);
}

/* Clears the screen */
void cls()
{
    unsigned blank;
    int i;

    /* Again, we need the 'short' that will be used to
    *  represent a space with color */
    blank = 0x20 | (attrib << 8);

    /* Sets the entire screen to spaces in our current
    *  color */
    for(i = 0; i <LINES ; i++)
        memsetw (textmemptr + i * COLUMNS , blank, COLUMNS );

    /* Update out virtual cursor, and then move the
    *  hardware cursor */
    csr_x = 0;
    csr_y = 0;
    move_csr();
}

/* puts a single character on the screen */
void putc(unsigned char c)
{
    unsigned short *where;
    unsigned att = attrib << 8;

    /* Handle a backspace, by moving the cursor back one space */
    if(c == 0x08)
    {
        if(csr_x != 0) csr_x--;
	char tmp = ' ';
	where = textmemptr + (csr_y * COLUMNS + csr_x);
	*where = tmp | att;	
    }
    /* Handles a tab by incrementing the cursor's x, but only
    *  to a point that will make it divisible by 8 */
    else if(c == 0x09)
    {
        csr_x = (csr_x + 8) & ~(8 - 1);
    }
    /* Handles a 'Carriage Return', which simply brings the
    *  cursor back to the margin */
    else if(c == '\r')
    {
        csr_x = 0;
    }
    /* We handle our newlines the way DOS and the BIOS do: we
    *  treat it as if a 'CR' was also there, so we bring the
    *  cursor to the margin and we increment the 'y' value */
    else if(c == '\n')
    {
        csr_x = 0;
        csr_y++;
    }
    /* Any character greater than and including a space, is a
    *  printable character. The equation for finding the index
    *  in a linear chunk of memory can be represented by:
    *  Index = [(y * width) + x] */
    else if(c >= ' ')
    {
        where = textmemptr + (csr_y *  COLUMNS + csr_x);
        *where = c | att;	/* Character AND attributes: color */
        csr_x++;
    }
    /* If the cursor has reached the edge of the screen's width, we
    *  insert a new line in there */
    if(csr_x >= COLUMNS )
    {
        csr_x = 0;
        csr_y++;
    }

    /* Scroll the screen if needed, and finally move the cursor */
    scroll();
    move_csr();
}

/* Uses the above routine to output a string... */
void puts(unsigned char *text)
{
    int i;

    for (i = 0; i < strlen((const char *)text); i++)
    {
        putc(text[i]);
    }
}

/* Sets the forecolor and backcolor that we will use */
void settextcolor(unsigned char forecolor, unsigned char backcolor)
{
    /* Top 4 bytes are the background, bottom 4 bytes
    *  are the foreground color */
    attrib = (backcolor << 4) | (forecolor & 0x0F);
}

/* Sets our text-mode VGA pointer, then clears the screen for us */
void init_video(void)
{
    textmemptr = (unsigned short *)0xC00B8000;
    //cls();
}

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

void MyPutc(char c)
{
	switch(c)
	{
		case '\n' :
			INDEX = (INDEX / (COLUMNS * BYTES_FOR_EACH_ELEMENT) + 1)*(COLUMNS * BYTES_FOR_EACH_ELEMENT);
			if(INDEX >= SCREENSIZE)
			{
				RollScreen();
			}
			//set_cursor(INDEX/2);
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

void MyPuts(char *str)
{
	int i = 0;
	while(str[i] != '\0')
	{
		putc(str[i]);
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
void itoa (char *buf, int base, int d)  
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
/* 格式化字符串并在屏幕上输出，就像 libc 函数 printf 一样。 */  
void printf(const char *format, ...)  
{  
	char **arg = (char **) &format;  
	int c;  
	char buf[20];  

	arg++;  

	while ((c = *format++) != 0)  
	{  
		if (c != '%')  
			putc(c);  
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
						putc(*p++);  
					break;  

				default:  
					putc(*((int *) arg++));  
					break;  
			}  
		}  
	}  
}  
