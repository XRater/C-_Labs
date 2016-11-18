#include <stdio.h>
#include <stdlib.h>
#include <bmp_rotate.h>

int crop_rotate_bmp(bmpheader_t* header, const bmp_t* bmp, bmp_t* resbmp, size_t x, size_t y, size_t w, size_t h) {
//Input correctness 
    if (x < 0 || y < 0|| x >= bmp->width || y >= bmp->height){
        printf("Point is out of image\n");
        return 1;
    }
    if (w <= 0 || h <= 0) {
       printf("Incorrect size\n"); 
       return 1;
    }
    if (y + h  > bmp->height || x + w  > bmp->width) {
        printf("Second point is out of image\n");
        return 1;
    } 
//Fill new header    
//    resbmp->width = h;
//    resbmp->height = w;
//    init_bmp(resbmp);
    header->biWidth = h;
    header->biHeight = w;
    header->bfSize = sizeof(bmpheader_t) + w * (sizeof(pixel_t) * h + resbmp->alignment_size);
    header->biSizeImage = w * (sizeof(pixel_t) * h + resbmp->alignment_size);
//Fill pixels
  	for (int i = 0; i < w; i++)
  		for (int j = 0; j < h; j++)
  			resbmp->pixels[i][j] = bmp->pixels[y + h - j - 1][x + i];
    return 0;
}

