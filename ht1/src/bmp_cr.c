#include <stdio.h>
#include <stdlib.h>
#include <bmp_cr.h>

void make_encrypt_key(encrypt_key_t* key, int x, int y, char c) {
    key->x = x;
    key->y = y;
    key->comp = c;
}

int insert(const char* keyfile, const char* textfile, bmp_t* bmp) {
    FILE* key_input;
    FILE* text_input;
    key_input = fopen(keyfile, "r");
    text_input = fopen(textfile, "r");
//Check Input files
    if (!key_input){
        printf("Cant open key file");
        return 1;
    }
    if (!text_input){
        printf("Cant open message file");
        return 1;
    }
//Encrypt data
    encrypt_key_t* key = malloc(sizeof(encrypt_key_t)*5);
    int x, y;
    char c, symbol;
    while (fscanf(text_input, "%c", &symbol) != EOF && symbol != 10) {
        for (int i = 0; i < 5; i++){
            fscanf(key_input, "%d%d%c", &x, &y, &c);
            make_encrypt_key(key + i, x, y, c);
        }
        encrypt(symbol, key, bmp);
    }
//Close files
    free(key);
    fclose(key_input);
    fclose(text_input);
    return 0;
}

char normalize(char symbol) {
    if (symbol >= 'a' && symbol <= 'z')
        return symbol - 'a';
    if (symbol == ' ')
        return 26;
    if (symbol >= '.')
        return 27;
    if (symbol >= ',')
        return 28;
    return 0;
}

void changebit(char* a, char* b) {
    *a -= (*a) & 1;
    *a += *b;
}

void encrypt_symbol(encrypt_key_t* key, bmp_t* bmp, char c) {
    if (key->comp == 'R')
        changebit(&(bmp->pixels[key->x][key->y].r), &c);    
    if (key->comp == 'G')
        changebit(&(bmp->pixels[key->x][key->y].g), &c);
    if (key->comp == 'B')
        changebit(&(bmp->pixels[key->x][key->y].b), &c);
}

int encrypt(char symbol, encrypt_key_t* key, bmp_t* bmp) {
    symbol = normalize(symbol);
    for (int i = 0; i < 5; i++){
        encrypt_symbol(key, bmp, symbol & 1);
        symbol = symbol >> 1;
    }
    return 0;
}

    
