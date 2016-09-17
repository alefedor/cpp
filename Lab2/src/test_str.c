#include "../include/str.h"
#include "stddef.h"
#include "stdio.h"
#include "stdbool.h"

bool equal(const char *a, const char* b){
	while (*a == *b && *a != '\0')
		a++, b++;
	return (*a == *b && *a == '\0');
}

char* test_strcpy(char *destination, const char *source, const char* ans){
	if (equal(ans, strcpy(destination, source)))
		return "OK";
	else
		return "Error";
}

char* test_strcat(char *destination, const char *source, const char* ans){
	if (equal(ans, strcat(destination, source)))
		return "OK";
	else
		return "Error";
}

char* test_strcmp(const char *str1, const char *str2, int ans){
	int res = strcmp(str1, str2);
	if ((ans == 0 && res == 0) || ans * res > 0)
		return "OK";
	else
		return "Error";
}

char* test_strlen(const char *str, size_t ans){
	size_t a = strlen(str);
	if (ans == a)
		return "OK";
	else
		return "Error";
}