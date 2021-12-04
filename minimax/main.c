#include <stdio.h>
#include "game.h"

int main()
{
    for(int i=0;i<30;i++) printf("\n");

    printf("Jogo da Velha - Versao HARD\n");
    printf("=============================\n\n");
    printf("Informe com qual lado deseja comecar:\n1- X (Cruz)\n2- O (Circulo)\n\nEntrada numerica: ");
    int player;
    while(player!=1 && player!=2){
        scanf("%d", &player);
        getchar();
        if(player==1) create_game('X');
        else if(player==2) create_game('O');
    }
    

}