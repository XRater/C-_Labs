#include <bmp_struct.h>

#pragma once
int init_bmp(bmp_t* bmp, size_t w, size_t h);
int load_bmp(const char* filename, bmpheader_t* header, bmp_t* bmp);
int save_bmp(const char* filename, const bmpheader_t* header, const bmp_t* bmp);
void free_bmp(bmp_t* bmp);

