#include<stdio.h>
#include "graph.h"
#include "queue.h"
#include <string.h>
#include <locale.h>
#define dbg if(0)
int main(){
    graph *paris = create_graph();
    pqueue *fr = create_queue();
    int source, destination;
    char line;
    float dist;
    FILE *file = fopen("input.txt", "r");
    if(!file) printf("Erro abrindo arquivo de entrada");
    else {
        while(fscanf(file, "%d %d %c %f", &source, &destination, &line, &dist)!=EOF)
            add_undirected_edge(paris, line, source, destination, dist);
    
        dbg print_distances_between_cities(paris);
        dbg print_lines_between_cities(paris);
    }
    printf("Insira uma estacao de origem (ex.: E1, E2, ..., E14): ");
    scanf("%c%d",&line, &source);
    state *o = create_state(paris, NULL, source, ' ');
    printf("\nInsira uma estacao de destino (ex.: E1, E2, ..., E14): ");
    getchar();
    scanf("%c%d",&line, &destination);
    enqueue(paris, fr, o, destination);
    state* predecessor = dequeue(fr);
    while(!is_final(predecessor, destination)){
        generate_new_states(paris, fr, predecessor, destination);
        predecessor = dequeue(fr);
    }
    print_path(predecessor);
}