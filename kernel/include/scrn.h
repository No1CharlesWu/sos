#ifndef _SCRN_H_
#define _SCRN_H_

#define LINES 25
#define COLUMNS 80
#define BYTES_FOR_EACH_ELEMENT 2
#define SCREENSIZE LINES * COLUMNS * BYTES_FOR_EACH_ELEMENT

#define black	0x00
#define blue 	0x01
#define green	0x02
#define	cyan	0x03
#define red	0x04
#define	magenta	0x05
#define	brown	0x06
#define light_grey	0x07
#define dark_grey	0x08
#define	light_green	0x09
#define	light_cyan	0x0a
#define light_red	0x0b
#define	light_magenta	0x0c
#define light_brown	0x0d
#define white	0x0f

#define TXT_COLOR white

void CleanScreen();

void RollScreen();  

void itoa (char *buf, int base, int d);

void printf(const char *format, ...);

/* Scrolls the screen */
void scroll(void);

void move_csr(void);

/* Clears the screen */
void cls();

/* puts a single character on the screen */
void putc(unsigned char c);

/* Uses the above routine to output a string... */
void puts(unsigned char *text);

/* Sets the forecolor and backcolor that we will use */
void settextcolor(unsigned char forecolor, unsigned char backcolor);

/* Sets our text-mode VGA pointer, then clears the screen for us */
void init_video(void);

void CleanScreen();

void MyPutc(char c);

void MyPuts(char *str);

void RollScreen();

/* 将整数 D 转换为字符串并保存在 BUF 中。如果 BASE 为 'd'，则 D 为十进制，如果 BASE 为 'x'，则 D 为十六进制。 */  
void itoa (char *buf, int base, int d);

/* 格式化字符串并在屏幕上输出，就像 libc 函数 printf 一样。 */  
void printf(const char *format, ...);

#endif 

