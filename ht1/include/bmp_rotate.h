#include <bmp_struct.h>

#pragma once
int crop_rotate_bmp(bmpheader_t* header, const bmp_t* bmp, bmp_t* resbmp, size_t x, size_t y, size_t w, size_t h);
