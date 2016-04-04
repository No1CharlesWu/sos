#include "timer.h"
#include "idt.h"

/* This will keep track of how many ticks that the system
*  has been running for */
int timer_ticks = 0;
int second = 0;

/* Handles the timer. In this case, it's very simple: We
*  increment the 'timer_ticks' variable every time the
*  timer fires. By default, the timer fires 18.222 times
*  per second. Why 18.222Hz? Some engineer at IBM must've
*  been smoking something funky */
void timer_handler(struct regs *r)
{
    /* Increment our 'tick count' */
    timer_ticks++;

    /* Every 18 clocks (approximately 1 second), we will
    *  display a message on the screen */
    if (timer_ticks % 100 == 0)
    {
	    second++;
	    timer_test(second);
    }
}

/* This will continuously loop until the given time has
 *  been reached */
void timer_wait(int ticks)
{
	unsigned long eticks;

	eticks = timer_ticks + ticks;
	while(timer_ticks < eticks);
}
void timer_phase(int hz)
{
	//	puts("timer_phase\n");
	int divisor = 1193180 / hz;       /* Calculate our divisor */
	outportb(0x43, 0x36);             /* Set our command byte 0x36 */
	outportb(0x40, divisor & 0xFF);   /* Set low byte of divisor */
	outportb(0x40, divisor >> 8);     /* Set high byte of divisor */
}
/* Sets up the system clock by installing the timer handler
 *  into IRQ0 */
void timer_install()
{
	/* Installs 'timer_handler' to IRQ0 */
	irq_install_handler(0, timer_handler);
	timer_phase(100);
}

void timer_test(int count)
{
	unsigned char c = count % 10 + 48;
	unsigned short *where = (unsigned short *)0xB8000;
	//int tmp = (((count+111) % 15) << 4) | ((count % 15) & 0x0F );
	//unsigned att = tmp << 8;
	unsigned att = 0x0F << 8;
	where += (0 * 80 + 79);
	*where = c | att;
}

