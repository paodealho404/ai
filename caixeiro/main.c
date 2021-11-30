#include<stdio.h>
#include"caixeiro.h"
#include<alg.h>
#include<limits.h>
#include<time.h>
#define MX_SIZE 11
int main(){
    int source, destination, dist;
    graph *dis = create_graph();
    FILE *file = fopen("in.txt", "r");
    if(!file) printf("Erro abrindo arquivo de entrada");
    else {
        while(fscanf(file, "%d %d %d", &source, &destination, &dist)!=EOF){
            add_vertex(dis, source, destination, dist);
        }
    }
    
    srand(time(NULL));
    int ori,min_dist=INT_MAX,i,k,j;
    printf("Insira a cidade de origem: ");
    scanf("%d", &ori);
    printf("Insira uma quantidade de reinicios aleatorios: ");
    scanf("%d", &i);
    printf("Insira uma quantidade de iteracoes de otimizacao: ");
    scanf("%d", &k);
    int v[MX_SIZE+1] = {0}, final[MX_SIZE+1]={0}, cur_dist=0;
    
    while(i--){
        j = k;
        generate_new_path(v, ori);
        while(j--){
            if(is_valid(v, dis)){
                cur_dist  = total_traveled_distance(v, dis);
                if(cur_dist<=min_dist){
                    copy(v, final);
                    min_dist = cur_dist;
                } 
            }
            optimize_solution_operator(v);
            // print_path(v);
        }
    }
    if(!is_done(final)||!is_valid(final, dis)){
        printf("\n\n==================================================================\n\n\n");
        printf("\nQuantidade de iteracoes insuficientes para achar trajeto valido...\n\nSolucoes:\n- Reinicie o programa novamente, sem alteracoes\n");
        printf("- Reinicie com mais iteracoes aleatorias\n- Reinicie com mais iteracoes de otimizacao");
        printf("\n\n==================================================================\n");
    }
    else{
        printf("\n\n==================================================================\n\n");
        print_path(final);
        printf("Distancia Total Percorrida: %d", min_dist);
        printf("\n\n==================================================================\n");
    }
}