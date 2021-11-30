#include "caixeiro.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define MX_SIZE 11
struct GRAPH
{
    vertex* adjacent_cities[MX_SIZE];
};
struct VERTEX
{
    int dist[MX_SIZE];
};
graph* create_graph()
{
    graph *new_graph = (graph*) malloc(sizeof(graph));
    for(int i=0;i<MX_SIZE ;i++)
    {
        new_graph->adjacent_cities[i] = (vertex*)malloc(sizeof(vertex));
    }
    for(int i=1;i<MX_SIZE;i++)
    {
        for(int j=1;j<MX_SIZE;j++)
        {
            new_graph->adjacent_cities[i]->dist[j]=0;
        }
    }
    return new_graph;   
}
int is_valid(int *state, graph *vertices){

    for(int i=1;i<MX_SIZE;i++)
    {
        int source = state[i];
        int dest = state[i+1];
        if(vertices->adjacent_cities[source]->dist[dest]==54) return 0;
    }
    return 1;
}
void add_vertex(graph *vertices, int source, int destination, int dist){
    vertices->adjacent_cities[source]->dist[destination] = dist;
    vertices->adjacent_cities[destination]->dist[source] = dist;
}
void print_graph(graph *g){
    for(int i=1;i<MX_SIZE;i++)
    {
        printf("%d| ",i);
        for(int j=1;j<MX_SIZE;j++)
        {
            printf(" %d(%d)|", j, g->adjacent_cities[i]->dist[j]);
        }
        printf("\n");
    }
}
int is_done(int *v){
    for(int i=1;i<MX_SIZE-1;i++)
    {
        if(v[i]==v[i+1]) return 0;
    }
    return 1;
}
void print_path(int *v){
    for(int i=1; i<=MX_SIZE; i++){
        if(i==1) printf("C%d ", v[i]);
        else printf("-> C%d ", v[i]);
    }
    printf("\n");
}
void generate_new_path(int *aux, int ori){
    aux[1]=aux[MX_SIZE]=ori;
    int generated[MX_SIZE]={0};
    generated[ori]=1;
    for(int i=2;i<MX_SIZE;i++)
    {
        while(!aux[i]){
            int rand_n = rand() % 10 + 1;
            if(generated[rand_n]) continue;
            else{
                aux[i] = rand_n;
                generated[rand_n]=1;
            }
            break;
        }
    }  
}

int total_traveled_distance(int *v, graph *g){
    // 5, 9, 6, 7, 10, 2, 1, 8, 4, 3, 5
    int total_dist=0;
    for(int i=1;i<MX_SIZE;i++)
    {
        int source = v[i];
        int dest = v[i+1];
        total_dist += g->adjacent_cities[source]->dist[dest];
    }
    return total_dist;
}
void swap(int *v, int i, int j){
    int aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}
void optimize_solution_operator(int *aux){
    int i = (rand()%9)+2;
    int j = (rand()%9)+2;
    swap(aux,i,j);
}
void copy(int *a, int *b){
    for(int i=1;i<=MX_SIZE;i++)
    {
        b[i]=a[i];
    }
}
// 1                       11