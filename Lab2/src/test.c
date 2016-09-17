#include "../include/test_str.h"
#include "stdio.h"

int main(){
	{
	char a1[] = "", a2[] = "a", a3[] = "abcd";
	printf("Testing strlen\n");
	printf("Test 1(str = %s): %s\n", a1, test_strlen(a1, 0));
	printf("Test 2(str = %s): %s\n", a2, test_strlen(a2, 1));
	printf("Test 3(str = %s): %s\n", a3, test_strlen(a3, 4));
	}
	{	
	char s1[] = "", s2[] = "a", s3[] = "abc", s4[] = "b";
	printf("Testing strcmp\n");
	printf("Test 1(str1 = %s, str2 = %s): %s\n", s1, s1, test_strcmp(s1, s1, 0));
	printf("Test 2(str1 = %s, str2 = %s): %s\n", s3, s4, test_strcmp(s3, s4, -1));
	printf("Test 3(str1 = %s, str2 = %s): %s\n", s4, s3, test_strcmp(s4, s3, 1));	
	printf("Test 4(str1 = %s, str2 = %s): %s\n", s1, s2, test_strcmp(s1, s2, -1));
	printf("Test 5(str1 = %s, str2 = %s): %s\n", s3, s3, test_strcmp(s3, s3, 0));
	}
	{
	char s1[] = "", s2[] = "a", s3[] = "abc";
	char d1[10] = "", d2[10] = "a", d3[10] = "abc", d4[10] = "", d5[10] = "a";
	char a1[] = "", a2[] = "abc", a3[] = "aa", a4[] = "abc", a5[] = "aabc";
	printf("Testing strcat\n");
	printf("Test 1(destination = %s, source = %s): ", d1, s1); 
	printf("%s\n", test_strcat(d1, s1, a1));
	printf("Test 2(destination = %s, source = %s): ", d4, s3); 
	printf("%s\n", test_strcat(d4, s3, a2));
	printf("Test 3(destination = %s, source = %s): ", d2, s2); 
	printf("%s\n", test_strcat(d2, s2, a3));
	printf("Test 4(destination = %s, source = %s): ", d3, s1); 
	printf("%s\n", test_strcat(d3, s1, a4));
	printf("Test 5(destination = %s, source = %s): ", d5, s3); 
	printf("%s\n", test_strcat(d5, s3, a5));	
	}
	{
	char s1[] = "", s2[] = "a", s3[] = "abc";
	char d1[10] = "", d2[10] = "a", d3[10] = "abc", d4[10] = "", d5[10] = "a";
	char a1[] = "", a2[] = "a", a3[] = "abc";
	printf("Testing strcpy\n");
	printf("Test 1(destination = %s, source = %s): ", d1, s1); 
	printf("%s\n", test_strcpy(d1, s1, a1));
	printf("Test 2(destination = %s, source = %s): ", d2, s2); 
	printf("%s\n", test_strcpy(d2, s2, a2));
	printf("Test 3(destination = %s, source = %s): ", d3, s2); 
	printf("%s\n", test_strcpy(d3, s2, a2));
	printf("Test 4(destination = %s, source = %s): ", d4, s2); 
	printf("%s\n", test_strcpy(d4, s2, a2));
	printf("Test 5(destination = %s, source = %s): ", d5, s3); 
	printf("%s\n", test_strcpy(d5, s3, a3));	
	}	
	return 0;
}