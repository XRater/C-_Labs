#include <stdlib.h>

#pragma once
typedef struct Pixel{
    char b;
    char g;
    char r;
} pixel_t;


typedef struct BMP{
    pixel_t** pixels;
    char* alignment;
    size_t alignment_size;
    size_t width;
    size_t height;
    size_t pixel_number;
} bmp_t;

#pragma pack(push, 1)
typedef struct BMPHeader{
    short bfType;
    int bfSize;
    short bfReserved1;
    short bfReserved2;
    int bfOffBits;
    int biSize;
    int biWidth;
    int biHeight; 
    short biPlanes;
    short biBitCount;
    int biCompression;
    int biSizeImage; 
    int biXPelsPerMeter;
    int biYPelsPerMeter;
    int biClrUsed; 
    int biClrImportant;    
} bmpheader_t;
#pragma pack(pop)

void init_bmp(bmp_t* bmp);
int load_bmp(const char* filename, bmpheader_t* header, bmp_t* bmp);
int save_bmp(const char* filename, const bmpheader_t* header, const bmp_t* bmp);
void free_bmp(bmp_t* bmp);
void mask_bmp(bmp_t* bmp);
int crop_rotate_bmp(bmpheader_t* header, const bmp_t* bmp, bmp_t* resbmp, size_t x, size_t y, size_t w, size_t h);
