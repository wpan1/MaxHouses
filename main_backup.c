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
	Set *s = CreateSet();
	Set *x = CreateSet();
	Set **sets = (Set**)malloc(sizeof(Set));
	Heap *h = CreateHeap(0);
	int num_houses, num_schools, v, u, data;

	scanf("%d",&num_houses);
	scanf("%d",&num_schools);

	Cover *c = CreateCover(num_houses+num_schools);
	Graph *g = graph_new(num_houses+num_schools);

	while(scanf("%d %d %d", &v, &u, &data)>0){
		graph_add_edge(g, v, u, (void*)data);
		//graph_add_edge(g, u, v, (void*)data);
		printf("%d %d %d\n", v,u,data);
		//printf("%d %d %d\n", u,v,data);
	}

	for(int count = num_houses; count < num_schools+num_houses; count ++){
		s = dijkstra(g,count);
		printf("school = %d\n",count-num_houses);
		for(int count2 = 0; count2<s->n; count2++){
			printf("%d ",SetPeekKey_val(s,count2));
		}
		printf("\n");
		HeapInsert(h,count-num_houses,s->n);
		sets[count-num_houses] = s;
		CoverInsertSet(c,s);
	}


	while(x->n != num_schools+num_houses){
		data = HeapRemoveMin(h);
		SetAddUnique(sets[data],x,c);
		HeapCoverUpdateVal(c,sets[data]);
		printf("%d\n",data);
	}

	return 0;
}