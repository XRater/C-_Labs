#include "stddef.h"

char* strcpy(char* destination, const char* source)
{
	char* temp_destination = destination;
	while(*source)
		*temp_destination++ = *source++;
	*temp_destination = '\0';
    return destination;
}

char* strcat(char* destination, const char* source)
{
	char* temp_destination=destination;
	while(*++temp_destination)
		continue;
	while(*source)
		*temp_destination++ = *source++;
	*temp_destination = '\0';
	return destination;
}

int strcmp(const char* str1, const char* str2)
{
	const char* temp_str1 = str1;
	const char* temp_str2 = str2;
	while (*str1||*str2)
	{
		if (*str1 > *str2)
			return 1;
		else if (*str1 < *str2) 
			return -1;
		*str1++;
		*str2++;
	}
	return 0;
}

size_t strlen(const char* str)
{
 	 const char* temp_str = str;
 	 size_t size = 0;
  	 while (*str++)
   		size++;
     return size;
}
