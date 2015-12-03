/*
** Graph data type
** Uses an adjacency list representation (arrays for lists).
** Written for workshop 3 of COMP20007
**
** Andrew Turpin
** Tue 17 Mar 2015 19:13:47 AEDT
*/

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

/*
** Create graph with number_of_vertices vertices
*/
Graph *
graph_new(int number_of_vertices) {
    assert(number_of_vertices > 0);

    Graph *g = NULL;

    // malloc space for g
    g = (Graph*)malloc(sizeof(Graph));
    assert(g);

    // malloc space for number_of_vertices vertices
    g->vertices = (Vertex*)malloc(sizeof(Vertex)*number_of_vertices);
    assert(g->vertices);

    // Set values for Graph *g
    g->number_of_vertices = number_of_vertices;

    for(int count=0;count<number_of_vertices;count++){
        g->vertices[count].num_edges=0;
        g->vertices[count].max_num_edges=1;
        g->vertices[count].edges = (Edge*)malloc(sizeof(Edge));
        assert(g->vertices[count].edges);
    }
    return(g);
}

/*
** Add edge to g. 
*/
void  
graph_add_edge(Graph *g, Label v, Label u, void *data) {
    assert(g);
    assert(v >= 0 && v < g->number_of_vertices);
    assert(u >= 0 && u < g->number_of_vertices);

    // Make room in g->vertices[v].edges if no room.
    if (g->vertices[v].num_edges == g->vertices[v].max_num_edges){
        g->vertices[v].max_num_edges *= 2;
        g->vertices[v].edges = (Edge*)realloc(g->vertices[v].edges,sizeof(Edge)*g->vertices[v].max_num_edges);
    }

    int num_edges = g->vertices[v].num_edges;
    // add u and data to g->vertices[v].edges array
    g->vertices[v].edges[num_edges].data = data;
    g->vertices[v].edges[num_edges].u = u;
    // increment g->vertices[v].num_edges
    g->vertices[v].num_edges ++;
    return;
}

/*
** Delete edge from g. Only deletes one copy if there are multiple.
** Does nothing if u is not in v's list.
*/
void  
graph_del_edge(Graph *g, Label v, Label u) {
    assert(g);
    assert(v >= 0 && v < g->number_of_vertices);
    assert(u >= 0 && u < g->number_of_vertices);

    //Find edge
    int count=0;
    for(count;count<g->vertices[v].num_edges-1;count++){
        if(g->vertices[v].edges[count].u == u){
            break;
        }
    }

    int count2 = count+1;
    for(count2;count2<g->vertices[v].num_edges-1;count2++){
        g->vertices[v].edges[count].u = g->vertices[v].edges[count2].u;
        g->vertices[v].edges[count].data = g->vertices[v].edges[count2].data;
        count++;
    }
    free(&g->vertices[v].edges[count].u);
    free(g->vertices[v].edges[count].data);
    free(&g->vertices[v].edges[count]);
    g->vertices[v].num_edges --;

    return;
}

/*
** Return pointer to start of edge array for vertex v
** Set n to the number of items in the edge array.
*/
Edge *
graph_get_edge_array(Graph *g, Label v, int *num_edges) {
    assert(g);
    assert(v >= 0 && v < g->number_of_vertices);

    *num_edges = g->vertices[v].num_edges;

    return g->vertices[v].edges;
}

/*
** Return 1 if (v,u) is in g
*/
int
graph_has_edge(Graph *g, Label v, Label u) {
    assert(g);
    assert(v >= 0 && v < g->number_of_vertices);
    assert(u >= 0 && u < g->number_of_vertices);
    
    //Find edge
    for(int count=0;count<g->vertices[v].num_edges-1;count++){
        if(g->vertices[v].edges[count].u == u){
            return 1;
        }
    }

    return 0;
}


/*
** Set vertex's data to data
*/
void  
graph_set_vertex_data(Graph *g, Label v, void *data) {
    assert(g);
    assert(v >= 0 && v < g->number_of_vertices);
    
    g->vertices[v].data = data;
}


/*
** Simple explore for calling from dfs that doesn't actually do anything.
** Use as a template for writing your own explore() functions.
** ASSUMES vertex->data is 1 or 0 for visited and unvisted 
*/
void 
graph_default_explore(Graph *g, Label v) {
    if (g->vertices[v].data)
        return;

    g->vertices[v].data = (void *)1; // mark as visited

    for(int i = 0 ; i < g->vertices[v].num_edges ; i++)
        graph_default_explore(g, g->vertices[v].edges[i].u);
}

/*
** Perform DFS beginning at v, calling pre() and post() as appropriate.
** ASSUMES vertex->data is 1 or 0 for visited and unvisted 
*/
void 
graph_dfs(Graph *g, Label v, void (explore)(Graph *g, Label v)) {
    assert(g);
    assert(explore);
    assert(v >= 0 && v < g->number_of_vertices);

    // First explore from v
    explore(g, v);

    // Now do the rest (if any)
    for(int i = 0; i < g->number_of_vertices ; i++)
        explore(g, i);
}
