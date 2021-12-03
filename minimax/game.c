#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
typedef struct STATE state;
typedef struct STACK stack;
int valor_min(state *cur, int alpha, int beta);
int valor_max(state *cur, int alpha, int beta);
struct STATE
{
    char game[3][3];
    int evaluation;
    state *prev;
    state *next;
};
struct STACK
{
    state *top;
};

int is_empty(stack *s){
    return (s->top==NULL);
}
stack* create_stack(){
    stack *new_stack = (stack*)malloc(sizeof(stack));
    new_stack->top = NULL;
    return new_stack;
}
state* create_state(state* prev){
    state *new_state = (state*)malloc(sizeof(state));
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(!prev) 
            {
                new_state->game[i][j] = '.';
            }
            else {
                new_state->game[i][j] = prev->game[i][j];
            }
        }   
    }
    new_state->evaluation = 0;
    new_state->prev = prev;
    new_state->next = NULL;
    return new_state;
}

void push(stack *s, state *push_element){
    if(is_empty(s)) s->top = push_element;
    else{
        push_element->next = s->top;
        s->top = push_element;
    }
}

state* pop(stack *s){
    state *pop_element = s->top;
    s->top = s->top->next;
    return pop_element;
}

int evaluate(state *s, char max, char min){
    if(s->game[1][1]==s->game[2][2] && s->game[1][1]==s->game[0][0] && (s->game[1][1]==max)) return 1;
    if(s->game[1][1]==s->game[2][2] && s->game[1][1]==s->game[0][0] && (s->game[1][1]==min)) return -1;
    if(s->game[1][1]==s->game[0][2] && s->game[1][1]==s->game[2][0] && (s->game[1][1]==max)) return 1;
    if(s->game[1][1]==s->game[0][2] && s->game[1][1]==s->game[2][0] && (s->game[1][1]==min)) return -1;
    for(int i=0;i<3;i++)
    {   
        if(s->game[i][0]==s->game[i][1] && s->game[i][0]==s->game[i][2] && (s->game[i][0]==max)) return 1;
        if(s->game[i][0]==s->game[i][1] && s->game[i][0]==s->game[i][2] && (s->game[i][0]==min)) return -1;
    }
    for(int j=0;j<3;j++)
    {   
        if(s->game[0][j]==s->game[1][j] && s->game[0][j]==s->game[2][j] && (s->game[0][j]==max)) return 1;
        if(s->game[0][j]==s->game[1][j] && s->game[0][j]==s->game[2][j] && (s->game[0][j]==min)) return -1;
    }
    return 0;
}
void change_game(state *s, char c, int i, int j){
    s->game[i][j] = c;
}
void print_state(state *s){
    printf("\n");
    printf("   1  2  3\n");
    for(int i=0;i<3;i++){
        
        for(int j=0;j<3;j++){
            if(j==0) printf("%d |%c|",i+1, s->game[i][j]);
            else printf("|%c|", s->game[i][j]);
        }
            
        printf("\n");
    }        
    printf("\nEvaluation: %d\n", s->evaluation);
}
void generate_next_state(stack *st, state *cur, char c){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(cur->game[i][j]=='.'){
                state *new_state = create_state(cur);
                change_game(new_state, c, i,j);
                push(st, new_state);
            }
        } 
    }
}
void swap(int *a, int *b){
    int aux = *a;
    *a = *b;
    *b = aux;
}

void print_stack(stack *s){
    while(!is_empty(s)) print_state(pop(s));
}
int call_next_turn(stack *st, char player, state* cur_state, char max, char min){
    char min, max;
    int turn=1;
    int win = evaluate(cur_state,max,min);
    while(!is_empty(st)){
        cur_state = pop(st);
        cur_state->evaluation = evaluate(cur_state,max,min);

        
        if(cur_state->evaluation==0){ // ESTADO INTERMEDIÁRIO
            generate_next_state(st, cur_state, turn, max, min);      
        } else{ //NÓS FOLHAS
            if(turn && cur_state->prev->evaluation < cur_state->evaluation){
                cur_state->prev->evaluation = cur_state->evaluation;

            }   // turn = 1 --> max
            else
        }

        
        win = cur_state->evaluation;
        if(turn==1) turn= 0;
        else turn = 1;
    }
    if(win) return 0;
    else return 1;
}
void create_game(char player){
    stack *st = create_stack();
    state *cur_state = create_state(NULL, 0);
    printf("Estado Inicial do Jogo:");
    print_state(cur_state);
    if(player=='X'){
        int i, j;
        printf("Insira a que linha que deseja jogar: ");
        scanf("%d", &i);
        printf("Insira a que coluna que deseja jogar: ");
        scanf("%d", &j);
        change_game(cur_state,'X', i-1, j-1);
    }
    push(st, cur_state);

    char min, max;
    if(player=='X'){
        min = 'X';
        max = 'O';
    } 
    else{
        min = 'O';
        max = 'X';
    }
    while(call_next_turn(st, player, cur_state, max, min)){
        //TODO
    }
}

int valor_min(state *cur, int alpha, int beta, char ia, char player){
    int evaluation = evaluate(cur,ia,player);
    if(evaluation) return evaluation;
    
    int v = INT_MAX;
    stack *next_states = create_stack();
    generate_next_state(next_states, cur, player);
    while(!is_empty(next_states)){
        state *aux = pop(next_states);
        v = min(v, valor_max(aux, alpha,beta,ia,player));
        if(v<=alpha) return v;
        beta = min(beta, v);
    }
    return v;
}
int valor_max(state *cur, int alpha, int beta, char ia, char player){
    int evaluation = evaluate(cur,ia,player);
    if(evaluation) return evaluation;
    
    int v = INT_MIN;
    stack *next_states = create_stack();
    generate_next_state(next_states, cur, ia);
    while(!is_empty(next_states)){
        state *aux = pop(next_states);
        v = max(v, valor_min(aux, alpha,beta, ia, player));
        if(v>=beta) return v;
        alpha = max(alpha, v);
    }
    return v;
}

state* alfa_beta_prunning(state *cur, char ia, char player){
    int v = valor_max(cur, INT_MIN, INT_MAX, ia, player);
}

