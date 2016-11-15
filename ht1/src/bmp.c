#include <stdio.h>
#include <stdlib.h>
#include <bmp.h>

void init_bmp(bmp_t* bmp){
    bmp->pixels = malloc(bmp->height * sizeof(pixel_t*));
    for (int i = 0; i < bmp->height; i++)
        bmp->pixels[i] = malloc(bmp->width * sizeof(pixel_t));

	bmp->alignment_size = bmp->width % 4;
	bmp->alignment = malloc(bmp->alignment_size);   
	for (int i = 0; i < bmp->alignment_size; i++)
		bmp->alignment[i] = 255;
}


int load_bmp(const char* filename, bmpheader_t* header, bmp_t* bmp){
    FILE* input;
    input = fopen(filename, "rb");
    if (!input) {
        printf("Failed to open input file\n");
        return 1;
    }
    
    fread(header, sizeof(char), 54, input); 
    bmp->height = header->biHeight;
    bmp->width = header->biWidth;
    bmp->pixel_number = header->biWidth*header->biHeight;
    init_bmp(bmp);
    for (int i = 1; i <= bmp->height; i++){
        fread(bmp->pixels[bmp->height - i], sizeof(pixel_t), bmp->width, input);
    	fread(bmp->alignment, 1, bmp->alignment_size, input);
    }
      
    fclose(input);  
    return 0;  
}


int save_bmp(const char* filename, const bmpheader_t* const header, const bmp_t* bmp){
    FILE* output;
    output = fopen(filename, "wb");
    fwrite(header, sizeof(char), 54, output);
    for (int i = 1; i <= bmp->height; i++){
        fwrite(bmp->pixels[bmp->height - i], sizeof(pixel_t), bmp->width, output);
    	fwrite(bmp->alignment, 1, bmp->alignment_size, output);
    }
    
    fclose(output);  
    return 0;  
}


void free_bmp(bmp_t* bmp){
    for (int i = 0; i < bmp->height; i++)
        free(bmp->pixels[i]);

    free(bmp->pixels);
 	free(bmp->alignment);
    free(bmp);
}


void mask_bmp(bmp_t* bmp){
    for (int i = 0; i < bmp->height; i++)
        for (int j = 0; j < bmp->width; j++){
            bmp->pixels[i][j].r -= bmp->pixels[i][j].r % 5;
            bmp->pixels[i][j].g -= bmp->pixels[i][j].g % 5;
            bmp->pixels[i][j].b -= bmp->pixels[i][j].b % 5;
        }
}


int crop_rotate_bmp(bmpheader_t* header, const bmp_t* bmp, bmp_t* resbmp, size_t x, size_t y, size_t w, size_t h){
    if (x < 0 || y < 0|| x >= bmp->width || y >= bmp->height){
        printf("Point is out of image\n");
        return 1;
    }
    
    if (w <= 0 || h <= 0){
       printf("Incorrect size\n"); 
       return 1;
    }
    
    if (y + h  > bmp->height || x + w  > bmp->width){
        printf("Second point is out of image\n");
            return 1;
    } 
    
    
    resbmp->width = h;
    resbmp->height = w;
    init_bmp(resbmp);
    header->biWidth = h;
    header->biHeight = w;
    header->bfSize = sizeof(bmpheader_t) + w * (sizeof(pixel_t) * h + resbmp->alignment_size);
    header->biSizeImage = w * (sizeof(pixel_t) * h + resbmp->alignment_size);
  	for (int i = 0; i < w; i++)
  		for (int j = 0; j < h; j++)
  			resbmp->pixels[i][j] = bmp->pixels[y + h - j - 1][x + i];

    return 0;
}

