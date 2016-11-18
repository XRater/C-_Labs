#include <bmp.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv){
    if (argc < 2){
        printf("Wrong input format\n");
        return 1;
    }
//Initialization
    size_t error;
    char* command = argv[1];
    char* input = argv[2];
    bmpheader_t* header = malloc(sizeof(bmpheader_t));
    bmp_t* bmp = malloc(sizeof(bmp_t));
//Open BMP    
    error = load_bmp(input, header, bmp);
    if (error) return 1;
//Get command
    if (strcmp(command, "crop-rotate") == 0){
        if (argc != 8){
            printf("Wrong input format\n");
            return 1;
        }
        //Get parametrs
        char* output = argv[3];
        int x = atoi(argv[4]), y = atoi(argv[5]), w = atoi(argv[6]), h = atoi(argv[7]);  
        bmp_t* resbmp = malloc(sizeof(bmp_t));
        error = init_bmp(resbmp, h, w);
        if (error) return 1;
        error = crop_rotate_bmp(header, bmp, resbmp, x, y, w, h);
        if (error) return 1;
        //Save BMP
        error = save_bmp(output, header, resbmp);
        if (error) return 1;
        free_bmp(resbmp);
    }
    else if (strcmp(command, "insert") == 0){
        if (argc != 6){
            printf("Wrong input format\n");
            return 1;
        }
        char *keyfile = argv[4], *textfile = argv[5], *output = argv[3];
       // printf("%s", keyfile);
        error = insert(keyfile, textfile, bmp);
        if (error) return 1;
        error = save_bmp(output, header, bmp);
        if (error) return 1;
    }
    else{
        printf("Unknown command\n");
        return 1;
    }
//Free memory
    free_bmp(bmp);
    free(header);
    return 0;
}
