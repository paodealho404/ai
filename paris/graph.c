#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
#include "graph.h"
#define MX_SIZE 15
struct GRAPH
{
    vertex *vertices[MX_SIZE];
    float distance_to_station[MX_SIZE][MX_SIZE];
};
struct VERTEX
{
    int station;
    char line;
    vertex *next;
};
graph* create_graph()
{
    graph *new_graph = (graph*) malloc(sizeof(graph));
    for(int x=0; x < MX_SIZE ; x++)
    {
        new_graph->vertices[x] = NULL;
    }
    for(int i=0;i<MX_SIZE;i++)
    {
        for(int j=0;j<MX_SIZE;j++)
        {
            new_graph->distance_to_station[i][j] = 0;
        }
    }
    return new_graph;   
}
vertex* create_vertex(int station, char line)
{
    vertex *new_vertex = (vertex*)malloc(sizeof(vertex));
    new_vertex->station = station;
    new_vertex->line = line;
    new_vertex->next = NULL;
    return new_vertex;
}
void add_undirected_edge(graph *graph, char line, int source, int destination, float dist)
{
    if(line!='.'){
    //Origin to Destination
        vertex* new_vertex = create_vertex(destination,line);
        new_vertex->next = graph->vertices[source];
        graph->vertices[source] = new_vertex;
        //Destination to Origin
        new_vertex = create_vertex(source, line);
        new_vertex->next = graph->vertices[destination];
        graph->vertices[destination] = new_vertex;    
    }
    graph->distance_to_station[source][destination] = dist;
    graph->distance_to_station[destination][source] = dist;
}
void print_distances_between_cities(graph *paris){  
    printf("    E1 E2 E4 E4 E5 E6 E7 E8 E9 E10 E11 E12 E13 E14\n");
    for(int i=1;i<MX_SIZE;i++)
    {
        printf("E%d ",i);
        for(int j=1;j<MX_SIZE;j++)
        {
            printf(" %.1f ", paris->distance_to_station[i][j]);
        }
        printf("\n");
    }
}
void print_lines_between_cities(graph *paris){
    printf("\n\n");
    for(int i=1;i<MX_SIZE;i++)
    {
        vertex *aux = paris->vertices[i];
        while(aux!=NULL){
            printf("Rota E%d->E%d: Linha: %c\n", i, aux->station, aux->line);
            aux = aux->next;
        }
        printf("\n");
    }
}
float calculate_cost_to_station(graph *paris, int s, int d){
    return paris->distance_to_station[s][d];
}
float calculate_heuristics(graph *paris, int s, int d){
    return paris->distance_to_station[s][d];
}
vertex* get_vertex(graph *paris, int i){
    return paris->vertices[i];
}
vertex* get_sucessor_vertex(graph *paris, int i){
    return paris->vertices[i]->next;
}
int get_station(vertex *v){
    return v->station;
}
void iterate_and_enqueue(graph *paris, pqueue *pq, state *source, int destination){
    vertex *vert = get_vertex(paris, get_station_number(source));
    while(vert){
        state* new_state = create_state(paris, source, vert->station, vert->line);
        enqueue(paris, pq, new_state, destination);
        vert = vert->next;
    }
}
char get_line(graph *paris, int prev_station, int next_station){
    vertex *aux = get_vertex(paris, prev_station);
    while((aux->next!=NULL)&&(aux->station!=next_station)){
        aux = aux->next;
    }
    if(aux->station==next_station) return aux->line;
    else return '.';
}


