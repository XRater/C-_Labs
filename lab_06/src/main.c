#include <expat.h>
#include <stdio.h>
#include <string.h>
#include "../include/phonebook.h"

#define BUFFER_SIZE 100000

void str_parse(char* dest, const char* source, size_t length){
    int i;
    for (i = 0; i < length; i++){
        if (*source != ' ' && *source != '\t' && *source != 10)
            *dest++ = *source;
        source++;        
    }
    *dest = '\0';
}

typedef struct data {
    size_t human_number;
    size_t phone_number;
    size_t phone;
    phonebook_t* book;
} data_t;

void start_element(void* data_void, const char *element, const char **attribute) {
    data_t* data = (data_t*) data_void;    
    int i = 0;
    if (strcmp(element, "human") == 0){
        human_t human;
        human.phone_number = 0;
        (data->human_number)++;
        char* tmp = malloc(1000);
        strcpy(tmp, attribute[1]);
        strcpy(human.name, strtok(tmp, " "));
        strcpy(human.middle_name, strtok(NULL, " "));
        strcpy(human.family_name, strtok(NULL, " "));
        push_back_human(data->book, &human);
        free(tmp);
    }
    if (strcmp(element, "phone") == 0){
        strcpy(data->book->humans[data->human_number].phones[data->phone_number], "");     
        data->phone = 1;
    }
}

void end_element(void *data_void, const char *element) {
    data_t* data = (data_t*) data_void;    
    if (strcmp(element, "human") == 0)    
        data->phone_number = 0;
    if (strcmp(element, "phone") == 0){    
        data->phone = 0;
        data->book->humans[data->human_number].phone_number++;
        data->phone_number++;
    }
}

void handle_data(void *data_void, const char *content, int length) {
    char* phone = malloc(length + 1);
    str_parse(phone, content, length);
    data_t* data = (data_t*) data_void;        
    if (strlen(phone)&&data->phone)
        strcat(data->book->humans[data->human_number].phones[data->phone_number], phone); 
    free(phone);     
}

int parse_xml(const char* filename, phonebook_t* book, char *buff, size_t buff_size) {
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Failed to open file\n");
        return 1;
    }

    data_t data;
    data.book = book;
    data.human_number = -1;
    data.phone_number = 0;
    data.phone = 0;
    XML_Parser  parser = XML_ParserCreate(NULL);
    XML_SetElementHandler(parser, start_element, end_element);
    XML_SetCharacterDataHandler(parser, handle_data);
    XML_SetUserData(parser, &data);

    memset(buff, 0, buff_size);

    size_t len = 0;
    int done = 0;
    do {
        len = fread(buff, sizeof(char), buff_size, fp);
        done = len < buff_size;
        if (XML_Parse(parser, buff, len, done) == XML_STATUS_ERROR) {
            printf("Error: %s\n", XML_ErrorString(XML_GetErrorCode(parser)));
            return 2;
        }
    } while (!done);

    XML_ParserFree(parser);
    fclose(fp);

    return 0;
}

int comp(const void* a, const void* b){
    return(strcmp(((human_t*) a)->family_name, ((human_t*) b)->family_name));
}

int load_phonebook_xml(const char* filename, phonebook_t* book){
    char buffer[BUFFER_SIZE];
    parse_xml(filename, book, buffer, BUFFER_SIZE);    
    qsort(book->humans, book->size, sizeof(human_t), comp);
}

int main(int argc, char **argv) {
    phonebook_t* book = malloc(sizeof(phonebook_t));
    init_phonebook(book);
    load_phonebook_xml(argv[1], book);
    print_phonebook(book);
    gen_phonebook(book, 5);
    save_phonebook_xml(argv[2], book);
    clear_phonebook(book);
    return 0;
}   
