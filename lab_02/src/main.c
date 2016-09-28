#include "../include/str.h"
#include "../include/tests.h"
#include "stdio.h"
#include "stddef.h"

int main()
{
	char s1[] = "123456";
	char s2[] = "1234";
	printf("strlen: %d\n", test_strlen(s1, 6));
	printf("strcmp: %d\n", test_strcmp(s1, s2, 1));
	char s3[] = "789";
	printf("strcat: %d\n", test_strcat(s1, s3, "123456789"));
	char s4[] = "qwerty";
	printf("strcpy: %d\n", test_strcpy(s1, s4, "qwerty"));

}
