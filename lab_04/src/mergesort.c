#include "stdio.h"
#include "stdlib.h"

void data_copy(const char* source, char* destination, size_t size){
	int i = 0;
	while (i < size){
		*destination++ = *source++;
		i++;
	}
}


void merge_func(char* first_begin, char* first_end, char* second_begin, char* second_end, char* result, size_t size, int (*compar)(const void*, const void*)){
	while  (first_begin != first_end || second_begin != second_end){
		if (second_begin == second_end || (compar(first_begin, second_begin) == -1) && first_begin != first_end){
			data_copy(first_begin, result, size);
			first_begin = first_begin + size;
		}
		else{
			data_copy(second_begin, result, size);
			second_begin = second_begin + size;
		} 
		result = result + size;
	}
}

int mergesort(void* base, size_t num, size_t size, int (*compar)(const void*,const void*)){
	if (num > 1){
		mergesort(base, num/2, size, compar);
		mergesort((char*)base + (num/2)*size, num - num/2, size, compar);
		char* result = malloc(sizeof(char)*num*size);
		merge_func((char*) base, (char*) base + num/2*size, (char*) base + num/2*size, (char*) base + num*size, result, size, compar);
		data_copy(result, (char*) base, size*num);
		free(result);
	}
}
