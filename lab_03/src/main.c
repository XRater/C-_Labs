#include "stdlib.h"
#include "../include/clist.h"
#include "stddef.h"
#include "stdio.h"

#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))

struct position_node{
	int x, y;
	struct intrusive_node node;
};

void add_position(struct intrusive_list* l, int x, int y){	
	struct position_node* pos = malloc(sizeof(struct position_node));
	pos->x = x;
	pos->y = y;
	add_node(l, &pos->node);
}; 

void remove_position(struct intrusive_list* l, int x, int y){
	struct intrusive_node* node = l->head.next;
	while (node != &l->head){
		struct position_node* ptr = container_of(node, struct position_node, node);
		node = node->next;	
		if ((ptr->x == x) && (ptr->y == y))
		{
			remove_node(l, node->prev);	
			free(ptr);
		}
	}
}
void show_all_positions(struct intrusive_list* l){
	struct intrusive_node* node = l->head.next;
	while (node != &l->head){
		struct position_node* ptr = container_of(node, struct position_node, node);
		printf("(%d, %d) ", ptr->x, ptr->y);	
		node = node->next;
	}
	printf("\n");                                   
}

void remove_all(struct intrusive_list* l){
	struct intrusive_node* node = l->head.next;
	while (node != &l->head){
		struct position_node* ptr = container_of(node, struct position_node, node);
		remove_node(l, node);	
		free(ptr);
		node = l->head.next;
	}
}

int main(){	 
	struct intrusive_list l;
	init_list(&l);
	add_position(&l, 10, 10);
	add_position(&l, 10, 10);
	add_position(&l, 20, 10);
	show_all_positions(&l);
	remove_position(&l, 10 ,10);
	add_position(&l, 10, 20);
	show_all_positions(&l);
	remove_all(&l);
	return 0;
}