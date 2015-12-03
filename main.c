/*
** COMP20007 Design of Algorithms
** Semester 1 2015
** Assignment 2 driver
** 
** William Pan 694945
*/

#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "set.h"
#include "cover.h"
#include "graph.h"
#include "dijkstra.h"

int main(int argc, char const *argv[])
{
	Set *x = CreateSet();
	Heap *h = CreateHeap(0);
	int num_houses, num_schools, v, u, data;

	scanf("%d",&num_houses);
	scanf("%d",&num_schools);

	Cover *c = CreateCover(num_houses+num_schools,num_houses);
	Set **total_sets = (Set**)malloc(sizeof(Set*)*num_schools+1);
	Graph *g = graph_new(num_houses+num_schools);

	while(scanf("%d %d %d", &v, &u, &data)>0){
		graph_add_edge(g, v, u, (void*)data);
		graph_add_edge(g, u, v, (void*)data);
	}

	for(int count = num_houses; count < num_schools+num_houses; count ++){
		Set *s = dijkstra(g,count);
		HeapInsert(h,count-num_houses,s->n);
		total_sets[count-num_houses] = s;
		CoverInsertSet(c,s,num_houses);
	}
	free(g);
	while(x->n != num_houses){
		data = HeapRemoveMin(h);
		printf("%d\n",data);
		SetAddUnique(total_sets[data],x,c);
		HeapCoverUpdateVal(c,h,total_sets[data],num_houses);
		//printf("%d,%d\n",x->n,num_houses);
	}
	return 0;
}