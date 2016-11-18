#include <stdio.h>
#include <stdlib.h>
#include <bmp_init.h>

int init_bmp(bmp_t* bmp, size_t w, size_t h) {
//Allocate meaningfull pixels
    if (w < 0|| h < 0){
        printf("Incorrect size initialization");
        return 1;
    }
    bmp->width = w;
    bmp->height = h;
    bmp->pixel_number = w * h;
    bmp->pixels = malloc(bmp->height * sizeof(pixel_t*));
    for (int i = 0; i < bmp->height; i++)
        bmp->pixels[i] = malloc(bmp->width * sizeof(pixel_t));
//Fill alignment pixels with zeores
	bmp->alignment_size = bmp->width % 4;
	bmp->alignment = malloc(bmp->alignment_size);   
	for (int i = 0; i < bmp->alignment_size; i++)
		bmp->alignment[i] = 0;
    return 0;
}

int load_bmp(const char* filename, bmpheader_t* header, bmp_t* bmp) {
//Open file
    FILE* input;
    input = fopen(filename, "rb");
    if (!input) {
        printf("Failed to open input file\n");
        return 1;
    }
//Read header && init BMP  
    fread(header, sizeof(char), 54, input); 
    init_bmp(bmp, header->biWidth, header->biHeight);
//Read pixels
    for (int i = 1; i <= bmp->height; i++) {
        fread(bmp->pixels[bmp->height - i], sizeof(pixel_t), bmp->width, input);
    	fread(bmp->alignment, 1, bmp->alignment_size, input);
    }      
//Close file    
    fclose(input);  
    return 0;  
}

int save_bmp(const char* filename, const bmpheader_t* const header, const bmp_t* bmp){
//Open file
    FILE* output;
    output = fopen(filename, "wb");
//Write BMP
    fwrite(header, sizeof(char), 54, output);
    for (int i = 1; i <= bmp->height; i++) {
        fwrite(bmp->pixels[bmp->height - i], sizeof(pixel_t), bmp->width, output);
    	fwrite(bmp->alignment, 1, bmp->alignment_size, output);
    }
//Close file
    fclose(output);  
    return 0;  
}

void free_bmp(bmp_t* bmp) {
    for (int i = 0; i < bmp->height; i++)
        free(bmp->pixels[i]);
    free(bmp->pixels);
 	free(bmp->alignment);
    free(bmp);
}
    
