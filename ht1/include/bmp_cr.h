#include <bmp_struct.h>

#pragma once
typedef struct encrypt_key {
    int x;
    int y;
    char comp;
} encrypt_key_t;

void changebit(char* a, char* b);
int encrypt(char symbol, encrypt_key_t* key, bmp_t* bmp);
int insert(const char* keyfile, const char* textfile, bmp_t* bmp);
void make_encrypt_key(encrypt_key_t* key, int x, int y, char c);
