/*
** COMP20007 Design of Algorithms
** Semester 1 2015
** Assignment 2 driver
** 
** William Pan 694945
*/

#include <stdio.h>
#include <stdlib.h>
#include "set.h"
#include "heap.h"
#include "cover.h"

Cover *CreateCover(int number_of_vertices){
	Cover *c = (Cover*)malloc(sizeof(Cover));
	c->houses = (Set**)malloc(sizeof(Set)*number_of_vertices);
	c->houses_size = (int*)malloc(sizeof(int)*number_of_vertices);
	c->add_values = (int*)malloc(sizeof(int)*number_of_vertices);
	c->n = number_of_vertices;

	for(int count=0; count<number_of_vertices; count++){
		c->add_values[count] = 1;
		c->houses_size[count] = 0;
	}

    return c;
}

void CoverInsertSet(Cover *c, Set *s){
	for (int count=0; count<s->n; count++){
		c->houses[s->houses[count]] = s;
	}
}

void SetAddUnique(Set *s, Set *u, Cover *c){
	int count=1;
    for (count; count<s->n; count++){
        if(c->add_values[s->houses[count]] == 1){
            SetInsert(u,s->houses[count]);
            c->houses_size[count] ++;
            c->add_values[s->houses[count]] = 0;
        }
    }
}

void HeapCoverUpdateVal(Cover *c, Set *s){
	int count=0, count2=0;
	for (count; count<s->n; count++){
		for (count2; count2<c->houses_size[count]; count2++){
			c->houses[count2]->n --;
		}
	}
}