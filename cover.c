/*
** COMP20007 Design of Algorithms
** Semester 1 2015
** Assignment 2 driver
** 
** William Pan 694945
*/

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "set.h"
#include "heap.h"
#include "cover.h"

Cover *CreateCover(int number_of_vertices, int num_houses){
	Cover *c = (Cover*)malloc(sizeof(Cover));
	assert(c);
	c->houses = (Houses*)malloc(sizeof(Houses)*number_of_vertices+1);
	assert(c->houses);
	c->add_values = (int*)malloc(sizeof(int)*number_of_vertices+1);
	assert(c->add_values);
	c->n = number_of_vertices;

	for(int count=0; count<number_of_vertices; count++){
		if (count < num_houses) c->add_values[count] = 1;
		else c->add_values[count] = 0;
		c->houses[count].sets = (Set**)malloc(sizeof(Set*));
		c->houses[count].size = 1;
		c->houses[count].n = 0;
	}

    return c;
}

void CoverInsertSet(Cover *c, Set *s, int num_houses){
	for (int count=0; count<s->n; count++){
		if (c->houses[s->houses[count]].n == c->houses[s->houses[count]].size){
			c->houses[s->houses[count]].size *= 2;
			c->houses[s->houses[count]].sets = (Set**)realloc(c->houses[s->houses[count]].sets,sizeof(Set*)*(c->houses[s->houses[count]].size+1));
			assert(c->houses[s->houses[count]].sets);
		}
		if (s->houses[count] < num_houses){
			//printf("%d\n",s->houses[count] );
			c->houses[s->houses[count]].sets[c->houses[s->houses[count]].n] = s;
			c->houses[s->houses[count]].n ++;
		}
	}
}

void SetAddUnique(Set *s, Set *u, Cover *c){
	int count=0;
    for (count; count<s->n_2; count++){
    	//printf("%d\n",c->add_values[s->houses[count]]);
        if(c->add_values[s->houses[count]] == 1){
            SetInsert(u,s->houses[count],-1);
            c->add_values[s->houses[count]] = 0;
        }
    }
}

void HeapCoverUpdateVal(Cover *c, Heap *h, Set *s,int num_houses){
	int count=0, count2=0, temp = s->n;
	Houses node;
	for (count=0; count<temp; count++){
		if (s->houses[count] < num_houses && c->add_values[s->houses[count]]==0){
			c->add_values[s->houses[count]] = -1;
			node = c->houses[s->houses[count]];
			//printf("%d\n",node.n);
			for (count2=0; count2<node.n;count2++){
				node.sets[count2]->n--;
				HeapChangeKeyDelta(h, node.sets[count2]->set_number-num_houses,-1);
				//printf("w=%d,%d\n",node.sets[count2]->set_number-num_houses,h->H[h->map[node.sets[count2]->set_number-num_houses]].key);
			}
		}
	}
}