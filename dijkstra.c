#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <limits.h>
#include "set.h"
#include "graph.h"
#include "heap.h"

Set *dijkstra(Graph *g, Label source){
	Set *s = CreateSet();
	assert(s);
	Heap *h = CreateHeap(1);
	assert(h);
	int v=0,u=0,count=0;
	int *dist = (int*)malloc(sizeof(int)*g->number_of_vertices+1);
	assert(dist);
	for (int i=0; i<g->number_of_vertices; i++){
		if (i==source){
			dist[source] = 0;
			HeapInsert(h, source, 0);
			i++;
		}
		dist[i] = INT_MAX;
		HeapInsert(h, i, INT_MAX);
	}
	while(h->n > 0 && HeapPeekKey(h) <= 1000){
		u = HeapRemoveMin(h);
		SetInsert(s,u,source);
		for (count=0; count < g->vertices[u].num_edges; count++){
			v = g->vertices[u].edges[count].u;
			if (dist[u] + (int)g->vertices[u].edges[count].data < dist[v]){
				dist[v] = dist[u] + (int)g->vertices[u].edges[count].data;
				HeapChangeKeyValue(h, v, dist[v]); 
			}
		}
	}
	HeapDestroyHeap(h);
	free(dist);
	return s;
}