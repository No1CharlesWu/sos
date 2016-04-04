#ifndef _KB_H_
#define _KB_H_

#include "idt.h"

/* Handles the keyboard interrupt */
void keyboard_handler(struct regs *r);

/* Installs the keyboard handler into IRQ1 */
void keyboard_install();

#endif

