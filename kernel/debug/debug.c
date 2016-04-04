#include "debug.h"
#include "scrn.h"

void panic(char *message,char *file, unsigned int line)
{
    // We encountered a massive problem and have to stop.
    __asm__ __volatile__ ("cli"); // Disable interrupts.
    printf("PANIC(%s) at %s:%d\n",message,file,line);
    // Halt by going into an infinite loop.
    for(;;);
}

void panic_assert(char *file, unsigned int line, char *desc)
{
    // An assertion failed, and we have to panic.
    __asm__ __volatile__ ("cli"); // Disable interrupts.

    printf("ASSERTION-FAILED(%s) at %s: %d\n",desc,file,line);
    // Halt by going into an infinite loop.
    for(;;);
}
