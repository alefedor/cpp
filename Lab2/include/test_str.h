#ifndef __TEST_STR_H
#define __TEST_STR_H 
#include "stddef.h"
#include "stdbool.h"

bool equal(const char *a, const char* b);
char* test_strcpy(char *destination, const char *source, const char *ans);
char* test_strcat(char *destination, const char *source, const char *ans);
char* test_strcmp(const char *str1, const char *str2, int ans);
char* test_strlen(const char *str, size_t ans);

#endif