#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define DEBUG if(0)
typedef struct NODE state;
typedef struct QUEUE queue;
struct NODE
{
    char state_n;
    short mis1;
    short mis2;
    short can1;
    short can2;
    short priority;
    short ilha_atual;
    short valid;
    short final;
    state *next;
    state *predecessor;
};
struct QUEUE
{
    state *head;
};
int isEmpty(queue *queue)

{
    return(queue->head == NULL);
}
void print_prev(state *st)
{
    if( st->predecessor != NULL){
        state *aux = st->predecessor;
        printf("Missionarios na Ilha 1: %d\n", aux->mis1);
        printf("Canibais na Ilha 1: %d\n", aux->can1);
        printf("Missionarios na Ilha 2: %d\n", aux->mis2);
        printf("Canibais na Ilha 2: %d\n", aux->can2);
        if(aux->ilha_atual==0) printf("Barco na Ilha 1\n");
        else printf("Barco na Ilha 2\n");
        if (aux->valid) printf("Estado Valido\n");
        else  printf("Estado Invalido\n");
        if (aux->final) printf("Estado Final\n");
        else printf("Estado Nao Final\n");
    }
    else printf("Primeiro estado");
}
void print_cur(state *st)
{
    if( st != NULL){
        state *aux = st;
        printf("Missionarios na Ilha 1: %d\n", aux->mis1);
        printf("Canibais na Ilha 1: %d\n", aux->can1);
        printf("Missionarios na Ilha 2: %d\n", aux->mis2);
        printf("Canibais na Ilha 2: %d\n", aux->can2);
        if(aux->ilha_atual==0) printf("Barco na Ilha 1\n");
        else printf("Barco na Ilha 2\n");
        if (aux->valid) printf("Estado Valido\n");
        else  printf("Estado Invalido\n");
        if (aux->final) printf("Estado Final\n");
        else printf("Estado Nao Final\n");
        printf("\n------------\n");
    }
    else printf("Nulo");
}
queue* createQueue()
{
    queue *pq = (queue*) malloc(sizeof(queue));
    pq->head=NULL;
    return pq;
}
void print_min(state *st){
     if( st != NULL){
        state *aux = st;
        printf("M1: %d, ", aux->mis1);
        printf("C1: %d, ", aux->can1);
        printf("M2: %d, ", aux->mis2);
        printf("C2: %d, ", aux->can2);
        if(aux->ilha_atual==0) printf("Barco: I1, ");
        else printf("Barco: I2, ");
        if (aux->valid) printf("Valido, ");
        else  printf("Invalido, ");
        if (aux->final) printf("Estado Final\n");
        else printf("Estado Nao Final\n");
    }
    else printf("Nulo");
}
void print_queue(queue *queue)
{
    if(!isEmpty(queue))
    {
        state *aux=queue->head;
        while(aux!=NULL)
        {
            print_min(aux);
            aux=aux->next;
        }
        printf("\n");
    }
    else printf("-1");
    
}
short is_valid(state *st){
    if((st->can1>=0) && (st->can1<=3) && (st->can2 >=0) && (st->can2<=3) && (st->mis1 >= 0) && (st->mis1<=3) &&(st->mis2 >= 0) && (st->mis2<=3) && (st->can1+st->can2==3) && (st->mis1+st->mis2==3))
    {
        if((st->mis1>0 && (st->mis1 >= st->can1)) && (st->mis2>0 && (st->mis2 >= st->can2))) return 1;
        else if((st->mis1==0 && (st->can1 >= st->mis1)) || (st->mis2==0 && (st->can2 >= st->mis2))) return 1;
        else return 0;
    }
    else return 0;
}
short is_final(state *st){
    if((st->can1==0 && st->can2==3) && (st->mis1==0 && st->mis2==3)) return 1;
    else return 0;
}
state* createState(char state_n, short mis1, short can1, short mis2,  short can2, short ilha)
{
    state *new_node = (state*) malloc(sizeof(state));
    new_node->priority = 0;
    new_node->state_n = state_n;
    new_node->mis1 = mis1;
    new_node->mis2 = mis2;    
    new_node->can1 = can1;
    new_node->can2 = can2;
    new_node->ilha_atual = ilha;
    new_node->final = is_final(new_node);
    new_node->valid = is_valid(new_node);
    new_node->next = NULL;
    new_node->predecessor = NULL;
    return new_node;
}
void enqueue_normal(queue *normal_queue, state *new_state, state *predecessor)
{
    state *new_node = new_state;
    new_node->predecessor = predecessor;
    if(!(new_node->valid)) return;
    if(isEmpty(normal_queue))
    {
        new_node->next = NULL;
        normal_queue->head = new_node;
    }
    else
    {
        state *aux = normal_queue->head;
        while(aux->next!=NULL)
        {
            aux=aux->next;
        }
        new_node->next = aux->next;
        aux->next = new_node;
    }
}
state* dequeue(queue *queue)
{
    if(!isEmpty(queue))
    {
        state *head = queue->head;
        queue->head = queue->head->next;
        head->next=NULL;
        return head;
    }
    return NULL;
}
state* peak(queue *queue)
{
    if(!isEmpty(queue))
    {
        return queue->head;
    }
    return NULL;
}
void generate_new_states(queue *fronteira, state *atual){
    //ILHA A
    if((atual->ilha_atual)==0){
        state *s1 = createState(' ', atual->mis1 - 1, atual->can1, atual->mis2+1, atual->can2, 1);
        state *s2 = createState(' ', atual->mis1 - 2, atual->can1, atual->mis2+2, atual->can2, 1);
        state *s3 = createState(' ', atual->mis1 - 1, atual->can1 - 1, atual->mis2+1, atual->can2+1, 1);
        state *s4 = createState(' ', atual->mis1, atual->can1-1, atual->mis2, atual->can2+1, 1);
        state *s5 = createState(' ', atual->mis1, atual->can1-2, atual->mis2, atual->can2+2, 1);
        enqueue_normal(fronteira, s1, atual);
        enqueue_normal(fronteira, s2, atual);
        enqueue_normal(fronteira, s3, atual);
        enqueue_normal(fronteira, s4, atual);
        enqueue_normal(fronteira, s5, atual);
    }
    //ILHA B
    else {
        state *s1 = createState(' ', atual->mis1 + 1, atual->can1, atual->mis2 - 1, atual->can2, 0);
        state *s2 = createState(' ', atual->mis1 + 2, atual->can1, atual->mis2 - 2, atual->can2, 0);
        state *s3 = createState(' ', atual->mis1 + 1, atual->can1 + 1, atual->mis2 - 1, atual->can2 - 1, 0);
        state *s4 = createState(' ', atual->mis1, atual->can1 + 1, atual->mis2, atual->can2 - 1, 0);
        state *s5 = createState(' ', atual->mis1, atual->can1 + 2, atual->mis2, atual->can2 - 2, 0);
        enqueue_normal(fronteira, s1, atual);
        enqueue_normal(fronteira, s2, atual);
        enqueue_normal(fronteira, s3, atual);
        enqueue_normal(fronteira, s4, atual);
        enqueue_normal(fronteira, s5, atual);
    }
}
short get_mis1(state *s){
    return s->mis1;
}
short get_mis2(state *s){
    return s->mis2;
}
short get_can1(state *s){
    return s->can1;
}
short get_can2(state *s){
    return s->can2;
}
short get_boat(state *s){
    return s->ilha_atual;
}
void print_transition(state *ori, state *des){
    if(des->ilha_atual==0){
        printf("Mova %d missionário(os) e %d canibal(is) para a Ilha A\n", abs(des->mis1 - ori->mis1), abs(des->can1 - ori->can1));
    }
    else {
        printf("Mova %d missionário(os) e %d canibal(is) para a Ilha B\n", abs(des->mis2 - ori->mis2), abs(des->can2 - ori->can2));
    }
}
void generate_path(state *s){
    state *aux = s;
    while(aux->predecessor!=NULL){
        aux->predecessor->next = aux;
        aux = aux->predecessor;
    }
    while(aux!=NULL){
        if(aux->next!=NULL){
            print_transition(aux, aux->next);
        }
        aux = aux->next;
    }

}




