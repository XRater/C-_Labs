#include "../include/str.h"
#include "stddef.h"
#include "stdio.h"

int test_strcpy(char * destination, const char * source, char* answer)
{
	if (strcmp(strcpy(destination, source), answer) == 0)
		return 1;
	else
		return 0;		
}

int test_strcat(char * destination, const char * source, char* answer)
{
	if (strcmp(strcat(destination, source), answer) == 0)
		return 1;
	else
		return 0;		
}

int test_strcmp(const char * str1, const char * str2, int answer)
{
	if (strcmp(str1, str2) == answer)
		return 1;
	else
		return 0;		
}

int test_strlen(const char* str, size_t answer)
{
	if (strlen(str) == answer)
		return 1;
	else
		return 0;		
}