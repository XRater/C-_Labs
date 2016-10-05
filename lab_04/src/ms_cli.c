#include "stdio.h"
#include "string.h"
#include "../include/mergesort.h"

int int_compare(const void* first, const void* second){
	int* a = (int*) first;
	int* b = (int*) second;
	if (*a > *b) 
		return 1;
	if (*a == *b)
		return 0;
	if (*a < *b)
		return -1;
}

int char_compare(const void* first, const void* second){
	char* a = (char*) first;
	char* b = (char*) second;
	if (*a > *b) 
		return 1;
	if (*a == *b)
		return 0;
	if (*a < *b)
		return -1;
}

int main(int argc, char* argv[]){
	int data1[5] = {5, 4, 2, 3, 2};
	int k = 0;
	mergesort(data1, 5, sizeof(int), int_compare);
	for (k = 0; k < 5; k++)
		printf("%d ", data1[k]);

	printf("\n");
	char data2[6] = {'1', 's', '%', 'r', ')', 'T'};
	k = 0;
	mergesort(data2, 6, sizeof(char), char_compare);
	for (k = 0; k < 6; k++)
		printf("%c ", data2[k]);	
}
