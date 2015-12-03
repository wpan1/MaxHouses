#include <stdio.h>
#include <stdlib.h>
#include "set.h"

node_t LLCreate(){
	node_t * head = NULL;
	head = malloc(sizeof(node_t));
	head->set = (set*)malloc(sizeof(set));

	head->next = NULL;
	return head;
}


node_t LLpush(node_t *head, Set *set) {
	node_t * new_node;
    new_node = LLCreate();

    new_node->set = set;
    new_node->next = *head;
    
    return new_node;
}