#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "game.h"

#define dbg if(0)
typedef struct STATE state;
typedef struct STACK stack;

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
};
int mini(int a, int b){
    return (a<b)? a: b;
}
int maxi(int a, int b){
    return (a>b)? a: b;
}
int evaluate(state *s, char max, char min){
    int value_max = 0, value_min=0;
    for(int i=0;i<3;i++)
    {
        // if((s->game[i][0]==max||s->game[i][1]==max||s->game[i][2]==max) && (s->game[i][0]!=min && s->game[i][1]!=min && s->game[i][2]!=min ))
        if((s->game[i][0]!=min && s->game[i][1]!=min && s->game[i][2]!=min )) value_max+=1;
        else if((s->game[i][0]!=max && s->game[i][1]!=max && s->game[i][2]!=max )) value_min+=1;

    }
    for(int j=0;j<3;j++)
    {
        // if((s->game[0][j]==max||s->game[1][j]==max||s->game[2][j]==max) && (s->game[0][j]!=min && s->game[1][j]!=min && s->game[2][j]!=min ))
        if((s->game[0][j]!=min && s->game[1][j]!=min && s->game[2][j]!=min )) value_max+=1;
        else if((s->game[0][j]!=max && s->game[1][j]!=max && s->game[2][j]!=max )) value_min+=1;
    }
    // if((s->game[0][0]==max || s->game[1][1]==max || s->game[1][1]==max) && ((s->game[0][0]!=min && s->game[1][1]!=min && s->game[1][1]!=min)))
    if((s->game[0][0]!=min && s->game[1][1]!=min && s->game[2][2]!=min)) value_max+=1;
    else if((s->game[0][0]!=max && s->game[1][1]!=max && s->game[2][2]!=max)) value_min+=1;

    if((s->game[0][2]!=min && s->game[1][1]!=min && s->game[2][0]!=min)) value_max+=1;
    else if((s->game[0][2]!=max && s->game[1][1]!=max && s->game[2][0]!=max)) value_min+=1;
    
    if(game_ended(s,max,min)==1) return INT_MAX;
    else if(game_ended(s,max,min)==-1) return INT_MIN;
    return (value_max-value_min);
}
int game_ended(state *s, char max, char min){
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
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(s->game[i][j]=='.') return 0;
        }
    }
    return 2; //
}
void change_game(state *s, char c, int i, int j){
    s->game[i][j] = c;
}
void print_state(state *s){
    printf("\n===============================\n");
    printf("   1  2  3\n");
    for(int i=0;i<3;i++){
        
        for(int j=0;j<3;j++){
            if(j==0) printf("%d |%c|",i+1, s->game[i][j]);
            else printf("|%c|", s->game[i][j]);
        }
            
        printf("\n");
    }        
    // printf("\nEvaluation: %d\n", s->evaluation);
    printf("\n===============================\n");
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
    state *aux = s->top;
    printf("\n===============================\n");
    while(aux)
    {
         print_state(aux);
         aux=aux->next;
    }
    printf("\n===============================\n");
}
void evaluate_all(stack *st,char max, char min)
{
    state *aux = st->top;
    while(aux){
        aux->evaluation = evaluate(aux,max,min);
        aux=aux->next;
    }
}
int call_next_turn(stack *st, char player, state* cur_state, char max, char min){
    int win = game_ended(cur_state,max,min);
    while(!win){
        cur_state = pop(st); //
        state *new_turn = alpha_beta_pruning(cur_state, max, min); // Turno da I.A
        win = game_ended(new_turn, max, min);

        for(int i=0;i<30;i++) printf("\n");
        printf("Turno da IA:");
        print_state(new_turn);
        printf("Pressione qualquer tecla para continuar...\n");
        getchar();
        if(win){
            push(st, new_turn);
            break;
        }
        else{
            int i, j;
            for(int i=0;i<30;i++) printf("\n");
            printf("Turno do Participante:\n");
            print_state(new_turn);
            printf("Insira em que linha que deseja jogar: ");
            scanf("%d", &i);
            printf("Insira em que coluna que deseja jogar: ");
            scanf("%d", &j);
            while(new_turn->game[i-1][j-1]!='.'){
                for(int i=0;i<30;i++) printf("\n");
                printf("Posicao ja ocupada, repita o processo\n");
                printf("Jogo atual:");
                print_state(new_turn);
                printf("Insira em que linha que deseja jogar: ");
                scanf("%d", &i);
                printf("Insira em que coluna que deseja jogar: ");
                scanf("%d", &j);
                getchar();
            }
            change_game(new_turn, min, i-1, j-1);
            push(st, new_turn);
            win = game_ended(new_turn, max, min);
        } 
       
    }
    for(int i=0;i<40;i++) printf("\n");
    printf("Estado Final:");
    print_state(pop(st));
    return win;
}
void create_game(char player){
    stack *st = create_stack();
    state *cur_state = create_state(NULL);
    for(int i=0;i<30;i++) printf("\n");

    printf("Estado Inicial do Jogo:");
    print_state(cur_state);
    if(player=='X'){
        int i, j;
        printf("Insira em que linha que deseja jogar: ");
        scanf("%d", &i);
        printf("Insira em que coluna que deseja jogar: ");
        scanf("%d", &j);
        getchar();
        change_game(cur_state,'X', i-1, j-1);
        for(int i=0;i<30;i++) printf("\n");
        printf("Turno do Participante:");
        print_state(cur_state);
        printf("Pressione qualquer tecla para continuar...\n");
        getchar();
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
    switch (call_next_turn(st, player, cur_state, max, min))
    {
    case 1:
        printf("\nVitoria da IA (*^ - ^*)\n");
        break;
    case -1:
        printf("\nVitória do Jogador (x _ x)\n");
        break;
    default:
        printf("\nEmpate (^ ^;)\n");
        break;
    };
}

int valor_min(state *cur, int alpha, int beta, char ia, char player, state* next_turn, int flag){
    int evaluation = game_ended(cur,ia,player);
    if(evaluation) return evaluate(cur,ia,player);
    
    int v = INT_MAX;
    stack *next_states = create_stack();
    generate_next_state(next_states, cur, player);
    dbg printf("MIN TURN");
    // evaluate_all(next_states;, ia, player);
    dbg print_stack(next_states);
    // printf("\nFIM PILHA\n");
    while(!is_empty(next_states)){
        state *aux = pop(next_states);
        v = mini(v, valor_max(aux, alpha,beta,ia,player,next_turn,0));
        dbg printf("Minimizing, Evaluation: %d Estado:\n",v);
        dbg print_state(aux);
        if(v<=alpha) return v;
        beta = mini(beta, v);
    }
    return v;
}
int valor_max(state *cur, int alpha, int beta, char ia, char player, state *next_turn, int flag){
    int evaluation = game_ended(cur,ia,player);
    if(evaluation) return evaluate(cur,ia,player);
    
    int v = INT_MIN;
    stack *next_states = create_stack();
    
    generate_next_state(next_states, cur, ia);
    dbg printf("MAX TURN");
    // evaluate_all(next_states, ia, player);
    dbg print_stack(next_states);
    // printf("\nFIM PILHA\n");
    while(!is_empty(next_states)){
        state *aux = pop(next_states);
        int k = valor_min(aux, alpha,beta, ia, player, next_turn, 0);

        
        if(v<k && flag) {
            *next_turn = *aux;
            dbg printf("Possivel proximo turno\n");
        }
        v = maxi(v,k);
        dbg printf("Maximizing, Evaluation: %d Estado:\n",v);
        dbg print_state(aux);
        if(v>=beta) return v;
        alpha = maxi(alpha, v);
    }
    return v;
}

state* alpha_beta_pruning(state *cur, char ia, char player){
    state *next_turn = (state*)malloc(sizeof(state));
    int v = valor_max(cur, INT_MIN, INT_MAX, ia, player, next_turn,1);
    return next_turn;
}

