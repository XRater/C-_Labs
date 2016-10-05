#pragma once
void merge_func(void* first_begin, void* first_end, void* second_begin, void* second_end, void* result, size_t size, int (*compar)(const void*, const void*));
int mergesort (void* base, size_t num, size_t size, int (*compar)(const void*,const void*));
void data_copy(char* source, char* destination, size_t size);