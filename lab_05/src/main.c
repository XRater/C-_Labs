#include "../include/position.h"
#include "stdio.h"
#include "string.h"

void apply(intrusive_list* list, void(*op)(intrusive_node*, void*), void* arg){
    intrusive_node *head = &list->head;
    intrusive_node *node = head->next;

    for (; node != head; node = node->next) 
        op(node, arg);      
}

void print(intrusive_node* node, void* format){
    position_node *pnode = get_position(node);
    printf(format, pnode->x, pnode->y);        
}

void count(intrusive_node* node, void* cnt){
    *((int*)cnt) += 1;       
}

void savetext(intrusive_list *list, FILE* output) {
    intrusive_node *head = &list->head;
    intrusive_node *node = head->next;

    for (; node != head; node = node->next) {
        position_node *pnode = get_position(node);
        fprintf(output, "%d %d\n", pnode->x, pnode->y);
    }
}

void savebin(intrusive_list *list, FILE* output) {
    intrusive_node *head = &list->head;
    intrusive_node *node = head->next;

    for (; node != head; node = node->next) {
        position_node *pnode = get_position(node);
        fwrite(&(pnode->x), sizeof(char)*3, 1, output);
        fwrite(&(pnode->y), sizeof(char)*3, 1, output);
    }
}

int main(int argc, char* argv[]) {
    intrusive_list list;
    intrusive_list* l = &list;
    init_list(l);    
    if (strcmp(argv[1], "loadtext") == 0){
        FILE* input;
        input = fopen(argv[2], "r");
        int first, second;
        while (fscanf(input, "%d%d", &first, &second) == 2)
            add_position(l, first, second);   
        fclose(input);
    }    
    if (strcmp(argv[1], "loadbin") == 0){
        FILE* input;
        input = fopen(argv[2], "rb");
        int first = 0, second = 0;
        while(fread(&first, sizeof(char)*3, 1, input) == 1){
            fread(&second, sizeof(char)*3, 1, input);
            add_position(l, first, second);    
        }
        fclose(input);
    }    
    if (strcmp(argv[3], "savetext") == 0){
        FILE* output;
        output = fopen(argv[4], "w");
        savetext(l, output);
        fclose(output);
    }
    if (strcmp(argv[3], "savebin") == 0){
        FILE* output;
        output = fopen(argv[4], "wb");
        savebin(l, output);
        fclose(output);
    }
    if (strcmp(argv[3], "print") == 0){
        char* format = argv[4];
        apply(l, print, format);
        printf("\n");
    }
    if (strcmp(argv[3], "count") == 0){
        int cnt = 0;
        apply(l, count, &cnt);  
        printf("%d\n", cnt);
    }
    remove_all(l);
    return 0;
}
