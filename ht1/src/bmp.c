#include <stdio.h>
#include <stdlib.h>
#include "../include/bmp.h"

void init_bmp(bmp_t* bmp){
    bmp->pixels = malloc(bmp->height*sizeof(pixel_t*));
    int i;
    for (i = 0; i < bmp->height; i++)
        bmp->pixels[i] = malloc(bmp->width*sizeof(pixel_t));
}

int load_bmp(char* filename, bmpheader_t* header, bmp_t* bmp){
    FILE* input;
    input = fopen(filename, "rb");
    if (input == NULL) {
        printf("Failed to open input file\n");
        return 1;
    }
    fread(header, sizeof(char), 54, input); 
    bmp->height = header->biHeight;
    bmp->width = header->biWidth;
    bmp->pixel_number = header->biWidth*header->biHeight;
    init_bmp(bmp);
    int i;
    for (i = 1; i <= bmp->height; i++)
        fread(bmp->pixels[bmp->height - i], sizeof(pixel_t), bmp->width, input);  
    fclose(input);  
    return 0;  
}

int save_bmp(char* filename, bmpheader_t* header, bmp_t* bmp){
    FILE* output;
    output = fopen(filename, "wb");
    if (output == NULL) {
        printf("Failed to open output file\n");
        return 1;
    }
    fwrite(header, sizeof(char), 54, output);
    int i;
    for (i = 1; i <= bmp->height; i++)
        fwrite(bmp->pixels[bmp->height - i], sizeof(pixel_t), bmp->width, output);
    fclose(output);  
    return 0;  
}

void free_bmp(bmp_t* bmp){
    int i;
    for (i = 0; i < bmp->height; i++)
        free(bmp->pixels[i]);
    free(bmp->pixels);
    free(bmp);
}

void mask_bmp(bmp_t* bmp){
    int i, j;
    for (i = 0; i < bmp->height; i++)
        for (j = 0; j < bmp->width; j++){
            bmp->pixels[i][j].r -= bmp->pixels[i][j].r%5;
            bmp->pixels[i][j].g -= bmp->pixels[i][j].g%5;
            bmp->pixels[i][j].b -= bmp->pixels[i][j].b%5;
        }
}


int crop_rotate_bmp(bmpheader_t* header, bmp_t* bmp, bmp_t* resbmp, size_t x, size_t y, size_t w, size_t h){
    if (x < 0 || y < 0|| x >= bmp->width || y >= bmp->height){
        printf("Point is out of image\n");
        return 1;
    }
    if (w <= 0 || h <= 0){
       printf("Incorrect size\n"); 
       return 1;
    }
    if (x + h  > bmp->height || y + w  > bmp->width){
        printf("Second point is out of image\n");
        return 1;
    }
    header->biWidth = h;
    header->biHeight = w;
    int i, j;
    resbmp->height = w;
    resbmp->width = h;
    init_bmp(resbmp);
    for (i = x; i < x + h; i++)
        for (j = y; j < y + w; j++)
            resbmp->pixels[j - y][i - x] = bmp->pixels[i][j];
    return 0;
}

