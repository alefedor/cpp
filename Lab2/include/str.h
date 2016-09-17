#ifndef __STR_H
#define __STR_H 
#include "stddef.h"
char * strcpy(char * destination, const char * source);
char * strcat(char * destination, const char * source);
int strcmp(const char * str1, const char * str2);
size_t strlen(const char * str);

#endif