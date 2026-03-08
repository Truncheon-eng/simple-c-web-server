#ifndef STRING_H
#define STRING_H

#include <stddef.h>
#include <stdbool.h>

char * lines(char * text);
char * memset(char * ptr, char fill, size_t count);
size_t strlen(const char * s);
int atoi(char * str);
int strncmp(const char * s1, const char * s2, size_t count);
char * find(char * str, char symb);

#endif