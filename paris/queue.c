#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "queue.h"
#include "graph.h"
#define dbg if(0)
struct QUEUE
{
    state *head;
};
struct STATE
{
    int station;
    char line;
    state *next;
    state *prev;

    float g_cost;
    float f_cost;
};
pqueue* create_queue()
{
    pqueue *new_pqueue = (pqueue*) malloc(sizeof(pqueue));
    new_pqueue->head = NULL;
    return new_pqueue;
}
state* create_state(graph *paris, state *source_station, int adjacent_station, char line){
    state* segment = (state*)malloc(sizeof(state));
    segment->station = adjacent_station;
    segment->prev = source_station;    
    segment->g_cost = 0;    
    if(source_station){
        segment->g_cost = source_station->g_cost;    
        dbg printf("Custo para chegar aqui: %.0f\n", source_station->g_cost);
    }
    segment->f_cost = 0; 
    segment->line = line;  
    segment->next = NULL;
    return segment;
}
int is_empty(pqueue *pqueue)
{
    return(pqueue->head==NULL);
}
float line_change(graph *paris, char prev_line, int prev_station, int next_station){
    if(prev_station==next_station) return 0;
    else {
        if(get_line(paris, prev_station, next_station)!=prev_line && prev_line!=' '){
            dbg printf("Houve baldeacao de %d para %d\n", prev_station, next_station);
            return 2;
        } 
        else return 0;
    }
}
void enqueue(graph *paris, pqueue *pqueue, state *new_state, int destination)
{
    int prev_cost = 0, prev_station = new_state->station, prev_line=' ';
    if(new_state->prev != NULL) {
        prev_cost = new_state->g_cost;
        prev_line = new_state->prev->line;
        prev_station = new_state->prev->station; 
    }

    float change_line = line_change(paris, prev_line, prev_station, new_state->station);
    new_state->g_cost = change_line + prev_cost + calculate_cost_to_station(paris, prev_station, new_state->station);
    new_state->f_cost = new_state->g_cost + calculate_heuristics(paris, new_state->station, destination);
    dbg printf("Calculando custo para %d e %d = %.0f\n", prev_station, new_state->station, new_state->g_cost);
    dbg printf("Calculando heuristica para %d e %d = %.0f\n", new_state->station, destination, new_state->f_cost);
    if(is_empty(pqueue) || (new_state->f_cost < pqueue->head->f_cost))
    {
        new_state->next = pqueue->head;
        pqueue->head = new_state;
    }
    else
    {
        state *aux = pqueue->head;
        while((aux->next!=NULL) && (new_state->f_cost >= aux->next->f_cost))
        {
            aux=aux->next;
        }
        new_state->next = aux->next;
        aux->next = new_state;
    }
}
void print_queue(pqueue *pq){
    state *aux = pq->head;
    while(aux!=NULL){
        printf("E%d(%.0f)\n", aux->station, aux->f_cost);
        aux=aux->next;
    }
}
state* peak(pqueue *pq){
    return pq->head;
}
state* get_next(state* s){
    return s->next;
}
state* dequeue(pqueue *pq){
    state *aux = pq->head;
    pq->head = pq->head->next;
    return aux;
}
void generate_new_states(graph *paris, pqueue* pq, state *predecessor, int destination){
    iterate_and_enqueue(paris, pq, predecessor, destination);
}
int get_station_number(state *state){
    return state->station;
}
float get_g_cost(state *st){
    return st->g_cost;
}
int is_final(state *terminal, int destination){
    return (terminal->station==destination);
}
void print_path(state *final){
    state *tmp = final->prev;
    final->next = NULL;
    while(tmp!=NULL){
        tmp->next = final;
        tmp = tmp->prev;
        final = final->prev;
    }
    tmp = final;
    printf("\n==================================================\n==================================================\nPercurso selecionado:\n\n\n");
    printf("Parta com o trem na Estacao E%d", tmp->station);
    int bald=0;
    while(tmp->next!=NULL){
        if(tmp->line!=tmp->next->line && tmp->line!=' ') 
        {
            char strA[10] = "";
            char strB[20] = "";
            if(tmp->line=='B') strcat(strA, "Azul\0");
            if(tmp->line=='Y') strcat(strA, "Amarela\0");
            if(tmp->line=='G') strcat(strA, "Verde\0");
            if(tmp->line=='R') strcat(strA, "Vermelha\0");
            if(tmp->next->line=='B') strcat(strB, "Azul\0");
            if(tmp->next->line=='Y') strcat(strB, "Amarela\0");
            if(tmp->next->line=='G') strcat(strB, "Verde\0");
            if(tmp->next->line=='R') strcat(strB, "Vermelha\0");
            bald++;
            printf("\nBaldeacao da Linha %s para %s em E%d", strA, strB, tmp->station);
        }
        printf("\nSiga para a Estacao E%d", tmp->next->station);
        tmp=tmp->next;
    }
    printf("\n\nTempo de Viagem: %.2f minuto(s)", 2*tmp->g_cost);
    printf("\nQuantidade de Baldeacoes: %d vez(es)", bald);
    printf("\n\nFim da Viagem !!\n==================================================\n==================================================");
}