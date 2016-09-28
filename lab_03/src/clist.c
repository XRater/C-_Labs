#include "stdlib.h"
#include "stdio.h"
 
struct intrusive_node{
	struct intrusive_node* next;	
	struct intrusive_node* prev;	 
};

struct intrusive_list{
	struct intrusive_node head;
};

void init_list(struct intrusive_list* l){
	struct intrusive_node head_node;
	l->head	= head_node;
	l->head.next = &l->head;
	l->head.prev = &l->head;
}

void add_node(struct intrusive_list* l, struct intrusive_node* node){
	node->next = l->head.next;
	node->prev = &l->head;
	l->head.next->prev = node;
	l->head.next = node;
}
                  
void remove_node(struct intrusive_list* l, struct intrusive_node* node){
	node->next->prev = node->prev;
	node->prev->next = node->next;	
}
                  
int get_length(struct intrusive_list* l){
    int k = 0;
	struct intrusive_node* node = l->head.next;
	while (node != &l->head){
			k++;
			node = node->next;
	}
	return k;
}                                   
