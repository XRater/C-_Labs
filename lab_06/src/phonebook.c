#include <stdio.h>
#include "stdlib.h"
#include <string.h>
#include "../include/names.h"
#include "time.h"

typedef struct human_s {
    char name[256];
    char middle_name[256];
    char family_name[256];
    char phones[10][21];
    size_t phone_number;
} human_t;

typedef struct phonebook_s {
    human_t *humans;
    size_t size;
    size_t capacity;
} phonebook_t;

void init_phonebook(phonebook_t *book){
    book->humans = malloc(sizeof(human_t));
    book->size = 0;
    book->capacity = 1;
}

void clear_phonebook(phonebook_t *book){
    free(book->humans);
    free(book); 
}

void print_phonebook(phonebook_t *book){
    printf("%d\n", (int)book->size);
    int i;
    for (i = 0; i < book->size; i++){
        printf("name: %s\n", (book->humans[i]).name);
        printf("middle name: %s\n", (book->humans[i]).middle_name);
        printf("family name: %s\n", (book->humans[i]).family_name);
        for (int j = 0; j < book->humans[i].phone_number; j++)
            printf("phone: %s\n", (book->humans[i]).phones[j]);
        printf("\n");
    }
}

void push_back_human(phonebook_t *book, human_t *human){
    if (book->size < book->capacity)
        book->humans[book->size] = *human;
    else{
        book->capacity *= 2;
        book->humans = realloc(book->humans, book->capacity*sizeof(human_t));
        book->humans[book->size] = *human; 
    }
    (book->size)++;
}


void push_random_human(phonebook_t *book){
    human_t human;
    strcpy(human.name, kNames[rand()%NAMES_CNT]);       
    strcpy(human.middle_name, kMiddleNames[rand()%MIDDLE_NAMES_CNT]);       
    strcpy(human.family_name, kFamilyNames[rand()%FAMILY_NAMES_CNT]);       
    human.phone_number = rand()%11;
    int i;
    for (i = 0; i < human.phone_number; i++){
        int l = rand()%20 + 1;
        int j;
        char* tmp = malloc(l + 1);
        for (j = 0; j < l; j++){
            char digit = rand()%10 + 48;
            tmp[j] = digit;
        }
        tmp[l] = '\0';
        strcpy(human.phones[i], tmp);
        free(tmp);
    }
    push_back_human(book, &human);
}

void gen_phonebook(phonebook_t *book, size_t size){
    free(book->humans);
    init_phonebook(book);
    int i;
    srand(time(NULL));
    for (i = 0; i < size; i++)
        push_random_human(book);
}

int save_phonebook_xml(const char* filename, phonebook_t* book){
    FILE *fp;
    fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Failed to open file\n");
        return 1;
    }
    fprintf(fp, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<phonebook>\n");
    int i; 
    for (i = 0; i < book->size; i++){
        fprintf(fp, "    <human name=\"%s %s %s\">\n", book->humans[i].name, book->humans[i].middle_name, book->humans[i].family_name);
        int j;
        for (j = 0; j < book->humans[i].phone_number; j++){
            fprintf(fp, "        <phone>%s</phone>\n", book->humans[i].phones[j]);
        }
        fprintf(fp, "    </human>\n");
    }
    fprintf(fp, "</phonebook>\n");
    fclose(fp);    
    return 0;
}

