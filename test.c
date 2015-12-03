/*
** COMP20007 Design of Algorithms
** Semester 1 2015
** Assignment 2 driver
** 
** William Pan 694945
*/

#include <stdio.h>
#include <graph.h>
#include "dijkstra.h"
#include "heap.h"

int main(int argc, char const *argv[])
{
	int num_houses, num_schools, v, u, data;
	scanf("%d",&num_houses);
	scanf("%d",&num_schools);

	*g = graph_new(num_houses+num_schools);

	while(scanf("%d %d %d", &v, &u, &data)>0){
		graph_add_edge(g, v, u, (void*)data);
		printf("%d %d %d\n", v,u,data);
	}

	for(int count = num_houses; count < num_schools; count ++){
		dijkstra(g,num_houses)
	}
	return 0;
}