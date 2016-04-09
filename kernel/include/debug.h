#ifndef _DEBUG_H_
#define _DEBUG_H_

#define PANIC(msg) panic(msg, __FILE__, __LINE__);
#define ASSERT(b) ((b) ? (void)0 : panic_assert(__FILE__, __LINE__, #b))

void panic(char *message,char *file, unsigned int line);

void panic_assert(char *file, unsigned int line, char *desc);

#endif 
