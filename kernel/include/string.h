#ifndef _STRING_H_
#define _STRING_H_

#include "type.h"

void *memcpy(void *dest, const void *src, size_t count);

void *memset(void *dest, char val, size_t count);

unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count);

// Compare two strings. Should return -1 if 
// str1 < str2, 0 if they are equal or 1 otherwise.
int strcmp(char *str1, char *str2);

// Copy the NULL-terminated string src into dest, and
// return dest.
char *strcpy(char *dest, const char *src);

// Concatenate the NULL-terminated string src onto
// the end of dest, and return dest.
char *strcat(char *dest, const char *src);

size_t strlen(const char *str);

#endif 
