#include "../include/str.h"

int test_strcpy(const char * destination, const char * source, char* answer)
{
	if (my_strcpy(destination, sourse) == answer)
		return 1;
	else
		return 0;		
}

int test_strcat(const char * destination, const char * source, char* answer)
{
	if (my_strcat(destination, sourse) == answer)
		return 1;
	else
		return 0;		
}

int test_strcmp(const char * str1, const char * str2, int answer)
{
	if (my_strcmp(str1, str2) == answer)
		return 1;
	else
		return 0;		
}

int test_strlen(const str, int answer)
{
	if (my_strlen(str) == answer)
		return 1;
	else
		return 0;		
}