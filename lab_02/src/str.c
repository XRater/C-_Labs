char* my_strcpy(char* destination, const char* source)
{
	while(*source)
		*destination++ = *source++;
	*destination = '\0';
    return destination;
}

char* my_strcat(char* destination, const char* source)
{

	while(*++destination)
		continue;
	while(*source)
		*destination++ = *source++;
	*destination = '\0';
	return destination;
}

int my_strcmp(const char* str1, const char* str2)
{
	while (*str1||*str2)
		if ((*str1++) != (*str2++))
			return 0;
	return 1;
}

int my_strlen(const char* str)
{
   int size = 0;
   while (*str++)
   		size++;
   return size;
}
