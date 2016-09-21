#include "stddef.h"

char* strcpy(char* destination, const char* source)
{
	while(*source)
		*destination++ = *source++;
	*destination = '\0';
    return destination;
}

char* strcat(char* destination, const char* source)
{

	while(*++destination)
		continue;
	while(*source)
		*destination++ = *source++;
	*destination = '\0';
	return destination;
}

int strcmp(const char* str1, const char* str2)
{
	while (*str1||*str2)
		if ((*str1++) != (*str2++))
			return 0;
	return 1;
}

size_t strlen(const char* str)
{
 	 size_t size = 0;
  	 while (*str++)
   		size++;
     return size;
}
