#include "stddef.h"
char * strcpy(char * destination, const char * source){
	char *pos = destination;
	while (*source != '\0'){
		*pos = *source;
		pos++;
		source++;
	}
	*pos = '\0';
	return destination;
}

char * strcat(char * destination, const char * source){
	char *pos = destination;
	while (*pos != '\0')
		pos++;
	while (*source != '\0')
		*pos = *source, source++, pos++;
	*pos = '\0';
	return destination;
}

int strcmp(const char * str1, const char * str2){
	while (*str1 == *str2 && *str1 != '\0')
		str1++, str2++;
	return (int)*str1 - (int)*str2;
}

size_t strlen(const char * str){
	size_t res = 0;
	while (*str)
		res++, str++;
	return res;
}